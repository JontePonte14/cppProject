#include "connection.h" 
#include "client_commandhandler.h"
#include "protocol.h"
#include <iostream>
#include <fstream>
#include <vector>

Client_commandhandler::Client_commandhandler(const std::shared_ptr<Connection>& conn)
    : conn(conn) {
}

std::vector<std::string> Client_commandhandler::LIST_NG(std::istream& paramerters){

    conn.sendProtocol(Protocol::COM_LIST_NG);
    conn.sendProtocol(Protocol::COM_END);
    return {"ID", "Name"};
}

std::vector<std::string> Client_commandhandler::CREATE_NG(std::istream& paramerters){
    return {"null"};
}

std::vector<std::string> Client_commandhandler::DELETE_NG(std::istream& paramerters) {
    return {"null"};
}

std::vector<std::string> Client_commandhandler::LIST_ART(std::istream& paramerters){
    return {"null"};
}

std::vector<std::string> Client_commandhandler::CREATE_ART(std::istream& paramerters){
    return {"null"};
}

std::vector<std::string> Client_commandhandler::DELETE_ART(std::istream& paramerters){
    return {"null"};
}

std::vector<std::string> Client_commandhandler::GET_ART(std::istream& paramerters){
    return{"null"};
}