#include "client_commanddecoder.h"
#include "client_commandhandler.h"
#include "connection.h"
#include "messagehandler.h"
#include <optional>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;



Client_commanddecoder::Client_commanddecoder(const std::shared_ptr<Connection>& conn) : comhand(conn) { //replace with messagehandler

}

void Client_commanddecoder::com_decode(std::istream& is){
    //std::vector<std::string> userInputs = readInputsStream(input); //Look at messege protocol for inputs
    std::string command;
    std::getline(is, command);

    removeWhitespaces(command);

    std::transform(command.begin(), command.end(), command.begin(),
    [](unsigned char c){ return std::tolower(c); });

    if (is.fail())
    {
        cout << "STREAM FAIL" << endl;
    }

    if (command == "help_com") {
        HELP_COM();
    }

    else if(command == "list_ng"){
        //cout << "List of news groups " << endl;
        LIST_NG();

    }

    else if(command == "create_ng"){
        cout << "Type the name of the newsgroup you want to create (or type exit): " << endl;
        CREATE_NG(is);
    }

    else if(command == "delete_ng"){
        cout << "Type the name of the newsgroup you want to delete: " << endl;
        //DELETE_NG(is);
    }

    else if(command == "list_art"){
        //cout << "List of articles in newsgroup ";
        //LIST_ART(is);
    }

    else if(command == "create_art"){
        //cout << "Article succesfully created ";
    } 

    else if(command == "delete_art"){
        //cout << "Article succesfully deleted ";
    }
    else if(command == "get_art"){
        //cout << "Article: ";
    }
    else if (command == "exit")
    {
        
    }
    else {
        cout << "FAIL! no such command exists, type help_com for command list" << endl;
    }
}
void Client_commanddecoder::LIST_NG() {
    auto reply = comhand.LIST_NG();
    printReply(reply);
}

void Client_commanddecoder::CREATE_NG(std::istream& is) {
    //Inputs
    auto title = readInputString(is);
    if (!title)
    {
        printInputError(title.error());
        if (title.error() == InputStatus::EmptyInput)
        {
            CREATE_NG(is);
        }
        return;
    }
    //Outputs
    auto reply = comhand.CREATE_NG(*title);
    printReply(reply);

}

/* void Client_commanddecoder::DELETE_NG(std::istream& is) {
    auto Id = readInputId(is);
    if (!Id)
    {
        printInputError(Id.error());
        if (Id.error() == InputStatus::EmptyInput)
        {
            DELETE_NG(is);
        }
        return;
    }
    reply = comhand.DELETE_NG(*Id);
    if (!reply)
    {
        printConnectionError(reply.error());
        return;
    }
    printReply(*reply);
} */

void Client_commanddecoder::LIST_ART(std::istream& is) {
    

    cout << "Reply from server: " << endl;
    //reply = comhand.LIST_ART(parameters);
}

void Client_commanddecoder::CREATE_ART(std::istream& is) {
    cout << "Reply from server: " << endl;
    //reply = comhand.CREATE_ART(parameters);
}

void Client_commanddecoder::DELETE_ART(std::istream& is) {
    cout << "Reply from server: " << endl;
    //reply = comhand.DELETE_ART(parameters);
}

void Client_commanddecoder::GET_ART(std::istream& is) {
    cout << "Reply from server: " << endl;
    //reply = comhand.GET_ART(parameters);
}

void Client_commanddecoder::printReply(const Expected<std::vector<std::string>, Status>& reply) const{
    if (!reply)
    {
        if (reply.error()) //errors are printed in client_commandhandler
        {
            return;
        }
    }
    else
    {
        std::vector<std::string> vec = *reply;
        cout << "Reply from server: " << endl;
        for (string i: vec) {
            std::cout << i << endl;
        }
        cout << "" << endl;
    }
}

Expected<int, InputStatus> Client_commanddecoder::stringToInt(const std::string& p) const{
    try {
        return std::stoi(p);

    } catch (const std::invalid_argument&) {
        return InputStatus::IdNotNumber;

    } catch (const std::out_of_range&) {
        return InputStatus::IdTooBig;
    }
    
}

Expected<std::string, InputStatus> Client_commanddecoder::readInputString(std::istream& is) const {
    // Skip any leading whitespace, including leftover newline

    std::string str;
    std::getline(is, str);
    if (str.empty())
    {
        return InputStatus::EmptyInput;
    }
    else if (str == "exit")
    {
        return InputStatus::Exit;
    }
    removeWhitespaces(str);
    return str;
}

Expected<int, InputStatus> Client_commanddecoder::readInputId(std::istream& is) const {
    std::string str;
    is >> str;
    if (str == "exit")
    {
        return InputStatus::Exit;
    }
    auto value = stringToInt(str);
    if (!value)
    {
        return value.error();
    }
    int valueInt = *value;
    if (valueInt < 0)
    {
        return InputStatus::IdLessZero;
    }
    return valueInt;

}

std::string Client_commanddecoder::removeWhitespaces(std::string& str) const {
    str.erase(
        std::remove_if(str.begin(), str.end(),
            [](unsigned char c) { return std::isspace(c); }),
        str.end());

    return str;
}
void Client_commanddecoder::HELP_COM() const{
    cout << "List of commands: " << endl;
    cout << "List newsgroups: LIST_NG" << endl;
    cout << "Create a newsgroup: CREATE_NG " << endl;
    cout << "Delete a newsgroup: DELETE_NG " << endl;
    cout << "List articles in newsgroup: LIST_ART" << endl;
    cout << "Create an article in newsgroup: CREATE_ART" << endl;
    cout << "Delete an article: DELETE_ART" << endl;
    cout << "Get an article: GET_ART" << endl; 
    /* cout << "Create a newsgroup: CREATE_NG <title>" << endl;
    cout << "Delete a newsgroup: DELETE_NG <NG_id_number>" << endl;
    cout << "List articles in newsgroup: LIST_ART <NG_id_number>" << endl;
    cout << "Create an article in newsgroup: CREATE_ART <NG_id_number> <title> <author> <text>" << endl;
    cout << "Delete an article: DELETE_ART <NG_id_number> <ART_id_number>" << endl;
    cout << "Get an article: GET_ART <NG_id_number> <ART_id_number>" << endl; */
}

void Client_commanddecoder::printConnectionError(const Status& error) const{
    switch (error)
    {
    case ProtocolViolation:
        cout << "Error protocol violation" << endl;
        break;
    case ConnectionClosed:
        cout << "Error Connection is closed" << endl;
        break;
    case FailedTransfer:
        cout << "Error Failed transfer" << endl;
        break;
    case InvalidArguments:
        cout << "Error Invalid arguments" << endl;
        break;
    case Success:
        cout << "Should not come here!!! " << endl;
        break;
    
    default:
        break;
    }
}
void Client_commanddecoder::printInputError(const InputStatus& error) const{

    switch (error)
    {
    case InputStatus::EmptyInput:
        cout << "Error Empty Input, Type again" << endl;
        break;
    case InputStatus::Exit:
        cout << "Exeting" << endl;
        break;
    case InputStatus::IdLessZero:
        cout << "Please input Id bigger than zero" << endl;
        break;
    case InputStatus::IdTooBig:
        cout << "Try inputing smaller number" << endl;
        break;
    case InputStatus::IdNotNumber:
        cout << "Id needs to be a number" << endl;
    default:
        break;
    }
}
