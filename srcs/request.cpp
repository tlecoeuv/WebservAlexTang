#include "../includes/Request.hpp"

// Constructor request
Request::Request(){}

bool Request::cmd(std::string buf){
    if (buf.size() && !buf.compare(0, 4, "exit"))
        exit(0);
    else
        return 1;   
}

void Request::fill(std::string buf){
    std::vector<std::string> readHeader;

    std::cout << buf << std::endl << std::endl;
    readHeader = fileToVector(buf, 0);
    for (size_t i = 0; i < readHeader.size() ; ){
        if (!(readHeader.at(i).compare(0, 3, "GET")))
            this->method = readHeader.at(i);
        else if (!(readHeader.at(i).compare(0, 5, "Host:")))
            this->host = readHeader.at(i).substr(6);
        else if (!(readHeader.at(i).compare(0, 11, "Connection:")))
            this->connection = readHeader.at(i).substr(12);
        else if (!(readHeader.at(i).compare(0, 11, "User-Agent:")))
            this->userAgent = readHeader.at(i).substr(12);
        else if (!(readHeader.at(i).compare(0, 7, "Accept:")))
            this->accept = readHeader.at(i).substr(8);
        else if (!(readHeader.at(i).compare(0, 8, "Referer:")))
            this->referer = readHeader.at(i).substr(9);
        else if (!(readHeader.at(i).compare(0, 16, "Accept-Encoding:")))
            this->acceptEncoding = readHeader.at(i).substr(17);
        else if (!(readHeader.at(i).compare(0, 16, "Accept-Language:")))
            this->acceptLanguage = readHeader.at(i).substr(17);
    }
}