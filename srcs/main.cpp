#include <iostream>
#include <unistd.h>

#include "../includes/Config.hpp"
#include "../includes/Server.hpp"
#include "../includes/SocketManager.hpp"

void end(int signal)
{
	(void)signal;
	std::cout << "\b\bWebserver is over" << std::endl;
	exit(0);
}

void error(std::exception& ex)
{
	std::cerr << "Error " << ex.what() << std::endl;
}

int main(int argc, char **argv)
{
	SocketManager	manager;
    if (argc != 2)
        exit(0);
    try {
		signal(SIGINT, end);
        Config server(argv[1]);
		for (size_t i = 0 ; i < server.getServer().size() ; ++i){
			manager.add_server(server.getServer().at(i));
		}
    }
    catch(std::exception& ex) {
		error(ex);
	}
	manager.start_servers();
}
