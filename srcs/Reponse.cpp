#include "Reponse.hpp"

Reponse::Reponse(Request r, Server s, int cfd): request(r), locations(s.locations), clientfd(cfd), server(s) {
	std::string tmpUri = request.uri;

	if (tmpUri.size() > 1 && tmpUri[tmpUri.size() - 1] == '/')
			tmpUri.pop_back();
	while (tmpUri.size()) {
		//std::cout << "tmpUri: " << tmpUri << std::endl;
		for (std::map<std::string, Location>::iterator it = locations.begin() ; it != locations.end(); ++it)
			if (tmpUri == it->first){
				makeReponse(request, it->second, tmpUri);
				return ;
			}
		tmpUri.pop_back();
		while (tmpUri.size() && tmpUri[tmpUri.size() - 1] != '/')
			tmpUri.pop_back();
		if (tmpUri.size() > 1)
			tmpUri.pop_back();
	}
	std::map<std::string, std::string> info;

	info["Content-Type"] = "text/html";
	methodError(info, 403);
}

void Reponse::makeReponse(Request request, Location location, std::string tmpUri){
	std::map<std::string, std::string> info;

	info["Content-Type"] = "text/html";
	header = "HTTP/1.1 200 OK\n";
	if (request.uri.size() > 2 && request.uri[request.uri.size() - 1] == '/')
		request.uri.pop_back();
	if (tmpUri == request.uri) {
		info["path"] = location.root + "/";
		info["path"] += location.index;
	}
	else
		info["path"] = location.root + "/" + request.uri.substr(tmpUri.size(), request.uri.size());
	//std::cout << "Path: " << info["path"] << std::endl;
	if (!acceptedMethod(request.method, location.method))
		return methodError(info, 405);
	URI uri(request.uri);
	if (CGIcapacity(uri.path, location)){
		std::cout << "CGI on" << std::endl;
		CGI cgi(location.cgi_path, info["path"], request, clientfd, server, tmpUri, uri);
		methodCGI(cgi, info, tmpUri, uri);
	}
	else if (request.method == "GET")
		methodGet(info, request);
	else if (request.method == "DELETE")
		methodDelete(info);
	else if (request.method == "POST")
		methodPOST(info, request, location.max_body);
}

int Reponse::acceptedMethod(std::string requestMethod, std::vector<std::string> locationsMethod){
	for (size_t i = 0 ; i < locationsMethod.size(); ++i){
    	if (requestMethod == locationsMethod[i])
			return 1;
	}
	return 0;
}

void Reponse::methodGet(std::map<std::string, std::string> info, Request request){
	std::string body; 
	(void)request;

	info["Content-Type"] = getMIMEType(info["path"]);
	try {
		body = readFile(info["path"]);
	}
	catch (const std::exception &e){
		methodError(info, 403);
	}
	header += "Content-Type: ";
	header += info["Content-Type"];
	header += "\nContent-Length: ";
	header += std::to_string(body.size());
	header += "\n\n";
	header += body;
}

void Reponse::methodPOST(std::map<std::string, std::string> info, Request request, std::string max_body){
	struct stat buf;

	if (max_body.size() && (int)request.body.size() > atoi(max_body.c_str()))
		methodError(info, 413);
	std::cout << "request.body: " << request.body << std::endl;
	if ((stat(info["path"].c_str(), &buf)) == 0){
		if (S_ISREG(buf.st_mode)){
			int fd = open(info["path"].c_str(), O_WRONLY | O_TRUNC, 0644);
			write(fd, request.body.c_str(), request.body.size());
			close(fd);
			header += "Content-Type: ";
			header += info["Content-Type"];
			header += "\nContent-Length: 0\n\n";
		}
		else 
			methodError(info, 500);
	}
	else {
		int fd = open(info["path"].c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644);
		write(fd, request.body.c_str(), request.body.size());
		close(fd);
		header = "HTTP/1.1 201 Created\n";
		header += "Content-Type: ";
		header += info["Content-Type"];
		header += "\nContent-Length: 0\n\n";
	}
}

void Reponse::methodDelete(std::map<std::string, std::string> info) {
	struct stat buf;

	if ((stat(info["path"].c_str(), &buf)) == 0 && S_ISREG(buf.st_mode)) {
		unlink(info["path"].c_str());
		info["Content-Type"] = getMIMEType(info["path"]);
		header += "Content-Type: ";
		header += info["Content-Type"];
		header += "\nContent-Length: 0\n\n";
	}
	else
		methodError(info, 404);
}

