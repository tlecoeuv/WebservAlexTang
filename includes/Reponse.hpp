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
#include <stdlib.h>
#include <stdio.h>

#include "Request.hpp"
#include "Location.hpp"

class 	Reponse {
    public:
        std::string header;

    public:
        Reponse(){};
        Reponse(Request request, std::map<std::string, Location> locations);
		void makeReponse(Request request, std::map<std::string, Location> locations);
        void methodGet(std::map<std::string, std::string> info, Request request);
		void methodPOST(std::map<std::string, std::string> info, Request request);
        void methodDelete(std::map<std::string, std::string> info);
        void methodError(std::map<std::string, std::string> info, int code);
		std::string bodyError(std::string oldBody, int code);
        std::string getMIMEType(std::string filename);
        std::string getMessage(size_t code);
        std::string readFile(std::string file);
};

#endif
