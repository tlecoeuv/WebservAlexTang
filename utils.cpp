#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>

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
