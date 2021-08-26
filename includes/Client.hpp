#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"
#include "utils.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <sstream>

#define RECV_SIZE	65536

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
	std::string             requestString;

	void                    parseRequestString();
	int						parseFirstLine(std::string line);
	int						parseHeaderLine(std::string line);
};



#endif