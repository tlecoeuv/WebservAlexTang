#include "../includes/Server.hpp"

/* Constructors and Destructors: */

Server::Server(int p, std::string h, std::string n, std::string e,
				std::vector<Location> loc)
		: port(p), host(h), name(n), error(e), locations(loc)
{}

/* other methods: */

void	Server::handleRequest(int client_fd)
{
//	char* buf[1000];
	std::cout << "new connection on fd: " << client_fd << std::endl;
/*	int nbytes = recv(client_fd, buf, sizeof buf, 0);
	buf[nbytes] = '\0';
	std::cout << "client request:\n________________________\n" << std::endl;
	std::cout << buf << std::endl;*/
	//send response to client here.
}
