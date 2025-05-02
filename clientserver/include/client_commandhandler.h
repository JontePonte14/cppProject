#ifndef CLIENT_COMMANDHANDLER_H
#define CLIENT_COMMANDHANDLER_H
#include "connection.h" 
#include "messagehandler.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class Client_commandhandler {
public:
    //todo: change to messagehandler
    Client_commandhandler(const Connection& conn); //replcace with message handler

    std::vector<std::string> LIST_NG();

    std::vector<std::string> CREATE_NG(std::string title);

    std::vector<std::string> DELETE_NG(int groupIndex);

    std::vector<std::string> LIST_ART(int groupIndex);

    std::vector<std::string> CREATE_ART(int groupIndex, std::string title, std::string author, std::string text);

    std::vector<std::string> DELETE_ART(int groupIndex, int articleIndex);

    std::vector<std::string> GET_ART(int groupIndex, int articleIndex);
private:
    MessageHandler mh;
    void checkCode(Protocol epectedCode, Protocol code) const; 
};

#endif