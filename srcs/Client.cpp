#include "../includes/Client.hpp"

Client::Client()
{
    endConnexion = false;
}

Client::~Client()
{
}

void    Client::readRequest()
{
    int     nbytes;

    nbytes = recv(fd, buf, 4096, 0);
    if (nbytes <= 0)
	{
		if (nbytes == 0)
			printf("Client on fd %d has closed connexion\n", fd);
		else
			perror("recv");
		endConnexion = true;
	}
    else  // We got some good data from a client
	{
        //parseBuffer(nbytes);
		write(0, buf, nbytes);
	}

}

// void    Client::parseBuffer(int nbytes)
// {

// }