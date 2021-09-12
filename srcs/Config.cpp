#include "Config.hpp"

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
				throw std::invalid_argument("No server");
			Server newServer;
			newServer.port = -1;
			while (++i < readParam.size() && readParam.at(i).compare(0, 6, "server") != 0){
				if (!(readParam.at(i).compare(0, 7, "listen "))){
					if (newServer.port != -1)
						throw std::invalid_argument("Port is set several times");
					if (readParam.at(i).size() > 6 && readParam.at(i).substr(7).find_first_not_of("0123456789") == std::string::npos){
						newServer.port = std::stoi(readParam.at(i).substr(7));
						for (size_t j = 0; j < confServer.size() ; j++){
							if (newServer.port == confServer.at(j).port)
								throw std::invalid_argument("Same port has already been set");
						}
					}
					else
						throw std::invalid_argument("Server Port has invalid value");
				}
				else if (!(readParam.at(i).compare(0, 6, "error "))){
					if (newServer.error.size() != 0)
						throw std::invalid_argument("Error file is set several times");
					if (readParam.at(i).size() > 5)
						newServer.error = readParam.at(i).substr(6);
					else
						throw std::invalid_argument("Error file has no value");
				}
				else if (!(readParam.at(i).compare(0, 5, "name "))){
					if (newServer.name.size() != 0)
						throw std::invalid_argument("Name is set several times");
					if (readParam.at(i).size() > 4)
						newServer.name = readParam.at(i).substr(5);
					else
						throw std::invalid_argument("Name has no value");
				}
				else if (!(readParam.at(i).compare(0, 5, "host "))){
					if (newServer.host.size() != 0)
						throw std::invalid_argument("host is set several times");
					if (readParam.at(i).size() > 4)
						newServer.host = readParam.at(i).substr(5);
					else
						throw std::invalid_argument("Host has no value");
				}
				else if (!(readParam.at(i).compare(0, 9, "location "))){
					if (readParam.at(i).size() > 8 && readParam.at(i)[readParam.at(i).size() - 1] == '{')
						i = configLocation(i, readParam, newServer);
					else
						throw std::invalid_argument("No location");
				}
				else if (i >= readParam.size() || readParam.at(i).compare(0, 1, "}")) 
					throw std::invalid_argument("invalid argument " + readParam.at(i));
			}
			if (newServer.name.size() == 0)
				throw std::invalid_argument("Server has no name");
			if (newServer.port == -1)
				throw std::invalid_argument("Server has no port");
			if (newServer.host.size() == 0)
				throw std::invalid_argument("Server has no host");
			if (newServer.error.size() == 0)
				throw std::invalid_argument("Server has no error file");
			if (newServer.locations.size() == 0)
				throw std::invalid_argument("Server " + newServer.name + " has no location");
			confServer.push_back(newServer);
		}
	}
}

