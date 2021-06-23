#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> fileToVector(std::string file, int conf);
//https://maximilienandile.github.io/2016/09/30/Comprendre-les-headers-d-une-requete-HTTP/
class 	Request {
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

        bool cmd(std::string buf);
    public:
        Request();
        void fill(std::string buf);
};

#endif
