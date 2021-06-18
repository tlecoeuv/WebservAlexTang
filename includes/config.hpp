#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include "Server.hpp"

std::string reduce(const std::string& str); 
struct location {
    std::vector<std::string> method;
    std::string root;
    std::string index;
    std::string cgi;
    std::string cgi_path;
    std::string max_body;
};

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