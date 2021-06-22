#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include "Header.hpp"

class 	Request {
    private:
        Header requestHeader;
        bool cmd(std::string buf);
    public:
        Request(std::string buf);
};

#endif
