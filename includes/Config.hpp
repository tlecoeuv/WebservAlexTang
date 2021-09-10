#ifndef CONFIG_HPP
#define CONFIG_HPP

/* Library: */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/* Includes: */
#include "Server.hpp"

std::vector<std::string>	fileToVector(std::string file, int conf);

class Config {
	public:
		std::vector<Server>	confServer;
		Config(std::string	conf);
		std::vector<Server>	getServer();

	private:
		void 				parametre(std::string conf);
		int					configLocation(int index, std::vector<std::string> readParam, Server &newServer);
		void 				checkConfig();
};

#endif
