#ifndef UTILS_HPP
# define UTILS_HPP

#include <vector>

extern bool		g_running;

std::string					get_time(void);
size_t						get_time_diff(std::string time_string);
std::vector<std::string>	split(std::string str, std::string delimiter);

#endif