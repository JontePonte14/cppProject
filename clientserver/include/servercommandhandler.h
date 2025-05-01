#ifndef SERVER_COMMAND_HANDLER_H
#define SERVER_COMMAND_HANDLER_H

#include "commandhandler.h"

class ServerCommandHandler : public CommandHandler {

    public:
        ServerCommandHandler();
        ServerCommandHandler(const std::shared_ptr<Connection>& connection);
        virtual ~ServerCommandHandler() = default;

        void processRequest();
        void processRequest(const std::shared_ptr<Connection>& connection);

        void listGroups() override;
        void createGroup() override;
        void deleteGroup() override;

        void listArticles() override;
        void createArticle() override;
        void deleteArticle() override;
        void getArticle() override;

    private:
        auto verifyProtocol(const Protocol expected) -> Expected<Protocol, Error>;
};

#endif