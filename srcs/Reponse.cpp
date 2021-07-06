#include "../includes/Reponse.hpp"

Reponse::Reponse(Request request, std::map<std::string, Location> locations){
	makeReponse(request, locations);
}


//if index == getindex => chercher index
void Reponse::makeReponse(Request request, std::map<std::string, Location> locations){
	std::map<std::string, std::string> info;

	info["Content-Type"] = "text/html";
	std::string ContentType = "Content-Type: text/plain\n";
	std::string ContentLength = "Content-Length: 12\n\n";
	std::string body = "Hello world!";
	header += "HTTP/1.1 200 OK\n";
	header += ContentType;
	header += ContentLength;
	header += body;
	info["path"] = locations["/"].root;
	//info["path"] += locations["/"].index;
	info["path"] += "/index.html";
	request.method = "GET";
	if (request.method == "GET")
		Reponse::get(info, request);
}

void Reponse::get(std::map<std::string, std::string> info, Request request){
	(void)request;

	info["Content-Type"] = _getMIMEType(info["path"]);
	std::cerr << "Content-Type " << info["Content-Type"] << std::endl;
	//info["Content-Type"] = _getMIMEType("ok.jpg");
}

std::string Reponse::_getMIMEType(std::string filename)
{
	std::map<std::string, std::string> MIME;
	std::string extension;
	size_t i;

	i = filename.size() - 1;
	while (i > 0 && filename[i] != '.')
		--i;
	if (i == 0)
		return ("text/plain");
	extension = filename.substr(i, filename.size());
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