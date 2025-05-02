#include "client_commanddecoder.h"
#include "client_commandhandler.h"
#include "connection.h"
#include <optional>
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

        //std::string p1, p2, p3, p4;
        //input >> p1 >> p2 >> p3 >> p4;
        if (input.fail())
        {
            cout << "STREAM FAIL" << endl;
        }
        
        //std::vector<std::string> reply;

        if (command == "help_com") {
            HELP_COM();
        }
        else if(command == "list_ng"){
            reply = comhand.LIST_NG();
            cout << "List of news groups ";
        }
        else if(command == "create_ng"){
            //reply = comhand.CREATE_NG(input);
            cout << "Newsgroup succesfully created " << endl;
        }
        else if(command == "delete_ng"){
            //reply = comhand.DELETE_NG(input);
            cout << "Newsgroup succesfully deleted " << endl;
        }
        else if(command == "list_art"){
            //reply = comhand.LIST_ART(input);
            cout << "List of articles in newsgroup ";
        }
        else if(command == "create_art"){
            //reply = comhand.CREATE_ART(input);
            cout << "Article succesfully created ";
        }
        else if(command == "delete_art"){
            //reply = comhand.DELETE_ART(input);
            cout << "Article succesfully deleted ";
        }
        else if(command == "get_art"){
            //reply = comhand.GET_ART(input);
            cout << "Article: ";
        }
        else {
            cout << "FAIL! no such command exists, type help_com for command list" << endl;
        }
        
    }
}
void Client_commanddecoder::LIST_NG() {
    cout << "Reply from server: " << endl;
    reply = comhand.LIST_NG();
    printReply(reply);
}

void Client_commanddecoder::CREATE_NG(const std::string& title) {
    
    cout << "Reply from server: " << endl;
    reply = comhand.CREATE_NG(title);
}

void Client_commanddecoder::DELETE_NG(std::string& groupIndexStr) {
    auto maybyIndex = string_to_int(groupIndexStr);
    if (!maybyIndex)
    {
        return;
    }
    int groupIndex = *maybyIndex;
    cout << "Reply from server: " << endl;
    //reply = comhand.DELETE_NG(parameters);
}

void Client_commanddecoder::LIST_ART(std::string& groupIndex) {
    

    cout << "Reply from server: " << endl;
    //reply = comhand.LIST_ART(parameters);
}

void Client_commanddecoder::CREATE_ART(std::string& groupIndex, const std::string& title, const std::string& author, const std::string& text) {
    cout << "Reply from server: " << endl;
    //reply = comhand.CREATE_ART(parameters);
}

void Client_commanddecoder::DELETE_ART(std::string& groupIndex, std::string& articleIndex) {
    cout << "Reply from server: " << endl;
    //reply = comhand.DELETE_ART(parameters);
}

void Client_commanddecoder::GET_ART(std::string& groupIndex, std::string& articleIndex) {
    cout << "Reply from server: " << endl;
    //reply = comhand.GET_ART(parameters);
}
void Client_commanddecoder::printReply(const std::vector<std::string>& vec) const{
    cout << "Reply from server: ";
    for (string i: vec) {
        std::cout << i << endl;
    }
    
}

std::optional<int> Client_commanddecoder::string_to_int(const std::string& p) const{
    try {
        return std::stoi(p);  // might throw
    } catch (const std::invalid_argument&) {
        // Not a number
        cout << "Index needs to be a number! " << endl;
        return std::nullopt;
    } catch (const std::out_of_range&) {
        // Too big/small for int
        cout << "try a smaller number " << endl;
        return std::nullopt;
    }
    
    
}

void Client_commanddecoder::HELP_COM() const{
    cout << "List of commands: " << endl;
    cout << "List newsgroups: LIST_NG" << endl;
    cout << "Create a newsgroup: CREATE_NG <title>" << endl;
    cout << "Delete a newsgroup: DELETE_NG <NG_id_number>" << endl;
    cout << "List articles in newsgroup: LIST_ART <NG_id_number>" << endl;
    cout << "Create an article in newsgroup: CREATE_ART <NG_id_number> <title> <author> <text>" << endl;
    cout << "Delete an article: DELETE_ART <NG_id_number> <ART_id_number>" << endl;
    cout << "Get an article: GET_ART <NG_id_number> <ART_id_number>" << endl;
}
