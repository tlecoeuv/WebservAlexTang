#include "CGI.hpp"

CGI::CGI(std::string cp, std::string rp, Request req, int cfd, Server s) {
	cgiPath = cp;
	ressourcePath = rp;
	request = req;
	clientfd = cfd;
	server = s;
}


std::string CGI::headerCGI() {
	std::map<std::string, std::string> header;
	std::string tmp;
	size_t i;
	//size_t j;
	
	std::string ret;
	ret = "GATEWAY_INTERFACE=CGI/1.1\n";
	ret += "PATH_TRANSLATED=" + ressourcePath + "\n";
	//ret += "QUERY_STRING=" + _getQueryString + "\n";
	ret += "REQUEST_METHOD=" + request.method + "\n";
	ret += "CONTENT_LENGTH=" + std::to_string(request.body.length()) + "\n";
	//for (size_t u = 0; u < _request.getHeaderFields().size(); u++)
	//	if (_request.getHeaderFields()[u]._field_name == "Content-Type")
	//	{
	//		header["CONTENT_TYPE"] = _request.headers;
	//	}
	ret += "REQUEST_URI=" + request.uri + "\n";
	ret += "REMOTE_IDENT=\n";
	ret += "REDIRECT_STATUS=200\n";
	ret += "REMOTE_ADDR=" + std::to_string(clientfd) + "\n";
	//header["REMOTE_ADDR"] = _request.getClientIP();
	//header["SCRIPT_NAME"] = _location.name + ((_location.name[_location.name.length() - 1] == '/') ? "" : "/") + replace(_ressource_path, _location.root, "");
	//header["PATH_INFO"] = _removeQueryheader(_request.getRequestLine()._request_target);
	ret += "SCRIPT_FILENAME=" + ressourcePath + "\n";
	ret += "SERVER_NAME=" + server.host + "\n";
	ret += "SERVER_PORT=" + std::to_string(server.port) + "\n";
	ret += "SERVER_PROTOCOL=HTTP/1.1\n";
	ret += "SERVER_SOFTWARE=webserv/1.0\n";
	//for (size_t a = 0; a < _request.getHeaderFields().size(); ++a)
	//{
	//	tmp = _request.getHeaderFields()[a]._field_name;
	//	tmp = replace(tmp, "-", "_");
	//	for (size_t b = 0; b < tmp.size(); ++b)
	//		tmp[b] = toupper(tmp[b]);
	//	header["HTTP_" + tmp] = _request.getHeaderFields()[a]._field_value;
	//}
	i = 0;
	//while (g_envp[i])
	//{
	//	j = 0;
	//	while (g_envp[i][j] && g_envp[i][j] != '=')
	//		j++;
	//	header[std::string(g_envp[i], 0, j)] = std::string(g_envp[i], j + 1, std::string(g_envp[i]).size() - j);
	//	++i;
	//}
	return (ret);
}