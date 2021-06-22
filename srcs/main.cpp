#include <iostream>
#include <unistd.h>

#include "../includes/Config.hpp"
#include "../includes/Server.hpp"
#include "../includes/SocketManager.hpp"

void error(std::exception& ex)
{
	std::cerr << "Error " << ex.what() << std::endl;
}

int main(int argc, char **argv){

    if (argc != 2)
        exit(0);
    try {
        Config server(argv[1]);
		for (size_t i = 0 ; i < server.getServer().size() ; ++i){
			SocketManager	manager;

			manager.add_server(server.getServer().at(i));
			manager.start_servers();
		}
    }
    catch(std::exception& ex) {
		error(ex);
	}
}
