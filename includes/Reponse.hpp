#ifndef REPONSE_HPP
# define REPONSE_HPP

/* Library: */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <libgen.h>

/* Includes: */
#include "Request.hpp"
#include "Location.hpp"
#include "Server.hpp"
#include "CGI.hpp"
#include "Uri.hpp"
#include "utils.hpp"

std::string getMIMEType(std::string filename);

class 	Reponse {
	public:
		std::string						header;
		bool							autoindex;
		Request							request;
		std::map<std::string, Location>	locations;
		int								clientfd;
		Server							server;

	public:
		Reponse(){};
		Reponse(Request r, Server s, int cfd);
		void		makeReponse(Request request, Location location, std::string tmpUri);
		void		methodGet(std::map<std::string, std::string> info, std::string body, std::string tmpUri, std::string max_body);
		void		methodPOST(std::map<std::string, std::string> info, Request request, std::string max_body, std::string body);
		void		methodDelete(std::map<std::string, std::string> info);
		std::string	methodCGI(CGI cgi, std::string path, URI uri);
		std::string	readBodyCGI(std::string body);
		void		methodError(std::map<std::string, std::string> info, int code);
		int			acceptedMethod(std::string requestMethod, std::vector<std::string> locationsMethod);
		std::string	bodyError(std::string oldBody, int code);
		std::string	getMessage(size_t code);
		std::string	readFile(std::string file);
		void		printResponse();
		bool		CGIcapacity(std::string path, Location location);
		std::string	directory_contents(const char *directory_path, std::string tmpUri);
};

#endif
