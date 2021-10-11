#ifndef LOCATION_HPP
# define LOCATION_HPP

/* Includes: */
#include <vector>
#include <string>

struct Location {
	std::vector<std::string>	method;
	std::string					root;
	std::string					index;
	bool						auto_index;
	std::string					cgi;
	std::string					cgi_path;
	std::string					max_size;
	std::pair<int, std::string>	redirection;
};

#endif