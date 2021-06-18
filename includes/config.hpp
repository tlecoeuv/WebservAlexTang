#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <fcntl.h>
#include <sstream>
#include <fstream>

std::string reduce(const std::string& str); 
struct location {
    std::vector<std::string> method;
    std::string root;
    std::string index;
    std::string cgi;
    std::string cgi_path;
    std::string max_body;
};

struct param {
    std::string port;
    std::string error;
    std::string name;
    std::string host;
    std::vector<struct location> _location;
};

class config {
    private:
        std::vector<param> confServer;

    public:
        config(std::string conf){
            parametre(conf);
        }
        void parametre(std::string conf){
            std::vector<std::string> readParam;
            readParam = readConf(conf);
            for (size_t i = 0; i < readParam.size() ; ){
                std::cout << readParam.at(i) << std::endl;
                if (readParam.at(i).compare(0, 6, "server") == 0){
                    param newServer;
                    while (++i < readParam.size() && readParam.at(i).compare(0, 6, "server") != 0){
                        if (!(readParam.at(i).compare(0, 6, "listen")))
                            newServer.port = readParam.at(i).substr(7);
                        else if (!(readParam.at(i).compare(0, 5, "error")))
                            newServer.error = readParam.at(i).substr(6);
                        else if (!(readParam.at(i).compare(0, 4, "name")))
                            newServer.name = readParam.at(i).substr(5);
                        else if (!(readParam.at(i).compare(0, 4, "host")))
                            newServer.host = readParam.at(i).substr(5);
                        else if (!(readParam.at(i).compare(0, 8, "location")))
                            i += configLocation(i, readParam);
                    }
                    confServer.push_back(newServer);
                }
            }
        }
        std::vector<std::string> readConf(std::string conf) {
            std::string ret;
            std::vector<std::string> vector;
            std::ifstream myfile(conf.c_str());

            if (!myfile) {
                std::cerr << "Error" << std::endl;
                throw std::out_of_range("Wrong Path");
            }
            while (std::getline(myfile, ret, '\n')) {
                ret = reduce(ret);
                if (!ret.size())
                    continue ;
                vector.push_back(ret);
            }
            return (vector);
        }
        int configLocation(int index, std::vector<std::string> readParam){
            (void)readParam;
            return index;
        }

};

#endif