//save param of location
int Config::configLocation(int index, std::vector<std::string> readParam, Server &newServer){
	Location newLocation;

	newLocation.redirection.first = 0;
	std::string path;
	if (!readParam.at(index).compare(9, 2, "/ ")){
		path = "/";
	}
	else if (!readParam.at(index).compare(9, 1, "/")){
		path = readParam.at(index).substr(9);
		path.erase(path.end() - 2, path.end());
	}
	else 
		throw std::out_of_range("No location path");
	while (readParam.at(++index).size() && readParam.at(index).compare(0, 1, "}")){
		if ((!readParam.at(index).compare(0, 5, "index"))){
			if (newLocation.index.size() != 0)
				throw std::invalid_argument("index is set several times");
			if (readParam.at(index).size() > 5)
				newLocation.index = readParam.at(index).substr(6);
			else
				throw std::invalid_argument("No index");
		}
		else if ((!readParam.at(index).compare(0, 11, "auto_index "))){
			if (readParam.at(index).size() > 10)
				newLocation.auto_index = std::stoi(readParam.at(index).substr(11));
			else
				throw std::invalid_argument("No auto_index");
		}
		else if ((!readParam.at(index).compare(0, 5, "root "))){
			if (newLocation.root.size() != 0)
				throw std::invalid_argument("root is set several times");
			if (readParam.at(index).size() > 4)
				newLocation.root = readParam.at(index).substr(5);
			else
				throw std::invalid_argument("No root");
		}
		else if ((!readParam.at(index).compare(0, 4, "cgi "))){
			if (newLocation.cgi.size() != 0)
				throw std::invalid_argument("cgi is set several times");
			if (readParam.at(index).size() > 3)
				newLocation.cgi = readParam.at(index).substr(4);
			else
				throw std::invalid_argument("No cgi");
		}
		else if ((!readParam.at(index).compare(0, 9, "cgi_path "))){
			if (newLocation.cgi_path.size() != 0)
				throw std::invalid_argument("cgi_path is set several times");
			if (readParam.at(index).size() > 8)
				newLocation.cgi_path = readParam.at(index).substr(9);
			else
				throw std::invalid_argument("No cgi_path");
		}
		else if ((!readParam.at(index).compare(0, 9, "max_body "))){
			if (newLocation.max_body.size() != 0)
				throw std::invalid_argument("max_body is set several times");
			if (readParam.at(index).size() > 8)
				newLocation.max_body = readParam.at(index).substr(9);
			else
				throw std::invalid_argument("No max_body");
		}
		else if ((!readParam.at(index).compare(0, 7, "return "))){
			if (readParam.at(index).size() > 6){
				size_t i = 7;
				for (;i < readParam.at(index).size() && readParam.at(index).at(i) != ' '; i++)
					;
				if (readParam.at(index).substr(7, i - 7).find_first_not_of("0123456789") != std::string::npos)
					throw std::invalid_argument("Redirection code has invalid value");
				newLocation.redirection.first = std::stoi(readParam.at(index).substr(7, i - 7));
				if (i == readParam.at(index).size() && (newLocation.redirection.first == 301 || newLocation.redirection.first == 302 ||
					newLocation.redirection.first == 303 || newLocation.redirection.first == 307 || newLocation.redirection.first == 308))
					throw std::invalid_argument("Invalid argument in Redirection");
				if (newLocation.redirection.first != 204 && newLocation.redirection.first != 400 && newLocation.redirection.first != 402 &&
				newLocation.redirection.first != 403 && newLocation.redirection.first != 404 && newLocation.redirection.first != 405 &&
				newLocation.redirection.first != 406 && newLocation.redirection.first != 408 && newLocation.redirection.first != 410 &&
				newLocation.redirection.first != 411 && newLocation.redirection.first != 413 && newLocation.redirection.first != 416 &&
				newLocation.redirection.first != 500 && newLocation.redirection.first != 501 && newLocation.redirection.first != 502 &&
				newLocation.redirection.first != 503 && newLocation.redirection.first != 504 && newLocation.redirection.first != 307 &&
				newLocation.redirection.first != 308 && newLocation.redirection.first != 301 && newLocation.redirection.first != 302 &&
				newLocation.redirection.first != 303)
					throw std::invalid_argument("Redirection code has to be 204, 301, 302, 303, 307, 308, 400, 402 — 406, 408, 410, 411, 413, 416, and 500 — 504");
				if (i != readParam.at(index).size()){
					size_t j = i + 1;
					for (;i < readParam.at(index).size() && readParam.at(index).at(i) != ' '; i++)
						;
					newLocation.redirection.second = readParam.at(index).substr(j, i - j);
				}
				
			}
			else
				throw std::invalid_argument("No return");

		}
		else if ((!readParam.at(index).compare(0, 7, "method "))){
			if (readParam.at(index).size() > 6)
				for (size_t i = 7; readParam.at(index)[i] ;){
					std::string newMethod;
					size_t j = i;
					while(i < readParam.at(index).size() && readParam.at(index)[i] != ' ')
						i++;
					newMethod = readParam.at(index).substr(j, i - j);
					if (newMethod == "GET" || newMethod == "POST" || newMethod == "delete")
						newLocation.method.push_back(newMethod);
					else
						throw std::invalid_argument("Wrong method: " + newMethod);
					if (readParam.at(index).size() && readParam.at(index)[i] == ' ')
						i++;
				}
			else
				throw std::invalid_argument("No method");
		}
		else {
			throw std::invalid_argument("invalid argument in Location " + path);
		}
	}
	if (newLocation.method.size() == 0 && newLocation.redirection.first == 0)
		throw std::invalid_argument("Missing method in Location " + path);
	if (newLocation.root.size() == 0 && newLocation.redirection.first == 0)
		throw std::invalid_argument("Missing root in Location " + path );
	newServer.locations[path] = newLocation;
	return index;
}

std::vector<Server> Config::getServer(){
	return confServer;
}

void Config::checkConfig(){
	if (!confServer.size())
		throw std::invalid_argument("Missing Server");
	for (size_t i = 0; i < confServer.size(); ++i){

	}
}
