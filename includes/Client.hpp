#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

class Client
{
public:
    Client();
    ~Client();

    int						fd;
    socklen_t				addr_size;
	struct sockaddr_storage	addr;
	Server					server;
    bool                    endConnexion;
    Request                 request;
    
    void                    readRequest();
    int                     sendall(int s, const char *buf, int *len);

private:
    char                    buf[4096];
    std::string             requestString;

    void                    parseRequestString();
};



#endif