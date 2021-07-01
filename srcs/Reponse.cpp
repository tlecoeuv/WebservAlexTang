#include "../includes/Reponse.hpp"

void Reponse::makeReponse(Request request){
	std::map<std::string, std::string> info;

	(void)request;
	info["Content-Type"] = "text/html";
	std::string ContentType = "Content-Type: text/plain\n";
	std::string ContentLength = "Content-Length: 12\n\n";
	std::string body = "Hello world!";
	header += "HTTP/1.1 200 OK\n";
	header += ContentType;
	header += ContentLength;
	header += body;
	if (request.method == "GET")
		Reponse::get(info);
}

void Reponse::get(std::map<std::string, std::string> info){
	(void)info;
}