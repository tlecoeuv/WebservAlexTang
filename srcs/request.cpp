#include "../includes/Request.hpp"

// Constructor request
Request::Request(std::string buf){
    if (cmd(buf))
        requestHeader.fill(buf);
}

bool Request::cmd(std::string buf){

    if (buf.size() && !buf.compare(0, 4, "exit"))
        exit(0);
    else
        return 1;
    
}

std::string Request::doGet(){
    std::string reponse;
    return "";
}

std::string Request::Response(){
    if (!requestHeader.method.compare(0, 3, "GET"))
        return doGet();
    return "";
}