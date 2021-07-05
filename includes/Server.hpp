#ifndef SERVEUR_HPP
# define SERVEUR_HPP

/*Library: */

#include <string>
#include <vector>
#include <iostream>
#include <netdb.h>
#include <poll.h>

/* Includes: */
#include "Location.hpp"
#include "Request.hpp"
#include "Reponse.hpp"

class		Server
{
public:
	Server() {};
	Server(int p, std::string h, std::string n, std::string e, std::map<std::string, Location> loc);
	~Server() {};

	void	getRequest(int client_fd);
	void	handleRequest(int client_fd);

	int									port;
	std::string							host;
	std::string							name;
	std::string							error;
	std::map<std::string, Location>		locations;
	Request								request;
	Reponse								reponse;
	int									sd;

private:
	void get_buffer_request(int fd);
};

#endif
