#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Server.hpp"

std::string reduce(const std::string& str); 

class Config {
    private:
        std::vector<Server> confServer;

    public:
        Config(std::string conf);
        void parametre(std::string conf);
        std::vector<std::string> readConf(std::string conf);
        int configLocation(int index, std::vector<std::string> readParam);

};

#endif