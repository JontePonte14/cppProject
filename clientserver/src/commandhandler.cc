#include "commandhandler.h"
#include "messagehandler.h"
#include "protocol.h"
#include <iostream>

CommandHandler::CommandHandler()
    : MessageHandler()
{
}

CommandHandler::CommandHandler(const std::shared_ptr<Connection>& connection)
    : MessageHandler(connection)
{
}

/*
void CommandHandler::checkCode(const Protocol code, const Protocol protocol, const string& method) {

}

void CommandHandler::checkCondition(const bool condition, const string& method, const string& message) {
    
}
*/