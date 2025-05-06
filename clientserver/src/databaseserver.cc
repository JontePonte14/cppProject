#include "databaseserver.h"
#include "connectionclosedexception.h"
#include <iostream>
#include "protocol.h"

DatabaseServer::DatabaseServer(const int port, const bool run)
    : Server(port), database(std::make_shared<Interface>()), handler(database)
{
    std::cout << "Database server initialized with port " << port << std::endl;

    if (run) {
        start();
    }
}

void DatabaseServer::start() {

    if (isReady()) {
        std::cout << "Database server is running" << std::endl;

        while (true) {
            serveConnection();
        }

        std::cout << "Database server has closed" << std::endl;
    } 
    
    else {
        std::cout << "Database failed to start" << std::endl;
    }
}

void DatabaseServer::serveConnection() {
    auto connection = waitForActivity();

    if(connection) {
        if (handler.processRequest(connection) != Status::Success) {
            deregisterConnection(connection);
            std::cout << "Client closed connection" << std::endl;
        }
    } else {
        connection = std::make_shared<Connection>();
        registerConnection(connection);
        std::cout << "A new client connected" << std::endl;
    }
}
