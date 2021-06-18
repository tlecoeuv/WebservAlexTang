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
                //std::cout << "begin:\t\t" << readParam.at(i) << std::endl;
                if (!(readParam.at(i).compare(0, 6, "listen")))
                    newServer.port = std::stoi(readParam.at(i).substr(7));
                else if (!(readParam.at(i).compare(0, 5, "error")))
                    newServer.error = readParam.at(i).substr(6);
                else if (!(readParam.at(i).compare(0, 4, "name")))
                    newServer.name = readParam.at(i).substr(5);
                else if (!(readParam.at(i).compare(0, 4, "host")))
                    newServer.host = readParam.at(i).substr(5);
                else if (!(readParam.at(i).compare(0, 8, "location")))
                    i = configLocation(i, readParam, newServer);
            }
            confServer.push_back(newServer);
        }
    }
}

//save param of location
int Config::configLocation(int index, std::vector<std::string> readParam, Server &newServer){
    Location newLocation;
    while (readParam.at(++index).size() && readParam.at(index).compare(0, 1, "}")){
        if ((!readParam.at(index).compare(0, 5, "index")))
            newLocation.index = readParam.at(index).substr(6);
        else if ((!readParam.at(index).compare(0, 10, "auto_index")))
            newLocation.auto_index = std::stoi(readParam.at(index).substr(11));
        else if ((!readParam.at(index).compare(0, 4, "root")))
            newLocation.root = readParam.at(index).substr(5);
        else if ((!readParam.at(index).compare(0, 3, "cgi")))
            newLocation.cgi = readParam.at(index).substr(4);
        else if ((!readParam.at(index).compare(0, 8, "cgi_path")))
            newLocation.cgi_path = readParam.at(index).substr(9);
        else if ((!readParam.at(index).compare(0, 8, "max_body")))
            newLocation.max_body = readParam.at(index).substr(9);
        else if ((!readParam.at(index).compare(0, 4, "auth")))
            newLocation.auth = readParam.at(index).substr(5);
        else if ((!readParam.at(index).compare(0, 6, "method"))){
            for (size_t i = 7; readParam.at(index)[i] ;){
                std::string newMethod;
                size_t j = i;
                while(i < readParam.at(index).size() && readParam.at(index)[i] != ' ')
                    i++;
                newMethod = readParam.at(index).substr(j, i - j);
                newLocation.method.push_back(newMethod);
                if (readParam.at(index).size() && readParam.at(index)[i] == ' ')
                    i++;
            }
            
        }
        else {
            std::cout << "Error: " << readParam.at(index) << std::endl;
            throw std::out_of_range("Wrong Location");
        }
    }
    newServer.locations.push_back(newLocation);
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