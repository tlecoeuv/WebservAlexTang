#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>

#include "../includes/config.hpp"

void error(std::exception& ex)
{
	std::cerr << "Error " << ex.what() << std::endl;
}

int main(int argc, char **argv){

    if (argc != 2)
        exit(0);
    try {
        Config server(argv[1]);
    }
    catch(std::exception& ex) {
		error(ex);
	}
}
