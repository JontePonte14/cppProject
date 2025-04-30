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

        virtual void listGroups() = 0;
        virtual void createGroup() = 0;
        virtual void deleteGroup() = 0;

        virtual void listArticles() = 0;
        virtual void createArticle() = 0;
        virtual void deleteArticle() = 0;
        virtual void getArticle() = 0;
    
    /*
    protected:
        void checkCode(const Protocol received, const Protocol expected, const string& method);
        void checkCondition(const bool condition, const string& method, const string& message);
    */
};

#endif