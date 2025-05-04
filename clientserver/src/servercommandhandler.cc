#include "servercommandhandler.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include <iostream>

// Macros for now, maybe change to lambdas later

#define RETURN_IF_FAILED(expr)              \
    do {                                    \
        Status _status = (expr);            \
        if (_status != Status::Success)     \
            return _status;                 \
    } while (0)
   
#define RETURN_IF_ERROR(expr) \
    { auto _s = (expr); if (!_s) return _s.error(); }

#define ASSIGN_OR_RETURN(var, expr)                                  \
    auto _result_##__LINE__ = (expr);                                \
    if (!_result_##__LINE__)                                         \
        return _result_##__LINE__.error();                           \
    decltype(auto) var = std::move(*_result_##__LINE__);


ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Database>& database) 
    : CommandHandler(), database(database) {
}

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Database>& database, const std::shared_ptr<Connection>& connection)
    : CommandHandler(connection), database(database) {
}

auto ServerCommandHandler::processRequest() noexcept -> Status {
    Protocol protocol = receiveProtocol();

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
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_LIST_NG));

    const auto groups = { "GroupA", "GroupB", "GroupC" };
    uint id = 0;

    RETURN_IF_FAILED(sendIntParameter(groups.size(), "# of groups"));

    for (const auto& group : groups) {
        RETURN_IF_FAILED(sendIntParameter(id++, "ID"));
        RETURN_IF_FAILED(sendStringParameter(group, "Name"));
    }

    return Status::ConnectionClosed;
}

auto ServerCommandHandler::createGroup() -> Status {
    ASSIGN_OR_RETURN(string_p, receiveStringParameter());
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));

    if (database->makeGroup(string_p)) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    } else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_ALREADY_EXISTS));
    }
    
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::deleteGroup() -> Status {
    ASSIGN_OR_RETURN(num_p, receiveInt());
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_DELETE_NG));

    if(true) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    } else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::listArticles() -> Status {
    ASSIGN_OR_RETURN(num_p, receiveIntParameter())
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_LIST_ART));
}

auto ServerCommandHandler::createArticle() -> Status {

}

auto ServerCommandHandler::deleteArticle() -> Status {

}

auto ServerCommandHandler::getArticle() -> Status {

}

auto ServerCommandHandler::verifyProtocol(const Protocol expected) -> Expected<Protocol, Status>
{
    Protocol protocol = receiveProtocol();

    if (protocol == expected) {
        return protocol;
    }

    else return Status::ProtocolViolation;
}
