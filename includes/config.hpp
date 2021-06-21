#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Server.hpp"

std::vector<std::string> fileToVector(std::string file);

class Config {
    private:
        std::vector<Server> confServer;
    public:
        Config(std::string conf);
        std::vector<Server> getServer();
        //print();
    private:
        void parametre(std::string conf);
        std::vector<std::string> readConf(std::string conf);
        int configLocation(int index, std::vector<std::string> readParam, Server &newServer);
		void checkConfig();

};

#endif