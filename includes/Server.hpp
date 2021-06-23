#ifndef SERVEUR_HPP
# define SERVEUR_HPP

/*Library: */

#include <string>
#include <vector>
#include <iostream>

/* Includes: */
#include "Location.hpp"

class		Server
{
public:
	Server() {};
	Server(int p, std::string h, std::string n, std::string e, std::vector<Location> loc);
	~Server() {};

	void	handleRequest(int client_fd);

	int							port;
	std::string					host;
	std::string					name;
	std::string					error;
	std::vector<Location>		locations;
	int							sd;

private:

};

#endif
