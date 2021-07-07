#include "../includes/Client.hpp"

Client::Client()
{
    endConnexion = false;
}

Client::~Client()
{
}

int Client::sendall(int s, const char *buf, int *len)
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
    bool     first_recv = true;
    int     nbytes = 4096;

    while (nbytes == 4096)
    {
        nbytes = recv(fd, buf, 4096, 0);
        if (first_recv && nbytes == 0)
        {
            endConnexion = true;
            printf("Client on fd %d has closed connexion\n", fd);
        }
        if (nbytes < 0)
        {
            perror("recv");
            endConnexion = true;
        }
        first_recv = false;
        requestString += buf;
    }
    if (!endConnexion)
        parseRequestString();
}

void    Client::parseRequestString()
{
    std::cout << requestString << std::endl;
}