#include "../includes/Reponse.hpp"

void Reponse::makeReponse(Request request){
	(void)request;
	std::string ContentType = "Content-Type: text/plain\n";
	std::string ContentLength = "Content-Length: 12\n\n";
	std::string body = "Hello world!";
	header += "HTTP/1.1 200 OK\n";
	header += ContentType;
	header += ContentLength;
	header += body;
}