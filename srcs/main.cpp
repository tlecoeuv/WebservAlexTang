#include <iostream>
#include <unistd.h>
#include <signal.h>

#include "../includes/Config.hpp"
#include "../includes/Server.hpp"
#include "../includes/ServerManager.hpp"

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
	ServerManager	manager;

    if (argc != 2)
        exit(0);
    try {
		signal(SIGINT, end);
        Config config(argv[1]);
		manager.initServers(config.getServer());
	}
    catch(std::exception& ex) {
		error(ex);
		exit(0);
	}
	manager.runServers();
}
