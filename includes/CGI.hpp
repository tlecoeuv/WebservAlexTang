#ifndef CGI_HPP
# define CGI_HPP

/* Library: */
#include <string>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <iostream>

/* Includes: */
#include "Server.hpp"
#include "Request.hpp"
#include "Uri.hpp"

std::string getMIMEType(std::string filename);

class CGI {
	public:
		Server server;
		std::string cgiPath;
		std::string ressourcePath;
		std::string body;
		Request request;
		int clientfd;
		std::string nameLocation;
		URI uri;

		CGI(std::string cp, std::string rp, Request req, int cfd, Server s, std::string nl, URI u);
		void cgi_body(std::string path);
		char** headerCGI(std::string body, char ** argv);
	private:

};

void freeCGI(char **tab);
char**	doArgv(std::string path, URI uri);

#endif