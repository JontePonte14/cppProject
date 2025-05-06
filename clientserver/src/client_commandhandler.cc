#include "connection.h" 
#include "client_commandhandler.h"
#include "messagehandler.h"
#include "protocol.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

/* #define RETURN_IF_FAILED_CONDITION(expr) \
    do { \
        if (!(expr)) return ProtocolViolation; \
    } while (0) */
#define RETURN_IF_FAILED_CLIENT(expr)              \
    do {                                    \
        Status _status = (expr);            \
        if (_status != Status::Success)     \
            return _status;                 \
    } while (0)

// Macro used for unpacking an Expected<V, E> object into V if valid, else returning E
#define ASSIGN_OR_RETURN_CLIENT(var, expr)                              \
auto CONCAT(_result_, __LINE__) = (expr);                    \
if (!CONCAT(_result_, __LINE__))                             \
    return CONCAT(_result_, __LINE__).error();               \
decltype(auto) var = std::move(*CONCAT(_result_, __LINE__));

/* #define RETURN_IF_ERROR(expr)                          \
    do {                                                \
        if (!(expr)) {                                  \
            std::cout << "Got no " #expr " from server" << std::endl; \
            return (expr).error();                      \
        }                                               \
    } while (0) */


using std::cout;
using std::endl;

Client_commandhandler::Client_commandhandler(const std::shared_ptr<Connection>& conn) : MessageHandler(conn) {
}

