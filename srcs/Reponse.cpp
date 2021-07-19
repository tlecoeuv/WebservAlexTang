#include "../includes/Reponse.hpp"

Reponse::Reponse(Request request, std::map<std::string, Location> locations){
	for (std::map<std::string, Location>::iterator it = locations.begin() ; it != locations.end(); ++it){
		std::cout << request.uri << " " << it->first << std::endl;
		if (request.uri == it->first){
			makeReponse(request, it->second);
			return ;
		}
	}
}

void Reponse::makeReponse(Request request, Location location){
	std::map<std::string, std::string> info;

	info["Content-Type"] = "text/html";
	header = "HTTP/1.1 200 OK\n";
	info["path"] = location.root + "/";
	info["path"] += location.index;
	if (!acceptedMethod(request.method, location.method))
		return methodError(info, 405);
	if (request.method == "GET")
		Reponse::methodGet(info, request);
	else if (request.method == "DELETE")
		Reponse::methodDelete(info);
	else if (request.method == "POST")
		Reponse::methodPOST(info, request, location.max_body);
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
	header = "HTTP/1.1 " + std::to_string(code) + " " + getMessage(code);
	header += "Content-Type: ";
	header += info["Content-Type"];
	header += "\nContent-Length: ";
	std::string body = bodyError(readFile("./www/error.html"), code);
	header += std::to_string(body.size());
	header += "\n\n";
	header += body;
}

std::string Reponse::getMIMEType(std::string filename) {
	std::map<std::string, std::string> MIME;
	std::string extension;
	size_t i;

	i = filename.size() - 1;
	while (i > 0 && filename[i] != '.')
		--i;
	if (i == 0)
		return ("text/plain");
	extension = filename.substr(i + 1, filename.size());
	MIME["aac"] = "audio/aac";
	MIME["abw"] = "application/x-abiword";
	MIME["arc"] = "application/octet-stream";
	MIME["avi"] = "video/x-msvideo";
	MIME["azw"] = "application/vnd.amazon.ebook";
	MIME["bin"] = "application/octet-stream";
	MIME["bmp"] = "image/bmp";
	MIME["bz"] = "application/x-bzip";
	MIME["bz2"] = "application/x-bzip2";
	MIME["csh"] = "application/x-csh";
	MIME["css"] = "text/css";
	MIME["csv"] = "text/csv";
	MIME["doc"] = "application/msword";
	MIME["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	MIME["eot"] = "application/vnd.ms-fontobject";
	MIME["epub"] = "application/epub+zip";
	MIME["gif"] = "image/gif";
	MIME["htm"] = "text/html";
	MIME["html"] = "text/html";
	MIME["ico"] = "image/x-icon";
	MIME["ics"] = "text/calendar";
	MIME["jar"] = "application/java-archive";
	MIME["jpeg"] = "image/jpeg";
	MIME["jpg"] = "image/jpeg";
	MIME["js"] = "application/javascript";
	MIME["json"] = "application/json";
	MIME["mid"] = "audio/midi";
	MIME["midi"] = "audio/midi";
	MIME["mpeg"] = "video/mpeg";
	MIME["mpkg"] = "application/vnd.apple.installer+xml";
	MIME["odp"] = "application/vnd.oasis.opendocument.presentation";
	MIME["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	MIME["odt"] = "application/vnd.oasis.opendocument.text";
	MIME["oga"] = "audio/ogg";
	MIME["ogv"] = "video/ogg";
	MIME["ogx"] = "application/ogg";
	MIME["otf"] = "font/otf";
	MIME["png"] = "image/png";
	MIME["pdf"] = "application/pdf";
	MIME["ppt"] = "application/vnd.ms-powerpoint";
	MIME["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	MIME["rar"] = "application/x-rar-compressed";
	MIME["rtf"] = "application/rtf";
	MIME["sh"] = "application/x-sh";
	MIME["svg"] = "image/svg+xml";
	MIME["swf"] = "application/x-shockwave-flash";
	MIME["tar"] = "application/x-tar";
	MIME["tif"] = "image/tiff";
	MIME["tiff"] = "image/tiff";
	MIME["ts"] = "application/typescript";
	MIME["ttf"] = "font/ttf";
	MIME["vsd"] = "application/vnd.visio";
	MIME["wav"] = "audio/x-wav";
	MIME["weba"] = "audio/webm";
	MIME["webm"] = "video/webm";
	MIME["webp"] = "image/webp";
	MIME["woff"] = "font/woff";
	MIME["woff2"] = "font/woff2";
	MIME["xhtml"] = "application/xhtml+xml";
	MIME["xls"] = "application/vnd.ms-excel";
	MIME["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	MIME["xml"] = "application/xml";
	MIME["xul"] = "application/vnd.mozilla.xul+xml";
	MIME["zip"] = "application/zip";
	MIME["3gp"] = "audio/3gpp";
	MIME["3g2"] = "audio/3gpp2";
	MIME["7z"] = "application/x-7z-compressed";
	if (MIME.count(extension))
		return (MIME[extension]);
	return ("application/octet-stream");
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