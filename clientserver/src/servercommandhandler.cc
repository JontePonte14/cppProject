#include "servercommandhandler.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include <iostream>

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Interface>& database) 
    : CommandHandler(), database(database) {
}

ServerCommandHandler::ServerCommandHandler(const std::shared_ptr<Interface>& database, const std::shared_ptr<Connection>& connection)
    : CommandHandler(connection), database(database) {
}

auto ServerCommandHandler::processRequest() const noexcept -> Status {
    ASSIGN_OR_RETURN(protocol, receiveProtocol());

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
        case Protocol::COM_CHANGE_DATABASE:
            return changeDatabase();
            break;
        default:
            return Status::ProtocolViolation;
    }

    return Status::Success;
}

auto ServerCommandHandler::processRequest(const std::shared_ptr<Connection>& connection) const noexcept -> Status {
    setConnection(connection);
    return processRequest();
}

auto ServerCommandHandler::listGroups() const -> Status {
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_LIST_NG));

    const auto groups = database->listGroup();

    RETURN_IF_FAILED(sendIntParameter(groups.size(), "# of groups"));

    for (const auto& group : groups) {
        RETURN_IF_FAILED(sendIntParameter(group.id, "group ID"));
        RETURN_IF_FAILED(sendStringParameter(group.name, "group name"));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));
    
    return Status::Success;
}

auto ServerCommandHandler::createGroup() const -> Status {
    ASSIGN_OR_RETURN(groupName, receiveStringParameter());
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_CREATE_NG));
    
    if (database->makeGroup(groupName)) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    } else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_ALREADY_EXISTS));
    }
    
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::deleteGroup() const -> Status {
    ASSIGN_OR_RETURN(groupID, receiveIntParameter());
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_DELETE_NG));

    const auto status = database->removeGroup(groupID);

    if(status == Database::RemoveStatus::SUCCESS) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    } 
    
    else if (status == Database::RemoveStatus::GROUP_NOT_FOUND) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    } 
    
    else {
        return Status::DatabaseError;
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::listArticles() const -> Status {
    ASSIGN_OR_RETURN(groupID, receiveIntParameter());
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_LIST_ART));

    const auto articles = database->listArticle(groupID);
    const auto n = articles.size();

    // Kanske bör ändras. Men har var felet för listArticles()
    if(n >= 0) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
        RETURN_IF_FAILED(sendIntParameter(n, "# of articles"));

        for(const auto& article : articles) {
            RETURN_IF_FAILED(sendIntParameter(article.id, "article ID"));
            RETURN_IF_FAILED(sendStringParameter(article.name, "article title"));
        }
    } 
    
    else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::createArticle() const -> Status {
    ASSIGN_OR_RETURN(id, receiveIntParameter());
    ASSIGN_OR_RETURN(title, receiveStringParameter());
    ASSIGN_OR_RETURN(author, receiveStringParameter());
    ASSIGN_OR_RETURN(text, receiveStringParameter());

    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_CREATE_ART));

    if (database->makeArticle(id, title, author, text)) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    }
    
    else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::deleteArticle() const -> Status {
    ASSIGN_OR_RETURN(groupID, receiveIntParameter());
    ASSIGN_OR_RETURN(articleID, receiveIntParameter());
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_DELETE_ART));

    const auto status = database->removeArticle(groupID, articleID);

    if (status == Database::RemoveStatus::SUCCESS) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    }
    
    else if (status == Database::RemoveStatus::GROUP_NOT_FOUND) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
    }
    
    else if (status == Database::RemoveStatus::ARTICLE_NOT_FOUND) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_ART_DOES_NOT_EXIST));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::getArticle() const -> Status {
    ASSIGN_OR_RETURN(groupID, receiveIntParameter());
    ASSIGN_OR_RETURN(articleID, receiveIntParameter());
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_GET_ART));

    const auto _article = database->getArticle(groupID, articleID);

    if (!_article) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_NG_DOES_NOT_EXIST));
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));
        return Status::DatabaseError;
    }

    const auto article = *_article;

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    //RETURN_IF_FAILED(sendIntParameter(article.getID(), "article ID"));
    RETURN_IF_FAILED(sendStringParameter(article.getTitle(), "article title"));
    RETURN_IF_FAILED(sendStringParameter(article.getAuthor(), "article author"));
    RETURN_IF_FAILED(sendStringParameter(article.getBody(), "article body"));
    
    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));

    return Status::Success;
}

auto ServerCommandHandler::changeDatabase() const -> Status {
    ASSIGN_OR_RETURN(dataBaseIndex, receiveIntParameter());
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::COM_END);

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_CHANGE_DATABASE));

    if(database->switchDateBase(dataBaseIndex)) {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_ACK));
    } else {
        RETURN_IF_FAILED(sendProtocol(Protocol::ANS_NAK));
        RETURN_IF_FAILED(sendProtocol(Protocol::ERR_DATABASE_DOES_NOT_EXIST));
    }

    RETURN_IF_FAILED(sendProtocol(Protocol::ANS_END));
}