Expected<std::vector<std::string>, Status> Client_commandhandler::LIST_NG(){
    std::vector<std::string> replyText;
    //Data to server

    RETURN_IF_FAILED(sendProtocol(Protocol::COM_LIST_NG));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));

    //ANS_LIST_NG
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_LIST_NG);
    //Data fropm server
    ASSIGN_OR_RETURN(nbrGroupsInt, receiveIntParameter());

    RETURN_IF_FAILED_CLIENT(checkCondition(nbrGroupsInt >= 0, Status::InvalidArguments));
    std::vector<std::string> nameIdPairVector(nbrGroupsInt);
    std::string nameIdPair;
    ASSIGN_OR_RETURN_CLIENT(intStringPair, receiveIntStringPairs(nbrGroupsInt));
    replyText = intStringPair;
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);
    return replyText;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::CREATE_NG(std::string title){
    std::vector<std::string> replyText;
    //Data to server
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_CREATE_NG));
    RETURN_IF_FAILED(sendStringParameter(title));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));

    //ANS_CREATE_NG
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_CREATE_NG);

    //Data from server
    ASSIGN_OR_RETURN(ans, receiveProtocol());

    if (ans == Protocol::ANS_ACK) {
        replyText.push_back("News group succesfully created");
    }
    else if (ans == Protocol::ANS_NAK) {
        const auto error = receiveProtocol();
        if (error && *error == Protocol::ERR_NG_ALREADY_EXISTS) {
            replyText.push_back("News group already exist ");
        }
        else {
            return ProtocolViolation;
        }
    }
    else {
        return ProtocolViolation;
    }
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);
    return replyText;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::DELETE_NG(int groupIndex) {
    std::vector<std::string> replyText;
    //Data to server
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_DELETE_NG));
    RETURN_IF_FAILED(sendIntParameter(groupIndex));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));

    //ANS_DELETE_NG
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_DELETE_NG);
    //Data from server
    ASSIGN_OR_RETURN(ans, receiveProtocol());

    if (ans == Protocol::ANS_ACK) {
        replyText.push_back("News group succesfully deleted");
    }
    else if (ans == Protocol::ANS_NAK) {
        const auto error = receiveProtocol();
        if (error && *error == Protocol::ERR_NG_DOES_NOT_EXIST) {
            replyText.push_back("News group does not exist ");
        }
        else {
            return ProtocolViolation;
        }
    }
    else {
        return ProtocolViolation;
    }
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);
    return replyText;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::LIST_ART(int groupIndex){
    //Data to server
    std::vector<std::string> replyText;
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_LIST_ART));
    RETURN_IF_FAILED(sendIntParameter(groupIndex));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));

    //ANS_LIST_ART
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_LIST_ART);
    //Data from server
    ASSIGN_OR_RETURN(ans, receiveProtocol());

    if (ans == Protocol::ANS_ACK) {
        ASSIGN_OR_RETURN(nbrArtsInt, receiveIntParameter());
        RETURN_IF_FAILED_CLIENT(checkCondition(nbrArtsInt >= 0, Status::InvalidArguments));
        //Receive article index plus article name
        ASSIGN_OR_RETURN_CLIENT(intStringPairs, receiveIntStringPairs(nbrArtsInt))
        replyText = intStringPairs;
    }
    else if (ans == Protocol::ANS_NAK) {
        auto error = receiveProtocol();
        if (error && *error == Protocol::ERR_NG_DOES_NOT_EXIST) {
            replyText = {"News group does not exist "};
        }
        else {
            return ProtocolViolation;
        }
    }
    else {
        return ProtocolViolation;
    }
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);// sätt violation istället för throw
    return replyText;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::CREATE_ART(int groupIndex, std::string title, std::string author, std::string text){
    std::vector<std::string> replyText;
    //Data sent to server
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_CREATE_ART));
    RETURN_IF_FAILED(sendIntParameter(groupIndex));
    RETURN_IF_FAILED(sendStringParameter(title));
    RETURN_IF_FAILED(sendStringParameter(author));
    RETURN_IF_FAILED(sendStringParameter(text));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));

    //ANS_CREATE_ART
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_CREATE_ART);
    //Data from server
    ASSIGN_OR_RETURN(ans, receiveProtocol());
    if (ans == Protocol::ANS_ACK) {
        replyText.push_back("Article succesfully created");
    }
    else if (ans == Protocol::ANS_NAK) {
        auto error = receiveProtocol();
        if (error && *error == Protocol::ERR_NG_DOES_NOT_EXIST) {
            replyText.push_back("News group does not exist ");
        }
        else {
            return ProtocolViolation;
        }
    }
    else {
        return ProtocolViolation;
    }
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);
    return replyText;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::DELETE_ART(int groupIndex, int articleIndex){
    std::vector<std::string> replyText;
    //Data sent to server
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_DELETE_ART));
    RETURN_IF_FAILED(sendIntParameter(groupIndex));
    RETURN_IF_FAILED(sendIntParameter(articleIndex));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));
    //ANS_CREATE_ART
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_DELETE_ART);
    //Data from server
    ASSIGN_OR_RETURN(ans, receiveProtocol());
    if (ans == Protocol::ANS_ACK) {
        replyText.push_back("Article succesfully Deleted");
    }
    else if (ans == Protocol::ANS_NAK) {
        auto error = receiveProtocol();
        if (error && *error == Protocol::ERR_NG_DOES_NOT_EXIST) {
            replyText.push_back("News group does not exist ");
        }
        else if (error && *error == Protocol::ERR_ART_DOES_NOT_EXIST){
            replyText.push_back("Article does not exist ");
        }
        else
        {
            return ProtocolViolation;
        }
        
    }
    else {
        return ProtocolViolation;
    }
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);
    return replyText;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::GET_ART(int groupIndex, int articleIndex){
    std::vector<std::string> replyText;
    //Data sent to server
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_GET_ART));
    RETURN_IF_FAILED(sendIntParameter(groupIndex));
    RETURN_IF_FAILED(sendIntParameter(articleIndex));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));
    //ANS_CREATE_ART
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_GET_ART);
    //Data from server
    ASSIGN_OR_RETURN(ans, receiveProtocol());
    if (ans == Protocol::ANS_ACK) {
        ASSIGN_OR_RETURN(title, receiveStringParameter());
        ASSIGN_OR_RETURN(author, receiveStringParameter());
        ASSIGN_OR_RETURN(text, receiveStringParameter());
        replyText.push_back(title);
        replyText.push_back(author);
        replyText.push_back(" ");
        replyText.push_back(text);
    }
    else if (ans == Protocol::ANS_NAK) {
        auto error = receiveProtocol();
        if (error && *error == Protocol::ERR_NG_DOES_NOT_EXIST) {
            replyText.push_back("News group does not exist ");
        }
        else if (error && *error == Protocol::ERR_ART_DOES_NOT_EXIST){
            replyText.push_back("Article does not exist ");
        }
        else
        {
            return ProtocolViolation;
        }
        
    }
    else {
        return ProtocolViolation;
    }
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);
    return replyText;
}
Expected<std::vector<std::string>, Status> Client_commandhandler::CHANGE_DATABASE(int dataBaseIndex){
    std::vector<std::string> replyText;
    //Data sent to server
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_CHANGE_DATABASE));
    RETURN_IF_FAILED(sendIntParameter(dataBaseIndex));
    RETURN_IF_FAILED(sendProtocol(Protocol::COM_END));
    //ANS_CHANGE_DATABASE
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_CHANGE_DATABASE);
    //Data from server
    ASSIGN_OR_RETURN(ans, receiveProtocol());
    if (ans == Protocol::ANS_ACK) {
        replyText.push_back("Database changed");
    }
    else if (ans == Protocol::ANS_NAK) {
        auto error = receiveProtocol();
        if (error && *error == Protocol::ERR_DATABASE_DOES_NOT_EXIST) {
            replyText.push_back("Database does not exist ");
        }
        else
        {
            return ProtocolViolation;
        }
        
    }
    else {
        return ProtocolViolation;
    }
    //ANS_END
    RECEIVE_AND_VERIFY_PROTOCOL(Protocol::ANS_END);
    return replyText;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::receiveIntStringPairs(const int nbrGroupsInt) {
    std::vector<std::string> nameIdPairVector(nbrGroupsInt);
    std::string nameIdPair;
    //Receive index plus groupname
    for (int i = 0; i < nbrGroupsInt; i++) {
        ASSIGN_OR_RETURN(groupId, receiveIntParameter());
        ASSIGN_OR_RETURN(groupName, receiveStringParameter());
        nameIdPairVector[i] = std::to_string(groupId) + " " + groupName;
    }
    if (nbrGroupsInt == 0) {
        nameIdPairVector = {"No newsgroups exist"};
    }
    return nameIdPairVector;
}

Status Client_commandhandler::checkCondition(bool condition, Status error) const{
    if (condition) {
        return Success;
    }
    else {
        return error;
    }
}
/* bool Client_commandhandler::checkCode(Protocol expectedCode, Protocol code) const{
    if(expectedCode == code){
        return true;
    }
    else {
        cout << "PROTOCOL VIOLATION. Expected: " << to_string(expectedCode) << " Got: " << to_string(code) << endl;
        return false;
    }
}  */
