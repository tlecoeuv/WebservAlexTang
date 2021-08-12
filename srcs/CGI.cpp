#include "CGI.hpp"

CGI::CGI(std::string cp, std::string rp, Request req, int cfd, Server s, std::string nl, URI u) {
	cgiPath = cp;
	ressourcePath = rp;
	request = req;
	clientfd = cfd;
	server = s;
	nameLocation = nl;
	uri = u;
}


char**  CGI::headerCGI() {
	std::vector<std::string> header;
	
	header.push_back("GATEWAY_INTERFACE=CGI/1.1");
	header.push_back("PATH_TRANSLATED=" + ressourcePath);
	header.push_back("QUERY_STRING=" + uri.query);
	header.push_back("REQUEST_METHOD=" + request.method);
	header.push_back("CONTENT_LENGTH=" + std::to_string(request.body.length()));
	header.push_back("CONTENT_TYPE" + getMIMEType(uri.path));
	header.push_back("REQUEST_URI=" + request.uri);
	header.push_back("REMOTE_IDENT=");
	header.push_back("REDIRECT_STATUS=200");
	header.push_back("REMOTE_ADDR=" + std::to_string(clientfd));
	header.push_back("SCRIPT_NAME=" + nameLocation + (nameLocation.size() ? "" : "/"));
	header.push_back("PATH_INFO=" + uri.path);
	header.push_back("SCRIPT_FILENAME=" + ressourcePath);
	header.push_back("SERVER_NAME=" + server.host);
	header.push_back("SERVER_PORT=" + std::to_string(server.port));
	header.push_back("SERVER_PROTOCOL=HTTP/1.1");
	header.push_back("SERVER_SOFTWARE=webserv/1.0");
	for (size_t k = 0; k < uri.queryName.size(); ++k) 
		header.push_back("HTTP_" + uri.queryName.at(k) + "=" + uri.queryValue.at(k));
	char** tab = (char**)malloc(header.size() * sizeof(char*));
	for (size_t i = 0; i < header.size(); i++){
		//std::cout << header.at(i) << std::endl;
		tab[i] = strdup(header.at(i).c_str());
	}
	tab[header.size()] = NULL;
	return (tab);
}

char**	doArgv(std::string path, URI uri){
	char** argv = (char**)malloc(3 * sizeof(char*));
	argv[0] = (char*)malloc(path.size() * sizeof(char));
	strcpy(argv[0], path.c_str());
	argv[1] = (char*)malloc(uri.path.size() * sizeof(char));
	strcpy(argv[1], uri.path.c_str());
	argv[2] = 0;
	return (argv);
}

void freeCGI(char **tab)
{
	size_t i = -1;

	std::cout << "FREE" << std::endl;
	while (tab[++i]){
		std::cout << i << " " << tab[i] << std::endl;
		free(tab[i]);
	}
	free(tab);
}
