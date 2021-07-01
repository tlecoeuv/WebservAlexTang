#ifndef REPONSE_HPP
# define REPONSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Request.hpp"

class 	Reponse {
    public:
        std::string header;

    public:
        Reponse(){};
		void makeReponse(Request request);
        void get(std::map<std::string, std::string> info);
};

#endif
