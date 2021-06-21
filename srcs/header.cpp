#include "../includes/header.hpp"

Header::Header(std::string requestHeader){
    std::vector<std::string> readheader;

    readHeader = fileToVector(requestHeader);
}