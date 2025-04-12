#ifndef CLIENTCOMMANDDECODER_H
#define CLIENTCOMMANDDECODER_H
#include "connection.h"
#include <iostream>
#include <fstream>

class Client_commanddecoder {
public:
    Client_commanddecoder(const Connection& conn);

    void com_decode(std::istream& input);

private:
    void HELP_COM();
};

#endif