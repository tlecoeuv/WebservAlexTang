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


char**  CGI::headerCGI(std::string body, char ** argv) {
	std::vector<std::string> header;

	header.push_back("GATEWAY_INTERFACE=CGI/1.1");
	header.push_back("PATH_TRANSLATED=index.php");
	header.push_back("QUERY_STRING=" + uri.query);
	header.push_back("REQUEST_METHOD=" + request.method);
	header.push_back("CONTENT_LENGTH=" + std::to_string(body.length()));
	header.push_back("CONTENT_TYPE=" + getMIMEType(uri.path));
	header.push_back("REMOTE_IDENT=");
	header.push_back("REDIRECT_STATUS=200");
	header.push_back("REMOTE_ADDR=" + std::to_string(clientfd));
	header.push_back((std::string)"PATH_INFO=" + argv[1]);
	header.push_back((std::string)"SCRIPT_FILENAME=" + argv[1]);
	header.push_back("SERVER_PORT=" + std::to_string(server.port));
	header.push_back("SERVER_PROTOCOL=HTTP/1.1");
	//header.push_back("SERVER_SOFTWARE=webserv/1.0");
	for (size_t k = 0; k < uri.queryName.size(); ++k) 
		header.push_back("HTTP_" + uri.queryName.at(k) + "=" + uri.queryValue.at(k));
	char** tab = (char**)malloc(header.size() * sizeof(char*));
	for (size_t i = 0; i < header.size(); i++){
		std::cerr << header.at(i) << "_" <<std::endl;
		tab[i] = strdup(header.at(i).c_str());
	}
	tab[header.size()] = NULL;
	return (tab);
}

void		CGI::cgi_body(std::string path) {
	std::string ret;
	std::ifstream myfile(path.c_str());

	while (std::getline(myfile, ret, '\n')){
		body += ret;
		body += "\n";
	}
}

char**	doArgv(std::string path, URI uri){
	char *pwd; 
	pwd = getcwd(NULL, 0);
	if (path[0] == '.')
		path = path.substr(1, path.size() - 1);
	char** argv = (char**)malloc(3 * sizeof(char*));
	path = pwd + path;
	argv[0] = (char*)malloc(path.size() * sizeof(char));
	strcpy(argv[0], path.c_str());
	uri.path = pwd + uri.path;
	argv[1] = (char*)malloc((uri.path.size()) * sizeof(char));
	strcpy(argv[1], uri.path.c_str());
	argv[2] = 0;
	return (argv);
}