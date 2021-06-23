#include "../includes/Server.hpp"
#include <unistd.h>

/* Constructors and Destructors: */

Server::Server(int p, std::string h, std::string n, std::string e,
				std::vector<Location> loc)
		: port(p), host(h), name(n), error(e), locations(loc)
{}

/* other methods: */

void Server::get_buffer_request(int client_fd){
    char                    buf[256];
    std::string result;
    int nbytes;

    while ((nbytes = recv(client_fd, buf, sizeof buf, 0)) > 0)
        result += buf;
    if (nbytes <= 0)
        if (nbytes == 0)
            printf("pollserver: socket %d hung up\n", client_fd);
        else
            perror("recv");
    else
        Request request(result);
}

void	Server::handleRequest(int client_fd)
{
//	char* buf[1000];
	std::cout << "new connection on fd: " << client_fd << std::endl;
	get_buffer_request(client_fd);
	char *hello = (char *)"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	write(client_fd , hello , strlen(hello));
/*	int nbytes = recv(client_fd, buf, sizeof buf, 0);
	buf[nbytes] = '\0';
	std::cout << "client request:\n________________________\n" << std::endl;
	std::cout << buf << std::endl;*/
	//send response to client here.
}
