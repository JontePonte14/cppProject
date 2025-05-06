#ifndef CLIENT_COMMANDHANDLER_H
#define CLIENT_COMMANDHANDLER_H

#include "messagehandler.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>



class Client_commandhandler : public MessageHandler {
public:
    Client_commandhandler(const std::shared_ptr<Connection>& conn); //replcace with message handler

    Expected<std::vector<std::string>, Status> LIST_NG();

    Expected<std::vector<std::string>, Status> CREATE_NG(std::string title);

    Expected<std::vector<std::string>, Status> DELETE_NG(int groupIndex);

    Expected<std::vector<std::string>, Status> LIST_ART(int groupIndex);

    Expected<std::vector<std::string>, Status> CREATE_ART(int groupIndex, std::string title, std::string author, std::string text);

    Expected<std::vector<std::string>, Status> DELETE_ART(int groupIndex, int articleIndex);

    Expected<std::vector<std::string>, Status> GET_ART(int groupIndex, int articleIndex);

    Expected<std::vector<std::string>, Status> CHANGE_DATABASE(int dataBaseIndex);
private:
    
    Expected<std::vector<std::string>, Status> receiveIntStringPairs(const int nbrGroups);
    Status checkCondition(bool condition, Status error) const;
    //bool checkCode(Protocol epectedCode, Protocol code) const; 
    
    MessageHandler mh;
};

#endif