#ifndef CGI_HPP
# define CGI_HPP

/* Library: */
#include <string>

/* Includes: */
#include "Server.hpp"
#include "Request.hpp"
#include "Reponse.hpp"
#include "Uri.hpp"

std::string getMIMEType(std::string filename);

class CGI {
	public:
		Server server;
		std::string cgiPath;
		std::string ressourcePath;
		Request request;
		int clientfd;
		std::string nameLocation;
		URI uri;

		CGI(std::string cp, std::string rp, Request req, int cfd, Server s, std::string nl, URI u);
		std::string headerCGI();

	private:

};

#endif