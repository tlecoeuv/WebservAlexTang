#include "../includes/Server.hpp"
#include <unistd.h>

/* Constructors and Destructors: */

Server::Server(int p, std::string h, std::string n, std::string e,
				std::vector<Location> loc)
		: port(p), host(h), name(n), error(e), locations(loc)
{}

/* other methods: */

void Server::getRequest(int client_fd){
    char                    buf[256];
    std::string result;
    int nbytes;

    while ((nbytes = recv(client_fd, buf, sizeof buf, 0)) > 0){
        result += buf;
		if (nbytes < 256)
			break ;
	}
    if (nbytes <= 0)
        if (nbytes == 0)
            printf("pollserver: socket %d hung up\n", client_fd);
        else
            perror("recv");
    else
        request.fill(result);
}

void	Server::handleRequest(int client_fd)
{
//	char* buf[1000];
	std::cout << "new connection on fd: " << client_fd << std::endl;
	getRequest(client_fd);
	reponse.makeReponse(request);
	write(client_fd , reponse.header.c_str() , reponse.header.size());
	std::cout << "client request:\n________________________\n" << std::endl;
	std::cout << request.method << std::endl;
	std::cout << request.host << std::endl;
/*	int nbytes = recv(client_fd, buf, sizeof buf, 0);
	buf[nbytes] = '\0';
	std::cout << "client request:\n________________________\n" << std::endl;
	std::cout << buf << std::endl;*/
	//send response to client here.
}
