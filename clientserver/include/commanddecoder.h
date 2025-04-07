#ifndef COMMANDDECODER_H
#define COMMANDDECODER_H
#include "connection.h"
#include <iostream>
#include <fstream>

class commanddecoder {
public:
    commanddecoder(const Connection& conn);

    void com_decode(std::istream& input);
private:
    void LIST_NG(std::istream& paramerters);

    void CREATE_NG(std::istream& paramerters);

    void DELETE_NG(std::istream& paramerters);

    void LIST_ART(std::istream& paramerters);

    void CREATE_ART(std::istream& paramerters);

    void DELETE_ART(std::istream& paramerters);

    void GET_ART(std::istream& paramerters);

    void HELP_COM();

};

#endif