void Reponse::methodCGI(CGI cgi, std::map<std::string, std::string> info, std::string path, URI uri) {
	pid_t pid;
	int fd[2];
request.body = "<?php php_info() ?>";
	if (pipe(fd) == -1){
		methodError(info, 500);
		return ;
	}
	pid = fork();
	if (pid == 0) {
		char ** argv = doArgv(path, uri);
		close(fd[1]);
		dup2(fd[0], 0);
		int tmp_fd = open("/tmp/fileCGI", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (tmp_fd < 0){
			methodError(info, 500);
			exit(0);
		}
		dup2(tmp_fd, 1);
		dup2(tmp_fd, 2);
		execve(path.c_str(), argv, cgi.headerCGI());
		close(0);
		close(tmp_fd);
		close(fd[0]);
		exit(0);
	}
	else {
		close(fd[0]);
		std::cout << "request.body " << request.body << std::endl;
		write(fd[1], request.body.c_str(), request.body.length());
		close(fd[1]);
		waitpid(-1, NULL, 0);
	}
	std::vector<std::string> fileCGI = fileToVector("/tmp/fileCGI", 0);
	std::string newfile;
	for (size_t i = 0; i < fileCGI.size(); i++){
		newfile += fileCGI.at(i) + "\n";
	}
	std::cout << std::endl << "test" << newfile << std::endl;
	return ;
}

std::string Reponse::bodyError(std::string oldBody, int code) {
	size_t start_pos = 0;
	std::string value = "$1";
	std::string tmp = std::to_string(code);

	while((start_pos = oldBody.find(value, start_pos)) != std::string::npos) {
		oldBody.replace(start_pos, value.length(), tmp);
		start_pos += tmp.length();
	}
	start_pos = 0;
	value = "$2";
	tmp = getMessage(code);
	while((start_pos = oldBody.find(value, start_pos)) != std::string::npos) {
		oldBody.replace(start_pos, value.length(), tmp);
		start_pos += tmp.length();
	}
	return (oldBody);
}

void Reponse::methodError(std::map<std::string, std::string> info, int code) {
	std::string body;

	header = "HTTP/1.1 " + std::to_string(code) + " " + getMessage(code);
	header += "Content-Type: ";
	header += info["Content-Type"];
	header += "\nContent-Length: ";
	body = bodyError(readFile("./www/error.html"), code);
	header += std::to_string(body.size());
	header += "\n\n";
	header += body;
}

std::string Reponse::getMessage(size_t code) {
	std::map<std::size_t, std::string> message;

	message[100] = "Continue";
	message[101] = "Switching Protocols";
	message[200] = "OK";
	message[201] = "Created";
	message[202] = "Accepted";
	message[203] = "Non-Authoritative Information";
	message[204] = "No Content";
	message[205] = "Reset Content";
	message[206] = "Partial Content";
	message[300] = "Multiple Choices";
	message[301] = "Moved Permanently";
	message[302] = "Found";
	message[303] = "See Other";
	message[304] = "Not Modified";
	message[305] = "Use Proxy";
	message[307] = "Temporary Redirect";
	message[400] = "Bad Request";
	message[401] = "Unauthorized";
	message[402] = "Payment Required";
	message[403] = "Forbidden";
	message[404] = "Not Found";
	message[405] = "Method Not Allowed";
	message[406] = "Not Acceptable";
	message[407] = "Proxy Authentication Required";
	message[408] = "Request Timeout";
	message[409] = "Conflict";
	message[410] = "Gone";
	message[411] = "Length Required";
	message[412] = "Precondition Failed";
	message[413] = "Payload Too Large";
	message[414] = "URI Too Long";
	message[415] = "Unsupported Media Type";
	message[416] = "Range Not Satisfiable";
	message[417] = "Expectation Failed";
	message[426] = "Upgrade Required";
	message[500] = "Internal Server Error";
	message[501] = "Not Implemented";
	message[502] = "Bad Gateway";
	message[503] = "Service Unavailable";
	message[504] = "Gateway Timeout";
	message[505] = "HTTP Version Not Supported";
	return message[code];
}

std::string Reponse::readFile(std::string file) {
	char buffer[256 + 1] = {0};
	int fd;
	int res;
	std::string result;

	if((fd = open(file.c_str(), O_RDONLY)) < -1){
		throw std::out_of_range("The file does not exists.");
	}
	while ((res = read(fd, buffer, 256)) > 0)
		for (size_t j = 0; j < (size_t)res; ++j)
			result += buffer[j];
	if (res < 0)
		throw std::out_of_range("Error while reading.");
	return (result);
}

bool Reponse::CGIcapacity(std::string path, Location location) {
	std::string tmpCGI;

	if (location.cgi_path.size())
		for (size_t i = path.size() - 1; i > 0 ; i--)
			if(path[i] == '.') {
				tmpCGI = path.substr(i, path.size() - 1);
				return (tmpCGI == location.cgi ? true : false);
			}
	return false;
}