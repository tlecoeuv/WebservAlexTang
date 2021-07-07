#include "../includes/ServerManager.hpp"

/* Constructors and Destructors: */


ServerManager::ServerManager()
{}

ServerManager::~ServerManager()
{}

/* public: */

void	ServerManager::add_server(Server &server)
{
	struct pollfd	newpfd;

	newpfd.fd = create_server_socket(server);
	newpfd.events = POLLIN;
	pfds.push_back(newpfd);
	servers.push_back(server);
}

void	ServerManager::start_servers(void)
{
	int 					poll_count;

	for(;;)
	{
		/*if (signal)
			break;*/
		poll_count = poll(&pfds[0], pfds.size(), -1);
		if (poll_count == -1)
		{
            perror("poll");
            exit(1);
        }
		checkServerSocket();
		checkClientSocket();
	}
}

		/*for(size_t i = 0; i < pfds.size(); i++)
		{
			if (pfds[i].revents & POLLIN)
			{
				if (is_server_socket(pfds[i].fd))
				{
					handleNewConnexion(pfds[i].fd);
					std::cout << "new connection handled" << std::endl;
				}
				else
				{
					int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);
					if (nbytes <= 0)
					{
						if (nbytes == 0)
							printf("pollserver: socket %d hung up\n", pfds[i].fd);
						else
							perror("recv");
						close(pfds[i].fd);
						del_from_pfds(i);
					}
					else  // We got some good data from a client
					{
						write(0, buf, nbytes);
					}
				}
			}
		}*/

/* private: */

void	ServerManager::add_to_pfds(int newfd)
{
	struct pollfd	newpfd;

	newpfd.fd = newfd;
	newpfd.events = POLLIN;
	pfds.push_back(newpfd);
}

void	ServerManager::del_from_pfds(int i)
{
	std::vector<struct pollfd>::iterator it;

	it = pfds.begin();
	while((*it).fd != pfds[i].fd)
		it++;
	pfds.erase(it);
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
	Client	client;

	client.server = servers[index];
	if ((client.fd = accept(servers[index].sd, (struct sockaddr *)&client.addr, &client.addr_size)) < 0)
		perror("accept");
	if ((fcntl(client.fd, F_SETFL, O_NONBLOCK)) == -1)
	{
		close(client.fd);
		perror("fcntl");
	}
	add_to_pfds(client.fd);
	clients.push_back(client);
}

void	ServerManager::checkClientSocket()
{
	Client					client;

	for (size_t i = servers.size(); i < pfds.size(); i++)
	{
		if (pfds[i].revents & POLLIN)
		{
			client = getClientByFd(pfds[i].fd);
			client.readRequest();
			Reponse reponse(client.request, client.server.locations);
			int size = reponse.header.size();
			client.sendall(pfds[i].fd, reponse.header.c_str(), &size);
			if (client.endConnexion)
			{
				close(pfds[i].fd);
				del_from_pfds(i);
				//removeClient(client);
			}
		}
	}
}

			/*int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);
			if (nbytes <= 0)
			{
				if (nbytes == 0)
					printf("pollserver: socket %d hung up\n", pfds[i].fd);
				else
					perror("recv");
				close(pfds[i].fd);
				del_from_pfds(i);
			}
			else  // We got some good data from a client
			{
				write(0, buf, nbytes);
			}*/

int 	ServerManager::create_server_socket(Server &server) // Return a listening socket
{
    int yes=1;        // For setsockopt() SO_REUSEADDR, below
	struct sockaddr_in address;

	if ((server.sd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}
	fcntl(server.sd, F_SETFL, O_NONBLOCK);
	setsockopt(server.sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // local ip address.
	address.sin_port = htons(server.port);
	memset(address.sin_zero, '\0', sizeof(address.sin_zero));

	if (bind(server.sd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("In bind");
		exit(EXIT_FAILURE);
	}

	if (listen(server.sd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

	return (server.sd);
}
