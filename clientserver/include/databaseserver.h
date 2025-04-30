#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include "server.h"
#include "database.h"
#include "commandhandler.h"

class DatabaseServer final : public Server {

    public:
        explicit DatabaseServer(int port);
        ~DatabaseServer() = default;

    private:
        CommandHandler commandHandler;
        Database database;
};

#endif