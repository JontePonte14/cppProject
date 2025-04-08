#include "commandhandler.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using std::string;
using std::cout;
using std::cin;
using std::endl;


commandhandler::commandhandler(const Connection& conn){ //replace with messagehandler

}

void commandhandler::com_decode(std::istream& input){
    string command;
    input >> command;
    
    std::transform(command.begin(), command.end(), command.begin(),
     [](unsigned char c){ return std::tolower(c); });

    if (input.fail()) {
        cout << "FAIL! command needs to be string" << endl;
    }
    else {
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

void commandhandler::HELP_COM(){
    cout << "List of commands: " << endl;
    cout << "List newsgroups: LIST_NG" << endl;
    cout << "Create a newsgroup: CREATE_NG <title>" << endl;
    cout << "Delete a newsgroup: DELETE_NG <NG_id_number>" << endl;
    cout << "List articles in newsgroup: LIST_ART <NG_id_number>" << endl;
    cout << "Create an article in newsgroup: CREATE_ART <NG_id_number> <title> <author> <text>" << endl;
    cout << "Delete an article: DELETE_ART <NG_id_number> <ART_id_number>" << endl;
    cout << "Get an article: GET_ART <NG_id_number> <ART_id_number>" << endl;
}
