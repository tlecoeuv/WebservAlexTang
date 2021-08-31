#ifndef SERVERMANAGER_HPP
# define SERVERMANAGER_HPP

#include "Server.hpp"
#include "Location.hpp"
#include "Request.hpp"
#include "Reponse.hpp"
#include "Client.hpp"

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
#include <list>


class 	ServerManager
{
public:

	ServerManager(void);
	~ServerManager(void);

	void	initServers(std::vector<Server> configServers);
	void	runServers(void);

private:

	std::vector<Server>			servers;
	struct pollfd				pfds[200];
	std::list<Client>			clients;
	int							nfds;
	bool						compress_array;

	void		add_to_pfds(int newfd);
	void		compress_pfds(void);
	int			is_server_socket(int fd);
	int			get_index_server(int fd);
	Client		getClientByFd(int fd);
	void		checkServerSocket();
	void		checkClientSocket();
	void		handleNewConnexion(int index);
	int 		create_server_socket(Server &server);
	void		removeClient(Client &client);
};

#endif
