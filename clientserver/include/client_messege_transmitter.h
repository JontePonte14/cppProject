#ifndef CLIENT_MESSEGE_TRANSMITTER_H
#define CLIENT_MESSEGE_TRANSMITTER_H
#include "connection.h" 
//include messege handler
#include <iostream>
#include <fstream>

class client_messege_transmitter {
public:
    client_messege_transmitter(const Connection& conn); //replcace with message handler

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