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


std::string CGI::headerCGI() {
	std::map<std::string, std::string> header;
	std::string tmp;

	std::string ret;
	ret = "GATEWAY_INTERFACE=CGI/1.1\n";
	ret += "PATH_TRANSLATED=" + ressourcePath + "\n";
	ret += "QUERY_STRING=" + uri.query + "\n";
	ret += "REQUEST_METHOD=" + request.method + "\n";
	ret += "CONTENT_LENGTH=" + std::to_string(request.body.length()) + "\n";
	ret += "CONTENT_TYPE" + getMIMEType(uri.path);
	ret += "REQUEST_URI=" + request.uri + "\n";
	ret += "REMOTE_IDENT=\n";
	ret += "REDIRECT_STATUS=200\n";
	ret += "REMOTE_ADDR=" + std::to_string(clientfd) + "\n";
	ret += "SCRIPT_NAME" + nameLocation + (nameLocation.size() ? "" : "/");
	ret += "PATH_INFO" + uri.path;
	ret += "SCRIPT_FILENAME=" + ressourcePath + "\n";
	ret += "SERVER_NAME=" + server.host + "\n";
	ret += "SERVER_PORT=" + std::to_string(server.port) + "\n";
	ret += "SERVER_PROTOCOL=HTTP/1.1\n";
	ret += "SERVER_SOFTWARE=webserv/1.0\n";
	for (size_t k = 0; k < uri.queryName.size(); ++k) 
		ret += "HTTP_" + uri.queryName.at(k) + "=" + uri.queryValue.at(k);
	return (ret);
}