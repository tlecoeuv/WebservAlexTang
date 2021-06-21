#include "../includes/Server.hpp"

/* Constructors and Destructors: */

Server::Server(int p, std::string h, std::string n, std::string e,
				std::vector<Location> loc)
		: port(p), host(h), name(n), error(e), locations(loc)
{}

Server::~Server(void)
{}

/* other methods: */
