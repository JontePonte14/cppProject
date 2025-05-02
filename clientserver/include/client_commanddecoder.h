#ifndef CLIENTCOMMANDDECODER_H
#define CLIENTCOMMANDDECODER_H
#include "client_commandhandler.h"
#include "connection.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

class Client_commanddecoder {
public:
    Client_commanddecoder(const std::shared_ptr<Connection>& conn);

    void com_decode(std::istream& input);

private:
    void LIST_NG();

    void CREATE_NG(const std::string& title);

    void DELETE_NG(std::string& groupIndexStr);

    void LIST_ART(std::string& groupIndex);

    void CREATE_ART(std::string& groupIndex, const std::string& title, const std::string& author, const std::string& text);

    void DELETE_ART(std::string& groupIndex, std::string& articleIndex);

    void GET_ART(std::string& groupIndex, std::string& articleIndex);

    void printReply(const std::vector<std::string>& vec) const;

    void HELP_COM() const;

    std::optional<int> string_to_int (const std::string& p) const;

    std::vector<std::string> reply;
    Client_commandhandler comhand;
};

#endif