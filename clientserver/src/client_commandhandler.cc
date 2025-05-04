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


using std::cout;
using std::endl;
Client_commandhandler::Client_commandhandler(const std::shared_ptr<Connection>& conn) : mh(conn) {
}

Expected<std::vector<std::string>, Status> Client_commandhandler::LIST_NG(){

    mh.sendProtocol(Protocol::COM_LIST_NG);
    mh.sendProtocol(Protocol::COM_END);
    Protocol code = mh.receiveProtocol();
    checkCode(Protocol::ANS_LIST_NG, code, "List groups");
    auto nbrGroups = mh.receiveIntParameter();
    if (!nbrGroups)
    {
        return nbrGroups.error();
    }
    int nbrGroupsInt = *nbrGroups;
    checkCondition(nbrGroupsInt >= 0, "List groups", "Number of groups < 0"); //todo, ändra så sätter protocol violation istället för throw

    std::vector<std::string> groupNamesString(nbrGroupsInt);
    std::vector<int> groupIdsInt(nbrGroupsInt);
    
    for (size_t i = 0; i < nbrGroupsInt; i++) 
    {
        auto groupId = mh.receiveIntParameter();
        auto groupName = mh.receiveStringParameter();
        if (!groupId)
        {
            return groupId.error();
        }
        if (!groupName)
        {
            return groupName.error();
        }
        groupIdsInt[i] = *groupId;
        groupNamesString[i] = *groupName;
    }
    Protocol ans_end = mh.receiveProtocol();
    checkCode(Protocol::ANS_END, ans_end, "List groups"); // sätt violation istället för throw

    return groupNamesString;
}

Expected<std::vector<std::string>, Status> Client_commandhandler::CREATE_NG(std::string title){
    std::vector<std::string> text;
    mh.sendProtocol(Protocol::COM_CREATE_NG);
    mh.sendStringParameter(title);
    mh.sendProtocol(Protocol::COM_END);
    cout << "Sent correctly" << endl;
    Protocol code = mh.receiveProtocol();
    checkCode(Protocol::ANS_CREATE_NG, code, "Create news group");

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
    checkCode(Protocol::ANS_END, ans_end, "Create groups"); // sätt violation istället för throw
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
    checkCode(Protocol::ANS_END, ans_end, "Delete groups"); // sätt violation istället för throw
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
    checkCode(Protocol::ANS_END, ans_end, "Delete groups"); // sätt violation istället för throw
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

void Client_commandhandler::checkCondition(bool condition, std::string method, std::string message) const{
    if (!condition)
    {
        throw std::runtime_error("Faulty method is " + method + ", With messege " + message);
    }
}
void Client_commandhandler::checkCode(Protocol expectedCode, Protocol code, std::string method) const{
    if(expectedCode != code){
        throw std::runtime_error("Faulty method is " + method + ". Protocol code mismatch: expected " + std::to_string(to_code(expectedCode)) + ", got " + std::to_string(to_code(code)));
    }
}