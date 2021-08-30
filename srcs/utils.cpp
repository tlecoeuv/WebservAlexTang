#include <map>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>

std::string trim(const std::string& str, const std::string& whitespace) {
	size_t begin = str.find_first_not_of(whitespace);
	if (begin == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(whitespace);
	size_t range = end - begin + 1;
	return str.substr(begin, range);
}

std::string reduce(const std::string& str)
{
	const std::string& fill = " ";
	const std::string& whitespace = " \t";
	std::string result = trim(str, whitespace);
	size_t begin = result.find_first_of(whitespace);
	while (begin != std::string::npos) {
		size_t end = result.find_first_not_of(whitespace, begin);
		size_t range = end - begin;
		result.replace(begin, range, fill);
		size_t newStart = begin + fill.length();
		begin = result.find_first_of(whitespace, newStart);
	}
	return result;
}

std::vector<std::string> fileToVector(std::string file, int conf) {
	std::string ret;
	std::vector<std::string> vector;
	std::ifstream myfile(file.c_str());

	if (conf && !myfile) {
		std::cerr << "Error" << std::endl;
		throw std::out_of_range("Wrong Path");
	}
	while (std::getline(myfile, ret, '\n')) {
		ret = reduce(ret);
		if (!ret.size())
			continue ;
		vector.push_back(ret);
	}
	return (vector);
}

std::vector<std::string>	split(std::string str, std::string delimiter)
{
	std::vector<std::string>	vec;
	size_t						pos = 0;
	std::string					token;

	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		if (token.size() > 0)
			vec.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	if (str.size() > 0)
		vec.push_back(str);
	return (vec);
}

std::string getMIMEType(std::string filename) {
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
	return ("text/html");
}