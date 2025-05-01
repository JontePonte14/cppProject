#include "servercommandhandler.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include <iostream>

ServerCommandHandler::ServerCommandHandler() 
    : CommandHandler() {
}

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Connection>& connection)
    : CommandHandler(connection) {
}

void ServerCommandHandler::processRequest() {
    Protocol protocol = receiveProtocol();

    std::cout << "Server received an " << to_string(protocol) << " protocol" << std::endl;
    switch (protocol) {
        case Protocol::COM_LIST_NG:
            listGroups();
            break;
        case Protocol::COM_CREATE_NG:
            createGroup();
            break;
        case Protocol::COM_DELETE_NG:
            deleteGroup();
            break;
        case Protocol::COM_LIST_ART:
            listArticles();
            break;
        case Protocol::COM_CREATE_ART:
            createArticle();
            break;
        case Protocol::COM_DELETE_ART:
            deleteArticle();
            break;
        case Protocol::COM_GET_ART:
            getArticle();
            break;
        default:
            throw ConnectionClosedException();
    }
}

void ServerCommandHandler::processRequest(const std::shared_ptr<Connection>& connection) {
    setConnection(connection);
    processRequest();
}

void ServerCommandHandler::listGroups() {
    auto protocol = verifyProtocol(Protocol::COM_END);
}

void ServerCommandHandler::createGroup() {

}

void ServerCommandHandler::deleteGroup() {

}

void ServerCommandHandler::listArticles() {

}

void ServerCommandHandler::createArticle() {

}

void ServerCommandHandler::deleteArticle() {

}

void ServerCommandHandler::getArticle() {

}

auto ServerCommandHandler::verifyProtocol(const Protocol expected) -> Expected<Protocol, Error>
{
    Protocol protocol = receiveProtocol();
    std::cout << "Server received an " << to_string(protocol) << " protocol, expected " << to_string(expected) << std::endl;

    if (protocol == expected) {
        return protocol;
    }

    else return Error::ProtocolViolation;
}
