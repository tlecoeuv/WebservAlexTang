#ifndef CGI_HPP
# define CGI_HPP

#include <string>

class CGI {
	public:
		std::string cgiPath;
		std::string ressourcePath;
		CGI(std::string cp, std::string rp);
		~CGI();

	private:

};

#endif