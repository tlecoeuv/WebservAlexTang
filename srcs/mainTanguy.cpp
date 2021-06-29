#include "../includes/Server.hpp"
#include "../includes/SocketManager.hpp"

int		main()
{
	std::string				host("localhost");
	std::string				name("test");
	std::string				error("error");
	std::vector<Location>	locations;

	Server		testServ(8080, host, name, error, locations);
	ServerManager	manager;

	manager.add_server(testServ);
	manager.start_servers();

	return 0;
}
