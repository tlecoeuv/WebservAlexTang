#ifndef SOCKETMANAGER_HPP
# define SOCKETMANAGER_HPP

#include "Server.hpp"
#include "Location.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#include <iostream>

class 	SocketManager
{
public:

	SocketManager(void);
	~SocketManager(void);

	void	add_server(Server &server);
	void	start_servers(void);

private:

	std::vector<Server>			servers;
	std::vector<pollfd> 		pfds;

	void	add_to_pfds(int newfd);
	void	del_from_pfds(int i);
	int		get_index_server(int fd);
	int 	create_server_socket(Server &server);
};

#endif
