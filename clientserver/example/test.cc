#include "databaseserver.h"
#include <iostream>

int main() {
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

	std::cout << sizeof(DatabaseServer) << std::endl;

	DatabaseServer server(10);
	
	return 0;
}
