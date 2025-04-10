#include "databaseserver.h"
#include <iostream>

DatabaseServer::DatabaseServer(int port)
    : Server(port), commandHandler(), database()
{
    std::cout << "Database server initialized" << std::endl;
}