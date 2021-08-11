#include "Uri.hpp"

URI::URI(std::string uri){
	size_t i = 0;
	for (size_t j = 0; j < uri.size(); j++) {
		if (path.size() == 0 && (uri.at(j) == '?'|| j + 1 == uri.size())) {
			path = uri.substr(i, j - i);
			i = j + 1;
		}
		if (path.size() && query.size() == 0 && (uri.at(j) == '#' || j + 1 == uri.size())) {
			query = uri.substr(i, j - i);
			if (uri.at(j) == '#')
				fragment = uri.substr(j, uri.size() - j);
			break;
		}
	}
	std::cout << "Path: " << path << std::endl;
	std::cout << "Query: " << query << std::endl;
	std::cout << "Fragment: " << fragment << std::endl;
}