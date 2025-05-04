#include "connection.h" 
#include "client_commandhandler.h"
#include "messagehandler.h"
#include "protocol.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
Client_commandhandler::Client_commandhandler(const std::shared_ptr<Connection>& conn) : mh(conn) {
}

std::vector<std::string> Client_commandhandler::LIST_NG(){

    mh.sendProtocol(Protocol::COM_LIST_NG);
    mh.sendProtocol(Protocol::COM_END);
    Protocol code = mh.receiveProtocol();
    checkCode(Protocol::ANS_LIST_NG, code);
    cout << to_string(code) << endl;

/*     std::optional<uint32_t> nbrGroups = mh.receiveIntParameter();

    conn.sendProtocol(Protocol::COM_LIST_NG);
    conn.sendProtocol(Protocol::COM_END); */
    return {"ID", "Name"};
}

std::vector<std::string> Client_commandhandler::CREATE_NG(std::string title){
    conn.sendProtocol(Protocol::COM_CREATE_NG);
    conn.sendStringParameter("TEST");
    
    return {"null"};
}

std::vector<std::string> Client_commandhandler::DELETE_NG(int groupIndex) {
    return {"null"};
}

std::vector<std::string> Client_commandhandler::LIST_ART(int groupIndex){
    return {"null"};
}

std::vector<std::string> Client_commandhandler::CREATE_ART(int groupIndex, std::string title, std::string author, std::string text){
    return {"null"};
}

std::vector<std::string> Client_commandhandler::DELETE_ART(int groupIndex, int articleIndex){
    return {"null"};
}

std::vector<std::string> Client_commandhandler::GET_ART(int groupIndex, int articleIndex){
    return{"null"};
}

void Client_commandhandler::checkCode(Protocol expectedCode, Protocol code) const{
    if(expectedCode != code){
        throw std::runtime_error("Protocol code mismatch: expected " + std::to_string(to_code(expectedCode)) + ", got " + std::to_string(to_code(code)));
    }
}