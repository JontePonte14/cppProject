#ifndef SERVER_COMMAND_HANDLER_H
#define SERVER_COMMAND_HANDLER_H

#include "commandhandler.h"
#include "database.h"
#include <memory>

class ServerCommandHandler : public CommandHandler {

    public:
        ServerCommandHandler(const std::shared_ptr<Database>& database);
        ServerCommandHandler(const std::shared_ptr<Database>& database, const std::shared_ptr<Connection>& connection);
        virtual ~ServerCommandHandler() = default;

        [[nodiscard]] auto processRequest() noexcept -> Status;
        [[nodiscard]] auto processRequest(const std::shared_ptr<Connection>& connection) noexcept -> Status;

        auto listGroups() -> Status override;
        auto createGroup() -> Status override;
        auto deleteGroup() -> Status override;

        auto listArticles() -> Status override;
        auto createArticle() -> Status override;
        auto deleteArticle() -> Status override;
        auto getArticle() -> Status override;

    private:
        std::shared_ptr<Database> database;

        auto sendProtocol(const Protocol protocol) noexcept -> bool override;
        [[nodiscard]] auto verifyProtocol(const Protocol expected) -> Expected<Protocol, Status>;
};

#endif