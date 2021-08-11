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

/* Includes: */

class URI {
	public:
		std::string scheme;
		std::string authority;
		std::string path;
		std::string query;
		std::string fragment;
	
	public:
		URI(std::string uri);
};

#endif