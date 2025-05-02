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

        virtual auto listGroups() -> Status = 0;
        virtual auto createGroup() -> Status = 0;
        virtual auto deleteGroup() -> Status = 0;

        virtual auto listArticles() -> Status = 0;
        virtual auto createArticle() -> Status = 0;
        virtual auto deleteArticle() -> Status = 0;
        virtual auto getArticle() -> Status = 0;
    
    /*
    protected:
        void checkCode(const Protocol received, const Protocol expected, const string& method);
        void checkCondition(const bool condition, const string& method, const string& message);
    */
};

#endif