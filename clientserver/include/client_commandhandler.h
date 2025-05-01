#ifndef CLIENT_COMMANDHANDLER_H
#define CLIENT_COMMANDHANDLER_H
#include "messagehandler.h" 
#include <iostream>
#include <fstream>
#include <vector>

class Client_commandhandler {
public:
    Client_commandhandler(const std::shared_ptr<Connection>& conn); //replcace with message handler

    std::vector<std::string> LIST_NG(std::istream& paramerters);

    std::vector<std::string> CREATE_NG(std::istream& paramerters);

    std::vector<std::string> DELETE_NG(std::istream& paramerters);

    std::vector<std::string> LIST_ART(std::istream& paramerters);

    std::vector<std::string> CREATE_ART(std::istream& paramerters);

    std::vector<std::string> DELETE_ART(std::istream& paramerters);

    std::vector<std::string> GET_ART(std::istream& paramerters);

    private:
        MessageHandler conn;
};

#endif