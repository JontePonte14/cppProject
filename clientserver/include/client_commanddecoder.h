#ifndef CLIENTCOMMANDDECODER_H
#define CLIENTCOMMANDDECODER_H

#include "client_commandhandler.h"
#include "connection.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

enum class InputStatus {
    EmptyInput,
    Exit,
    IdLessZero,
    IdTooBig,
    IdNotNumber,
};

class Client_commanddecoder {
public:
    Client_commanddecoder(const std::shared_ptr<Connection>& conn);

    void com_decode(std::istream& is);

private:
    void LIST_NG();

    void CREATE_NG(std::istream& is);

    void DELETE_NG(std::istream& is);

    void LIST_ART(std::istream& is);

    void CREATE_ART(std::istream& is);

    void DELETE_ART(std::istream& is);

    void GET_ART(std::istream& is);

    void HELP_COM() const;

    void printReply(const Expected<std::vector<std::string>, Status>& vec) const;

    void printConnectionError(const Status& error) const;

    void printInputError(const InputStatus& error) const;
    
    Expected<std::string, InputStatus>  readInputString(std::istream& is) const;

    Expected<int, InputStatus> readInputId(std::istream& is) const;

    Expected<int, InputStatus> stringToInt (const std::string& p) const;

    std::string removeWhitespaces(std::string& str) const;
    //Expected<std::vector<std::string>, Status> reply;

    Client_commandhandler comhand;
};

#endif