#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include "Header.hpp"

class 	Request {
    private:
        Header requestHeader;
        bool cmd(std::string buf);
        std::string doGet();
    public:
        Request(std::string buf);
        std::string Response();
};

#endif
