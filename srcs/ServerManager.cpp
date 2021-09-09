#include "ServerManager.hpp"

/* Constructors and Destructors: */


ServerManager::ServerManager() : nfds(1), compress_array(false)
{}

ServerManager::~ServerManager()
{}

/* public: */

void	ServerManager::initServers(std::vector<Server> configServers)
{
	servers = configServers;

	for (size_t i = 0; i < servers.size(); i++)
	{
		pfds[i].fd = create_server_socket(servers.at(i));
		pfds[i].events = POLLIN;
	}
	nfds = servers.size();
}

void	ServerManager::compress_pfds(void)
{
	compress_array = false;
	for(int i = 0; i < nfds; i++)
	{
		if (pfds[i].fd == -1)
		{
			for (int j = i; j < nfds; j++)
				pfds[j].fd = pfds[j+1].fd;
			i--;
			nfds--;
		}
	}
}

void	ServerManager::runServers(void)
{
	int 					poll_count;

	while(g_running)
	{
		poll_count = poll(pfds, nfds, -1);
		if (poll_count == -1)
		{
            perror("poll");
            break ;
        }
		checkServerSocket();
		checkClientSocket();
		if (compress_array)
			compress_pfds();
	}
}

/* private: */

void	ServerManager::add_to_pfds(int newfd)
{
	pfds[nfds].fd = newfd;
	pfds[nfds].events = POLLIN | POLLOUT;
	pfds[nfds].revents = 0;
	nfds++;
}

int		ServerManager::get_index_server(int fd)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		if (servers[i].sd == fd)
			return(i);
	}
	return (-1);
}

int		ServerManager::is_server_socket(int fd)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		if (servers[i].sd == fd)
			return(1);
	}
	return (0);
}

Client	ServerManager::getClientByFd(int fd)
{
	Client	client;
	for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if ((*it).fd == fd)
			client = (*it);
	}
	return (client);
}

void	ServerManager::checkServerSocket()
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		if (pfds[i].revents & POLLIN)
			handleNewConnexion(i);
	}
}

void	ServerManager::handleNewConnexion(int index)
{
	if (nfds > 199)
	{
		std::cout << "max number of connexions reached on webserv" << std::endl;
		return ;
	}
	Client	client;
	int		yes = 1;

	memset(&client.addr, 0, sizeof(client.addr));
	client.server = servers[index];
	client.addr_size = sizeof(sockaddr);
	if ((client.fd = accept(servers[index].sd, (struct sockaddr *)&client.addr, &client.addr_size)) < 0)
	{
		std::cout << "Error in accept fonction, client not created." << std::endl;
		return ;
	}
	if ((fcntl(client.fd, F_SETFL, O_NONBLOCK)) == -1)
	{
		close(client.fd);
		std::cout << "Error in fcntl., client not created." << std::endl;
		return ;
	}
	setsockopt(client.fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(int));
	add_to_pfds(client.fd);
	clients.push_back(client);
	std::cout << "new connection on fd: " << client.fd << std::endl;
}

void	ServerManager::checkClientSocket()
{
	Client					client;

	for (int i = servers.size(); i < nfds; i++)
	{
		if (pfds[i].revents & POLLIN)
		{
			client = getClientByFd(pfds[i].fd);
			
			client.readRequest();
			if (!client.endConnexion)
			{
				Reponse reponse(client.request, client.server, client.fd);
				int size = reponse.header.size();
				client.sendall(pfds[i].fd, reponse.header.c_str(), &size);
				/*char hello[] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
				write(pfds[i].fd , hello , strlen(hello));*/
			}
			if(client.endConnexion)
			{
				close(pfds[i].fd);
				pfds[i].fd = -1;
				compress_array = true;
				removeClient(client);
			}
			else
				client.request.clear();
		}
	}
}

void	ServerManager::removeClient(Client &client)
{
	std::list<Client>::iterator		it = clients.begin();

	for (; it != clients.end(); it ++)
	{
		if ((*it).fd == client.fd)
			break ;
	}
	clients.erase(it);
}

int 	ServerManager::create_server_socket(Server &server) // Return a listening socket
{
    int yes=1;        // For setsockopt() SO_REUSEADDR, below
	struct sockaddr_in address;

	if ((server.sd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		throw std::runtime_error("Problem when creating server socket.");
	fcntl(server.sd, F_SETFL, O_NONBLOCK);
	setsockopt(server.sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // local ip address.
	address.sin_port = htons(server.port);
	memset(address.sin_zero, '\0', sizeof(address.sin_zero));

	if (bind(server.sd, (struct sockaddr *)&address, sizeof(address)) < 0)
		throw std::runtime_error("Problem when binding server socket.");

	if (listen(server.sd, 200) < 0)
		throw std::runtime_error("Problem when calling listen on server socket.");

	return (server.sd);
}
