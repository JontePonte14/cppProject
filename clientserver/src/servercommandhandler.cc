#include "servercommandhandler.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include <iostream>

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Database>& database) 
    : CommandHandler(), database(database) {
}

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Database>& database, const std::shared_ptr<Connection>& connection)
    : CommandHandler(connection), database(database) {
}

auto ServerCommandHandler::processRequest() noexcept -> Status {
    Protocol protocol = receiveProtocol();

    std::cout << "Server received an " << to_string(protocol) << " protocol" << std::endl;

    switch (protocol) {
        case Protocol::COM_LIST_NG:
            return listGroups();
            break;
        case Protocol::COM_CREATE_NG:
            return createGroup();
            break;
        case Protocol::COM_DELETE_NG:
            return deleteGroup();
            break;
        case Protocol::COM_LIST_ART:
            return listArticles();
            break;
        case Protocol::COM_CREATE_ART:
            createArticle();
            break;
        case Protocol::COM_DELETE_ART:
            return deleteArticle();
            break;
        case Protocol::COM_GET_ART:
            return getArticle();
            break;
        default:
            return Status::ProtocolViolation;
    }
}

auto ServerCommandHandler::processRequest(const std::shared_ptr<Connection>& connection) noexcept -> Status {
    setConnection(connection);
    return processRequest();
}

auto ServerCommandHandler::listGroups() -> Status {
    auto protocol = verifyProtocol(Protocol::COM_END);

    if (!protocol) {
        return protocol.error();
    }

    if (sendProtocol(Protocol::ANS_LIST_NG)) {
        const auto groups = database->listGroup();

        if (!sendInt(groups.size())) {
            return Status::FailedTransfer;
        }

        for (const auto& group : groups) {
            /*if (sendStringParameter(group)) {
                return Status::ConnectionClosed;
            }*/
        }

        if (!sendProtocol(Protocol::ANS_END)) {
            return Status::FailedTransfer;
        }

        return Status::Success;
    }

    else {
        return Status::ConnectionClosed;
    }
}

auto ServerCommandHandler::createGroup() -> Status {
    const auto string_p = receiveStringParameter();

    if (!string_p) {
        return string_p.error();
    }

    auto protocol = verifyProtocol(Protocol::COM_END);

    if (!protocol) {
        return protocol.error();
    }

    if (!database->makeGroup(*string_p)) {
        return Status::InvalidArguments; // TEMP
    }
    
}

auto ServerCommandHandler::deleteGroup() -> Status {

}

auto ServerCommandHandler::listArticles() -> Status {

}

auto ServerCommandHandler::createArticle() -> Status {

}

auto ServerCommandHandler::deleteArticle() -> Status {

}

auto ServerCommandHandler::getArticle() -> Status {

}

auto ServerCommandHandler::sendProtocol(const Protocol protocol) noexcept -> bool {
    std::cout << "Served sent a " << to_string(protocol) << " protocol" << std::endl;
    return MessageHandler::sendProtocol(protocol);
}

auto ServerCommandHandler::verifyProtocol(const Protocol expected) -> Expected<Protocol, Status>
{
    Protocol protocol = receiveProtocol();
    std::cout << "Server received an " << to_string(protocol) << " protocol, expected " << to_string(expected) << std::endl;

    if (protocol == expected) {
        return protocol;
    }

    else return Status::ProtocolViolation;
}
