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

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define ASSIGN_OR_RETURN(var, expr)                              \
    auto CONCAT(_result_, __LINE__) = (expr);                    \
    if (!CONCAT(_result_, __LINE__))                             \
        return CONCAT(_result_, __LINE__).error();               \
    decltype(auto) var = std::move(*CONCAT(_result_, __LINE__));
    

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Interface>& database) 
    : CommandHandler(), database(database) {
}

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Interface>& database, const std::shared_ptr<Connection>& connection)
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

    const auto groups = database->listGroup();
    uint id = 0;

    RETURN_IF_FAILED(sendIntParameter(groups.size(), "# of groups"));

    for (const auto& group : groups) {
        RETURN_IF_FAILED(sendIntParameter(group.id, "group ID"));
        RETURN_IF_FAILED(sendStringParameter(group.name, "group name"));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));
    
    return Status::Success;
}

auto ServerCommandHandler::createGroup() -> Status {
    ASSIGN_OR_RETURN(string_p, receiveStringParameter());
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_CREATE_NG));
    
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
    ASSIGN_OR_RETURN(num_p, receiveIntParameter());
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
    ASSIGN_OR_RETURN(num_p, receiveIntParameter());
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_LIST_ART));

    const auto articles = database->listArticle(num_p);
    const auto n = articles.size();

    if(n == 0) {
        uint id = 0;

        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
        RETURN_IF_FAILED(sendIntParameter(num_p, "# of articles"));

        for(const auto& article : articles) {
            RETURN_IF_FAILED(sendIntParameter(article.id, "article ID"));
            RETURN_IF_FAILED(sendStringParameter(article.name, "article title"));
        }
    } else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::createArticle() -> Status {
    ASSIGN_OR_RETURN(id, receiveIntParameter());
    ASSIGN_OR_RETURN(title, receiveStringParameter());
    ASSIGN_OR_RETURN(author, receiveStringParameter());
    ASSIGN_OR_RETURN(text, receiveStringParameter());

    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_CREATE_ART));

    if (database->makeArticle(id, title, author, text)) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    } else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::deleteArticle() -> Status {
    ASSIGN_OR_RETURN(groupID, receiveIntParameter());
    ASSIGN_OR_RETURN(articleID, receiveIntParameter());
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_DELETE_ART));
    auto status = database->removeArticle(groupID, articleID);
    if (status == Database::RemoveStatus::SUCCESS) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    } else if (status == Database::RemoveStatus::GROUP_NOT_FOUND) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    } else if (status == Database::RemoveStatus::ARTICLE_NOT_FOUND) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_ART_DOES_NOT_EXIST));
    }


    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::getArticle() -> Status {
    ASSIGN_OR_RETURN(groupID, receiveIntParameter());
    ASSIGN_OR_RETURN(articleID, receiveIntParameter());
    RETURN_IF_ERROR(verifyProtocol(Protocol::COM_END));

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_GET_ART));
    Article article;
    try {
        article = database->getArticle(groupID, articleID);
    } catch (const std::exception& e) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
        return Status::FailedTransfer;
    }
 
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    RETURN_IF_FAILED(sendIntParameter(article.getID(), "article ID"));
    RETURN_IF_FAILED(sendStringParameter(article.getTitle(), "article title"));
    RETURN_IF_FAILED(sendStringParameter(article.getAuthor(), "article author"));
    RETURN_IF_FAILED(sendStringParameter(article.getBody(), "article body"));
    

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::verifyProtocol(const Protocol expected) -> Expected<Protocol, Status>
{
    Protocol protocol = receiveProtocol();

    if (protocol == expected) {
        return protocol;
    }

    else return Status::ProtocolViolation;
}
