#ifndef SERVEUR_HPP
# define SERVEUR_HPP

/*Library: */

#include <string>
#include <vector>
#include <iostream>
#include <netdb.h>

/* Includes: */
#include "Location.hpp"
#include "../includes/Request.hpp"

class		Server
{
public:
	Server() {};
	Server(int p, std::string h, std::string n, std::string e, std::vector<Location> loc);
	~Server() {};

	Request	getRequest(int client_fd);
	void	handleRequest(Request request);

	int							port;
	std::string					host;
	std::string					name;
	std::string					error;
	std::vector<Location>		locations;
	int							sd;

private:
	void get_buffer_request(int fd);
};

#endif
