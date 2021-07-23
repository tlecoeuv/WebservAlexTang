#ifndef CGI_HPP
# define CGI_HPP

/* Library: */
#include <string>

/* Includes: */
#include "Request.hpp"
#include "Reponse.hpp"

class CGI {
	public:
		std::string cgiPath;
		std::string ressourcePath;
		Request request;

		CGI(std::string cp, std::string rp, Request req);

	private:

};

#endif