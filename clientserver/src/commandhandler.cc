#include "commandhandler.h"
#include "messagehandler.h"
#include "protocol.h"
#include <iostream>

CommandHandler::CommandHandler()
    : messageHandler()
{
    std::cout << "Command handler initialized" << std::endl;
}

auto CommandHandler::listGroups() -> std::vector<string>
{
    /*
    messageHandler.sendCode(Protocol::COM_LIST_NG);
    messageHandler.sendCode(Protocol::COM_END);
    
    const int code = messageHandler.receiveCode();
    checkCode("List groups", Protocol::ANS_LIST_NG, code);

    const int nbrGroups = messageHandler.receiveIntParameter();
    checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");

    int groupIds[nbrGroups];
    */
    return std::vector<string>();
}

auto CommandHandler::createGroup(const string &) -> int
{
    return 0;
}

auto CommandHandler::deleteGroup(const int) -> int
{
    return 0;
}

auto CommandHandler::listArticles(const int) -> std::vector<string>
{
    return std::vector<string>();
}

auto CommandHandler::createArticle(const int, const string &, const string &) -> int
{
    return 0;
}

auto CommandHandler::deleteArticle(const int, const int) -> int
{
    return 0;
}

auto CommandHandler::getArticle(const int, const int) -> std::vector<string>
{
    return std::vector<string>();
}

void CommandHandler::setConnection(const std::shared_ptr<Connection>& connection)
{
    messageHandler.setConnection(connection);
}
