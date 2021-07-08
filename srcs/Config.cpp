#include "../includes/Config.hpp"

// Constructor config
Config::Config(std::string conf){
    parametre(conf);
	checkConfig();
}

//save param of server
void Config::parametre(std::string conf){
    std::vector<std::string> readParam;

    readParam = fileToVector(conf, 1);
    for (size_t i = 0; i < readParam.size() ; ){
        if (readParam.at(i).compare(0, 6, "server") == 0){
			if (readParam.at(i).size() < 8 && readParam.at(i)[readParam.at(i).size() - 1] != '{')
				throw std::out_of_range("No server");
            Server newServer;
            while (++i < readParam.size() && readParam.at(i).compare(0, 6, "server") != 0){
                if (!(readParam.at(i).compare(0, 6, "listen"))){
					if (readParam.at(i).size() > 6  && readParam.at(i).substr(7).find_first_not_of("0123456789") == std::string::npos)
                    	 newServer.port = std::stoi(readParam.at(i).substr(7));
					else
						throw std::out_of_range("Listen has no value");
				}
                else if (!(readParam.at(i).compare(0, 5, "error"))){
					if (readParam.at(i).size() > 5)
                    	newServer.error = readParam.at(i).substr(6);
					else
						throw std::out_of_range("Error has no value");
				}
                else if (!(readParam.at(i).compare(0, 4, "name"))){
					if (readParam.at(i).size() > 4)
                    	newServer.name = readParam.at(i).substr(5);
					else
						throw std::out_of_range("Name has no value");
				}
                else if (!(readParam.at(i).compare(0, 4, "host"))){
					if (readParam.at(i).size() > 4)
                    	newServer.name = readParam.at(i).substr(5);
					else
						throw std::out_of_range("Host has no value");
				}
                else if (!(readParam.at(i).compare(0, 8, "location"))){
					if (readParam.at(i).size() > 8 && readParam.at(i)[readParam.at(i).size() - 1] == '{')
                    	i = configLocation(i, readParam, newServer);
					else
						throw std::out_of_range("No location");
				}
				else if (i >= readParam.size() || readParam.at(i).compare(0, 1, "}")) {
					std::cout << "Error: " << readParam.at(i) << std::endl;
					throw std::out_of_range("Wrong parameter");
				}
            }
            confServer.push_back(newServer);
        }
    }
}

//save param of location
int Config::configLocation(int index, std::vector<std::string> readParam, Server &newServer){
    Location newLocation;

	std::string path;
	if (!readParam.at(index).compare(9, 2, "/ ")){
		path = "/";
	}
	else if (!readParam.at(index).compare(9, 1, "/")){
		path = readParam.at(index).substr(9);
		path.erase(path.end() - 1, path.end());
	}
	else 
		throw std::out_of_range("No location path");
    while (readParam.at(++index).size() && readParam.at(index).compare(0, 1, "}")){
        if ((!readParam.at(index).compare(0, 5, "index"))){
			if (readParam.at(index).size() > 5)
            	newLocation.index = readParam.at(index).substr(6);
			else
				throw std::out_of_range("No index");
		}
        else if ((!readParam.at(index).compare(0, 10, "auto_index"))){
			if (readParam.at(index).size() > 10)
            	newLocation.auto_index = std::stoi(readParam.at(index).substr(11));
			else
				throw std::out_of_range("No auto_index");
		}
        else if ((!readParam.at(index).compare(0, 4, "root"))){
			if (readParam.at(index).size() > 4)
            	newLocation.root = readParam.at(index).substr(5);
			else
				throw std::out_of_range("No root");
		}
        else if ((!readParam.at(index).compare(0, 3, "cgi"))){
			if (readParam.at(index).size() > 3)
            	newLocation.cgi = readParam.at(index).substr(4);
			else
				throw std::out_of_range("No cgi");
		}
        else if ((!readParam.at(index).compare(0, 8, "cgi_path"))){
			if (readParam.at(index).size() > 8)
            	newLocation.cgi_path = readParam.at(index).substr(9);
			else
				throw std::out_of_range("No cgi_path");
		}
        else if ((!readParam.at(index).compare(0, 8, "max_body"))){
			if (readParam.at(index).size() > 8)
            	newLocation.max_body = readParam.at(index).substr(9);
			else
				throw std::out_of_range("No max_body");
		}
        else if ((!readParam.at(index).compare(0, 4, "auth"))){
			if (readParam.at(index).size() > 4)
            	newLocation.auth = readParam.at(index).substr(5);
			else
				throw std::out_of_range("No auth");
		}
        else if ((!readParam.at(index).compare(0, 6, "method"))){
			if (readParam.at(index).size() > 6)
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
			else
				throw std::out_of_range("No method");
            
        }
        else {
            std::cout << "Error: " << readParam.at(index) << std::endl;
            throw std::out_of_range("Wrong Location");
        }
    }
    newServer.locations[path] = newLocation;
    return index;
}

std::vector<Server> Config::getServer(){
	return confServer;
}

void Config::checkConfig(){
	if (!confServer.size())
		throw std::out_of_range("No Server");
	for (size_t i = 0; i < confServer.size(); ++i){

	}
}