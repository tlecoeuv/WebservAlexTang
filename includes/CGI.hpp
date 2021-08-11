#ifndef CGI_HPP
# define CGI_HPP

/* Library: */
#include <string>

/* Includes: */
#include "Server.hpp"
#include "Request.hpp"
#include "Reponse.hpp"
#include "Uri.hpp"

class CGI {
	public:
		Server server;
		std::string cgiPath;
		std::string ressourcePath;
		Request request;
		int clientfd;

		CGI(std::string cp, std::string rp, Request req, int cfd, Server s);
		std::string headerCGI();

	private:

};

#endif