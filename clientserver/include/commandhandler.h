#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>
#include "messagehandler.h"

class CommandHandler : public MessageHandler {

    public:
        CommandHandler();
        CommandHandler(const std::shared_ptr<Connection>& connection);
        virtual ~CommandHandler() = default;

        virtual auto listGroups() const -> Status = 0;
        virtual auto createGroup() const -> Status = 0;
        virtual auto deleteGroup() const -> Status = 0;

        virtual auto listArticles() const -> Status = 0;
        virtual auto createArticle() const -> Status = 0;
        virtual auto deleteArticle() const -> Status = 0;
        virtual auto getArticle() const -> Status = 0;
};

#endif