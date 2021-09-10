#include <iostream>
#include <unistd.h>
#include <signal.h>

#include "Config.hpp"
#include "Server.hpp"
#include "ServerManager.hpp"
#include "utils.hpp"

bool	g_running = true;

void end(int signal)
{
	(void)signal;
	std::cout << "\b\b webserver is stopping." << std::endl;
	g_running = false;
}

void error(std::exception& ex)
{
	std::cerr << "\033[31mError: " << ex.what() << "\033[0m" << std::endl;
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
