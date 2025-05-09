#include "databaseserver.h"
#include <iostream>
#include "logger.h"

int main(int argc, char* argv[])
{
	if (argc < 1) {
		std::cerr << "Usage: test port-number [logLevel]*" << std::endl;
		exit(1);
	}

	int port = -1;
	try {
			port = std::stoi(argv[1]);
	} catch (std::exception& e) {
			std::cerr << "Wrong port number. " << e.what() << std::endl;
			exit(2);
	}

	for(int i = 1; i < argc; ++i) {
		std::string logLevel = argv[i];
		std::cout << logLevel << std::endl;
		Logger::setLogLevel(logLevel, true);
	}

	/*
	std::cout << "Size of bool: " << sizeof(bool) << std::endl;
	std::cout << "Size of char: " << sizeof(char) << std::endl;
	std::cout << "Size of char&: " << sizeof(char&) << std::endl;
	std::cout << "Size of char*: " << sizeof(char*) << std::endl;
	std::cout << "Size of shared int*: " << sizeof(std::shared_ptr<int>) << std::endl;
	std::cout << "Size of connection: " << sizeof(Connection) << std::endl;
	std::cout << "Size of shared connection*: " << sizeof(std::shared_ptr<Connection>) << std::endl;
	std::cout << "Size of shared& connection*: " << sizeof(std::shared_ptr<Connection>&) << std::endl;
	std::cout << "Size int " << sizeof(int) << std::endl;
	std::cout << "Size int&: " << sizeof(int&) << std::endl;
	std::cout << "Size int*: " << sizeof(int*) << std::endl;

	std::cout << "Size string " << sizeof(std::string) << std::endl;
	std::cout << "Size string&: " << sizeof(const std::string&) << std::endl;
	std::cout << "Size string*: " << sizeof(std::string*) << std::endl;
	*/

	DatabaseServer server(port, true);

	return 0;
}
