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

int		SocketManager::is_server_fd(int fd)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		if (servers[i].sd == fd)
			return(servers[i].sd);
	}
	return (-1);
}

void	SocketManager::start_servers(void)
{
	int 					poll_count;
	struct sockaddr_storage	remoteaddr;
    socklen_t				addrlen;
	int						newfd;
	char 					buf[256];
	int						listener_fd;

	char *hello = (char *)"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

	for(;;)
	{
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
				if ((listener_fd = is_server_fd(pfds[i].fd)) >= 0)
				{
					addrlen = sizeof remoteaddr;
					newfd = accept(listener_fd,(struct sockaddr *)&remoteaddr,
                        			&addrlen);
					if (newfd == -1)
						perror("accept");
					else
					{
						add_to_pfds(newfd);
						send(newfd, hello, strlen(hello), 0);
					}
				}
				else
				{
					int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);
					int sender_fd = pfds[i].fd;

					if (nbytes <= 0) {
                        // Got error or connection closed by client
                        if (nbytes == 0) {
                            // Connection closed
                            printf("pollserver: socket %d hung up\n", sender_fd);
                        } else {
                            perror("recv");
                        }

                        close(pfds[i].fd); // Bye!
                        del_from_pfds(i);
                    }
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
