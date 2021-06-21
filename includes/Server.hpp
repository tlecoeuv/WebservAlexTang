#ifndef SERVEUR_HPP
# define SERVEUR_HPP

/*Library: */

#include <string>
#include <vector>

/* Includes: */
#include "Location.hpp"

class		Server
{
public:

	Server(int p, std::string h, std::string n, std::string e, std::vector<Location> loc);
	~Server(void);

	int							port;
	std::string					host;
	std::string					name;
	std::string					error;
	std::vector<Location>		locations;
	int							sd;

private:

};

#endif
