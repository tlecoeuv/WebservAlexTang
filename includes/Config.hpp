#ifndef CONFIG_HPP
#define CONFIG_HPP

/* Library: */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/* Includes: */
#include "Server.hpp"

std::vector<std::string> fileToVector(std::string file);

class Config {
    public:
        std::vector<Server> confServer;
    public:

        Config(std::string conf);
        std::vector<Server> getServer();
        //print();
    private:
        void parametre(std::string conf);
        int configLocation(int index, std::vector<std::string> readParam, Server &newServer);
		void checkConfig();

};

#endif
