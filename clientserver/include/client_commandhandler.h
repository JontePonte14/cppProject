#ifndef CLIENT_COMMANDHANDLER_H
#define CLIENT_COMMANDHANDLER_H

#include "messagehandler.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class Client_commandhandler {
public:
    Client_commandhandler(const std::shared_ptr<Connection>& conn); //replcace with message handler

    std::vector<std::string> LIST_NG();

    Expected<std::vector<std::string>, Status> CREATE_NG(std::string title);

    Expected<std::vector<std::string>, Status> DELETE_NG(int groupIndex);

    Expected<std::vector<std::string>, Status> LIST_ART(int groupIndex);

    Expected<std::vector<std::string>, Status> CREATE_ART(int groupIndex, std::string title, std::string author, std::string text);

    Expected<std::vector<std::string>, Status> DELETE_ART(int groupIndex, int articleIndex);

    Expected<std::vector<std::string>, Status> GET_ART(int groupIndex, int articleIndex);
private:
    MessageHandler mh;

    void checkCondition(bool condition, std::string method, std::string message) const;
    bool checkCode(Protocol epectedCode, Protocol code) const; 
    
    MessageHandler conn;
};

#endif