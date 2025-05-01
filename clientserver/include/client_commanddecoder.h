#ifndef CLIENTCOMMANDDECODER_H
#define CLIENTCOMMANDDECODER_H
#include "client_commandhandler.h"
#include "connection.h"
#include <iostream>
#include <fstream>
#include <vector>

class Client_commanddecoder {
public:
    Client_commanddecoder(const std::shared_ptr<Connection>& conn);

    void com_decode(std::istream& input);

private:
    void LIST_NG(std::istream& paramerters);

    void CREATE_NG(std::istream& paramerters);

    void DELETE_NG(std::istream& paramerters);

    void LIST_ART(std::istream& paramerters);

    void CREATE_ART(std::istream& paramerters);

    void DELETE_ART(std::istream& paramerters);

    void GET_ART(std::istream& paramerters);

    void printReply(const std::vector<std::string>& vec) const;

    void HELP_COM();

    std::vector<std::string> reply;
    Client_commandhandler comhand;
};

#endif