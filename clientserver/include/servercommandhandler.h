#ifndef SERVER_COMMAND_HANDLER_H
#define SERVER_COMMAND_HANDLER_H

#include "commandhandler.h"
#include "interface.h"
#include <memory>

class ServerCommandHandler : public CommandHandler {

    public:
        ServerCommandHandler(const std::shared_ptr<Interface>& database);
        ServerCommandHandler(const std::shared_ptr<Interface>& database, const std::shared_ptr<Connection>& connection);
        virtual ~ServerCommandHandler() = default;

        [[nodiscard]] auto processRequest() const noexcept -> Status;
        [[nodiscard]] auto processRequest(const std::shared_ptr<Connection>& connection) const noexcept -> Status;

        auto listGroups() const -> Status override;
        auto createGroup() const -> Status override;
        auto deleteGroup() const -> Status override;

        auto listArticles() const -> Status override;
        auto createArticle() const -> Status override;
        auto deleteArticle() const -> Status override;
        auto getArticle() const -> Status override;
    
        auto changeDatabase() const -> Status override;

    private:
        std::shared_ptr<Interface> database;
};

#endif