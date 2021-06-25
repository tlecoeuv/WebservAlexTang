#include "../includes/SocketManager.hpp"

/* Constructors and Destructors: */


SocketManager::SocketManager()
{}

SocketManager::~SocketManager()
{}

/* other methods: */
/* public: */

void	SocketManager::add_server(Server &server)
{
	struct pollfd	newpfd;

	newpfd.fd = create_server_socket(server);
	newpfd.events = POLLIN;
	servers.push_back(server);
	pfds.push_back(newpfd);
}

void	SocketManager::add_to_pfds(int newfd)
{
	struct pollfd	newpfd;

	newpfd.fd = newfd;
	newpfd.events = POLLIN;
	pfds.push_back(newpfd);
}

void	SocketManager::del_from_pfds(int i)
{
	std::vector<struct pollfd>::iterator it;

	it = pfds.begin();
	while((*it).fd != pfds[i].fd)
		it++;
	pfds.erase(it);
}

int		SocketManager::get_index_server(int fd)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		if (servers[i].sd == fd)
			return(i);
	}
	return (-1);
}

void	SocketManager::start_servers(void)
{
	int 					poll_count;
	struct sockaddr_storage	remoteaddr;
    socklen_t				addrlen;

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
		for(size_t i = 0; i < pfds.size(); i++)
		{
			if (pfds[i].revents & POLLIN)
			{
				int index = get_index_server(pfds[i].fd);
				addrlen = sizeof remoteaddr;
				int newfd = accept(servers[index].sd, (struct sockaddr *)&remoteaddr,
						&addrlen);
				if (newfd == -1)
					perror("accept");
				else
				{
					servers[index].handleRequest(newfd);
					close(newfd);
				}
			}
		}
	}
}

/* private: */

int 	SocketManager::create_server_socket(Server &server) // Return a listening socket
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
