#include "../includes/Config.hpp"

// Constructor config
Config::Config(std::string conf){
     parametre(conf);
}

//save param of server
void Config::parametre(std::string conf){
    std::vector<std::string> readParam;
    readParam = readConf(conf);
    for (size_t i = 0; i < readParam.size() ; ){
        //std::cout << readParam.at(i) << std::endl;
        if (readParam.at(i).compare(0, 6, "server") == 0){
            Server newServer;
            while (++i < readParam.size() && readParam.at(i).compare(0, 6, "server") != 0){
                if (!(readParam.at(i).compare(0, 6, "listen")))
                    newServer.port = std::stoi(readParam.at(i).substr(7));
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

//save param of location
int Config::configLocation(int index, std::vector<std::string> readParam){
    (void)readParam;
    return index;
}

// save .conf
std::vector<std::string> Config::readConf(std::string conf) {
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