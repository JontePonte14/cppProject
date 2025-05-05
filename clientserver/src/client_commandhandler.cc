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

#define RETURN_IF_FAILED(expr) \
    do { \
        if (!(expr)) return ProtocolViolation; \
    } while (0)

#define RETURN_IF_ERROR(expr)                          \
    do {                                                \
        if (!(expr)) {                                  \
            std::cout << "Got no " #expr " from server" << std::endl; \
            return (expr).error();                      \
        }                                               \
    } while (0)

using std::cout;
using std::endl;
Client_commandhandler::Client_commandhandler(const std::shared_ptr<Connection>& conn) : mh(conn) {
}

Expected<std::vector<std::string>, Status> Client_commandhandler::LIST_NG(){
    std::vector<std::string> text;
    mh.sendProtocol(Protocol::COM_LIST_NG);
    mh.sendProtocol(Protocol::COM_END);
    Protocol code = mh.receiveProtocol();

    RETURN_IF_FAILED(checkCode(Protocol::ANS_LIST_NG, code));
    
    auto nbrGroups = mh.receiveIntParameter();
    RETURN_IF_ERROR(nbrGroups);

    int nbrGroupsInt = *nbrGroups;
    RETURN_IF_FAILED(checkCondition(nbrGroupsInt >= 0, "Error, number of groups received from server is less than 0"));

    std::vector<std::string> nameIdPairVector(nbrGroupsInt);
    std::string nameIdPair;
    for (size_t i = 0; i < nbrGroupsInt; i++) {
        auto groupId = mh.receiveIntParameter();
        auto groupName = mh.receiveStringParameter();
        if (!groupId) {
            cout << "Missing Group Id on iteration: " << i << "Expected length: " << nbrGroupsInt << endl;
            return groupId.error();
        }
        if (!groupName) {
            cout << "Missing Group Name on iteration: " << i << "Expected length: " << nbrGroupsInt <<endl;
            return groupName.error();
        }
        cout << "Id is: " << *groupId << endl;
        nameIdPair = std::to_string(*groupId) + " " + *groupName; 
        nameIdPairVector[i] = nameIdPair;
    }
    if (nbrGroupsInt == 0)
    {
        nameIdPairVector = {"No newsgroups exist"};
    }
    
    Protocol ans_end = mh.receiveProtocol();
    RETURN_IF_FAILED(checkCode(Protocol::ANS_END, ans_end));
    return nameIdPairVector;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::CREATE_NG(std::string title){
    std::vector<std::string> text;
    mh.sendProtocol(Protocol::COM_CREATE_NG);
    mh.sendStringParameter(title);
    mh.sendProtocol(Protocol::COM_END);
    Protocol code = mh.receiveProtocol();
    RETURN_IF_FAILED(checkCode(Protocol::ANS_CREATE_NG, code));
    Protocol ans = mh.receiveProtocol();
    if (ans == Protocol::ANS_ACK)
    {
        text.push_back("News group succesfully created");
    }
    else if (ans == Protocol::ANS_NAK)
    {
        Protocol error = mh.receiveProtocol();
        if (error == Protocol::ERR_NG_ALREADY_EXISTS)
        {
            text.push_back("News group already exist ");
        }
        else
        {
            return ProtocolViolation;
        }
    }
    else
    {
        return ProtocolViolation;
    }
    Protocol ans_end = mh.receiveProtocol();
    RETURN_IF_FAILED(checkCode(Protocol::ANS_END, ans_end));
    return text;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::DELETE_NG(int groupIndex) {
    std::vector<std::string> text;
    mh.sendProtocol(Protocol::COM_DELETE_NG);
    mh.sendIntParameter(groupIndex);
    mh.sendProtocol(Protocol::COM_END);
    Protocol ans = mh.receiveProtocol();
    if (ans == Protocol::ANS_ACK)
    {
        text.push_back("News group succesfully created");
    }
    else if (ans == Protocol::ANS_NAK)
    {
        Protocol error = mh.receiveProtocol();
        if (error == Protocol::ERR_NG_DOES_NOT_EXIST)
        {
            text.push_back("News group does not exist ");
        }
        else
        {
            return ProtocolViolation;
        }
    }
    else
    {
        return ProtocolViolation;
    }
    Protocol ans_end = mh.receiveProtocol();
    RETURN_IF_FAILED(checkCode(Protocol::ANS_END, ans_end)); 
    return text;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::LIST_ART(int groupIndex){
    std::vector<std::string> text;
    mh.sendProtocol(Protocol::COM_LIST_ART);
    mh.sendIntParameter(groupIndex);
    mh.sendProtocol(Protocol::COM_END);
    Protocol ans = mh.receiveProtocol();
    if (ans == Protocol::ANS_ACK) //add more stuff
    {
        text.push_back("News group succesfully created");
    }
    else if (ans == Protocol::ANS_NAK)
    {
        Protocol error = mh.receiveProtocol();
        if (error == Protocol::ERR_NG_DOES_NOT_EXIST)
        {
            text.push_back("News group does not exist ");
        }
        else
        {
            return ProtocolViolation;
        }
    }
    else
    {
        return ProtocolViolation;
    }
    Protocol ans_end = mh.receiveProtocol();
    checkCode(Protocol::ANS_END, ans_end); // sätt violation istället för throw
    return text;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::CREATE_ART(int groupIndex, std::string title, std::string author, std::string text){
    return std::vector<std::string>{};
}

Expected<std::vector<std::string>, Status> Client_commandhandler::DELETE_ART(int groupIndex, int articleIndex){
    return std::vector<std::string>{};
}

Expected<std::vector<std::string>, Status> Client_commandhandler::GET_ART(int groupIndex, int articleIndex){
    return std::vector<std::string>{};
}

bool Client_commandhandler::checkCondition(bool condition, std::string message) const{
    if (condition)
    {
        return true;
    }
    else {
        cout << message << endl;
        return false;
    }
}
bool Client_commandhandler::checkCode(Protocol expectedCode, Protocol code) const{
    if(expectedCode == code){
        return true;
    }
    else
    {
        cout << "PROTOCOL VIOLATION. Expected: " << to_string(expectedCode) << " Got: " << to_string(code) << endl;
        return false;
    }
} 
/* void Client_commandhandler::checkCode(Protocol expectedCode, Protocol code) const{
    if(expectedCode != code){
        throw std::runtime_error("Expected: " + std::string(to_string(expectedCode)) + ". Got: " + std::string(to_string(code)));
    }
} */