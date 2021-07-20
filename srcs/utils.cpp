#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>

std::string trim(const std::string& str, const std::string& whitespace) {
	size_t begin = str.find_first_not_of(whitespace);
	if (begin == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(whitespace);
	size_t range = end - begin + 1;
	return str.substr(begin, range);
}

std::string reduce(const std::string& str)
{
	const std::string& fill = " ";
	const std::string& whitespace = " \t";
	std::string result = trim(str, whitespace);
	size_t begin = result.find_first_of(whitespace);
	while (begin != std::string::npos) {
		size_t end = result.find_first_not_of(whitespace, begin);
		size_t range = end - begin;
		result.replace(begin, range, fill);
		size_t newStart = begin + fill.length();
		begin = result.find_first_of(whitespace, newStart);
	}
	return result;
}

std::vector<std::string> fileToVector(std::string file, int conf) {
	std::string ret;
	std::vector<std::string> vector;
	std::ifstream myfile(file.c_str());

	if (conf && !myfile) {
		std::cerr << "Error" << std::endl;
		throw std::out_of_range("Wrong Path");
	}
	while (std::getline(myfile, ret, '\n')) {
		ret = reduce(ret);
		if (!ret.size())
			continue ;
		vector.push_back(ret);
	}
	return (vector);
}

std::vector<std::string>	split(std::string str, std::string delimiter)
{
	std::vector<std::string>	vec;
	size_t						pos = 0;
	std::string					token;

	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		if (token.size() > 0)
			vec.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	if (str.size() > 0)
		vec.push_back(str);
	return (vec);
}