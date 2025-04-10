#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>
#include "messagehandler.h"

enum class Protocol;

class CommandHandler final {

    using string = std::string;
    friend class DatabaseServer;

    public:
        CommandHandler();
        ~CommandHandler() = default;

        auto listGroups() -> std::vector<string>;
        auto createGroup(const string&) -> int;
        auto deleteGroup(const int) -> int;

        auto listArticles(const int) -> std::vector<string>;
        auto createArticle(const int, const string&, const string&) -> int;
        auto deleteArticle(const int, const int) -> int;
        auto getArticle(const int, const int) -> std::vector<string>;

        
    private:
        MessageHandler messageHandler;

        void checkCode(const string&, const Protocol, const int);
        void checkCondition(const bool, const string&, const string&);
        void setConnection(const std::shared_ptr<Connection>&);
};

#endif