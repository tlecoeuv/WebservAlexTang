#ifndef HEADER_HPP
#define HEADER_HPP
#include <string>
#include <vector>

std::vector<std::string> fileToVector(std::string file);
//https://maximilienandile.github.io/2016/09/30/Comprendre-les-headers-d-une-requete-HTTP/
class Header {
    public:
        std::string method;
        std::string host;
        std::string connection;
        std::string cacheControl;
        std::string upgradeInsecureRequests;
        std::string userAgent;
        std::string referer;
        std::string accept;
        std::string acceptEncoding;
        std::string acceptLanguage;
        std::string cookie;
        std::string ifModifiedSince;

        Header(std::string requestHeader);
        ~Header();
};

#endif