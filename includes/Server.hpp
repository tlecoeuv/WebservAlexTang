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
	int							port;
	std::string					host;
	std::string					name;
	std::string					error;
	std::vector<Location>		locations;

private:

};

#endif
