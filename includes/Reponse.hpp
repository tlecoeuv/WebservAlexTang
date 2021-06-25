#ifndef REPONSE_HPP
# define REPONSE_HPP

#include <iostream>
#include <vector>
#include <string>

#include "Request.hpp"

class 	Reponse {
    public:
        std::string header;

    public:
        Reponse(){};
		void makeReponse(Request request);
};

#endif
