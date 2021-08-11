#ifndef URI_HPP
#define URI_HPP

/**
         foo://example.com:8042/over/there?name=ferret#nose
         \_/   \______________/\_________/ \_________/ \__/
          |           |            |            |        |
       scheme     authority       path        query   fragment
          |   _____________________|__
         / \ /                        \
         urn:example:animal:ferret:nose
**/

/* Library: */
#include <string>
#include <iostream>
#include <vector>
/* Includes: */

class URI {
	public:
		std::string scheme;
		std::string authority;
		std::string path;
		std::string query;
		std::vector<std::string> queryName;
		std::vector<std::string> queryValue;
		std::string fragment;
	
	public:
		URI() {};
		URI(std::string uri);
		void parseQuery();
};

#endif