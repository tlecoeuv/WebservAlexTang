#include "../includes/CGI.hpp"

CGI::CGI(std::string cp, std::string rp, Request req) {
	cgiPath = cp;
	ressourcePath = rp;
	request = req;
}
