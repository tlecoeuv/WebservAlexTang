#ifndef REPONSE_HPP
# define REPONSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Request.hpp"
#include "Location.hpp"

class 	Reponse {
    public:
        std::string header;

    public:
        Reponse(){};
		void makeReponse(Request request, std::map<std::string, Location> locations);
        void get(std::map<std::string, std::string> info, Request request);
        std::string _getMIMEType(std::string filename);
};

#endif
