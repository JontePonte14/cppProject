#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include "server.h"
#include "interface.h"
#include "servercommandhandler.h"
#include "database.h"

class DatabaseServer final : public Server {

    public:
        explicit DatabaseServer(const int port, const bool run = false);
        ~DatabaseServer() = default;

        void start();

    private:
        std::shared_ptr<Interface> database;
        ServerCommandHandler handler;

        void serveConnection();
};

#endif