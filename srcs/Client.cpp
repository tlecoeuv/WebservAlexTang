#include "../includes/Client.hpp"

Client::Client()
{
    endConnexion = false;
}

Client::~Client()
{
}

int sendall(int s, const char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;

    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
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
		Reponse reponse(server.request, server.locations);
		std::cout << reponse.header.c_str() << std::endl;
		std::cout << strlen(reponse.header.c_str()) << std::endl;
		//write(fd, reponse.header.c_str(), reponse.header.size());
		int size = reponse.header.size();
		sendall(fd, reponse.header.c_str(), &size);
	}
}

// void    Client::parseBuffer(int nbytes)
// {

// }