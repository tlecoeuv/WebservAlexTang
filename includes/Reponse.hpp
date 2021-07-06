#ifndef REPONSE_HPP
# define REPONSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Request.hpp"
#include "Location.hpp"

class 	Reponse {
    public:
        std::string header;

    public:
        Reponse(){};
        Reponse(Request request, std::map<std::string, Location> locations);
		void makeReponse(Request request, std::map<std::string, Location> locations);
        void get(std::map<std::string, std::string> info, Request request);
        std::string _getMIMEType(std::string filename);
        std::string readFile(std::string file);
};

#endif
