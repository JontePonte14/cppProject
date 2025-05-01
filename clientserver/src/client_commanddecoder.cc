#include "client_commanddecoder.h"
#include "client_commandhandler.h"
#include "connection.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;

Client_commanddecoder::Client_commanddecoder(const std::shared_ptr<Connection>& conn) : comhand(conn) { //replace with messagehandler

}

void Client_commanddecoder::com_decode(std::istream& input){
    string command;
    input >> command;

    if (input.fail()) {
        cout << "FAIL! command needs to be string" << endl;
        input.clear();
        input.ignore();
    }
    else {
        std::transform(command.begin(), command.end(), command.begin(),
        [](unsigned char c){ return std::tolower(c); });

        if (command == "help_com") {
            HELP_COM();
        }
        else if(command == "list_ng"){
            LIST_NG(input);
        }
        else if(command == "create_ng"){
            CREATE_NG(input);
        }
        else if(command == "delete_ng"){
            DELETE_NG(input);
        }
        else if(command == "list_art"){
            LIST_ART(input);
        }
        else if(command == "create_art"){
            CREATE_ART(input);
        }
        else if(command == "delete_art"){
            DELETE_ART(input);
        }
        else if(command == "get_art"){
            GET_ART(input);
        }
        else {
            cout << "FAIL! no such command exists, type help_com for command list" << endl;
        }
        
    }
}
void Client_commanddecoder::LIST_NG(std::istream& parameters) {
    cout << "Reply from server: " << endl;
    reply = comhand.LIST_NG(parameters);
    printReply(reply);
}

void Client_commanddecoder::CREATE_NG(std::istream& parameters) {
    cout << "Reply from server: " << endl;
    reply = comhand.CREATE_NG(parameters);
}

void Client_commanddecoder::DELETE_NG(std::istream& parameters) {
    cout << "Reply from server: " << endl;
    reply = comhand.DELETE_NG(parameters);
}

void Client_commanddecoder::LIST_ART(std::istream& parameters) {
    cout << "Reply from server: " << endl;
    reply = comhand.LIST_ART(parameters);
}

void Client_commanddecoder::CREATE_ART(std::istream& parameters) {
    cout << "Reply from server: " << endl;
    reply = comhand.CREATE_ART(parameters);
}

void Client_commanddecoder::DELETE_ART(std::istream& parameters) {
    cout << "Reply from server: " << endl;
    reply = comhand.DELETE_ART(parameters);
}

void Client_commanddecoder::GET_ART(std::istream& parameters) {
    cout << "Reply from server: " << endl;
    reply = comhand.GET_ART(parameters);
}
void Client_commanddecoder::printReply(const std::vector<std::string>& vec) const{
    for (string i: vec)
    std::cout << i << endl;
}

void Client_commanddecoder::HELP_COM(){
    cout << "List of commands: " << endl;
    cout << "List newsgroups: LIST_NG" << endl;
    cout << "Create a newsgroup: CREATE_NG <title>" << endl;
    cout << "Delete a newsgroup: DELETE_NG <NG_id_number>" << endl;
    cout << "List articles in newsgroup: LIST_ART <NG_id_number>" << endl;
    cout << "Create an article in newsgroup: CREATE_ART <NG_id_number> <title> <author> <text>" << endl;
    cout << "Delete an article: DELETE_ART <NG_id_number> <ART_id_number>" << endl;
    cout << "Get an article: GET_ART <NG_id_number> <ART_id_number>" << endl;
}
