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

#define RETURN_IF_ERROR(input)        \
    if (!(input)) {                         \
        return;                             \
    }

Client_commanddecoder::Client_commanddecoder(const std::shared_ptr<Connection>& conn) : comhand(conn) { //replace with messagehandler

}

void Client_commanddecoder::com_decode(std::istream& is){
    std::string command;
    std::getline(is, command);

    removeWhitespaces(command);

    std::transform(command.begin(), command.end(), command.begin(),
    [](unsigned char c){ return std::tolower(c); });

    if (is.fail()) {
        cout << "STREAM FAIL" << endl;
    }

    if (command == "help_com") {
        HELP_COM();
    }

    else if(command == "list_ng"){
        LIST_NG();
    }

    else if(command == "create_ng"){
        CREATE_NG(is);
    }

    else if(command == "delete_ng"){
        DELETE_NG(is);
    }

    else if(command == "list_art"){
        LIST_ART(is);
    }

    else if(command == "create_art"){
        CREATE_ART(is);
    } 

    else if(command == "delete_art"){
        //cout << "Function not implemented " << endl;
        DELETE_ART(is);
    }
    else if(command == "get_art"){
        //cout << "Function not implemented " << endl;
        GET_ART(is);
    }
    else if (command == "exit") {
        
    }
    else if (command == "change_database")
    {
        //cout << "Function not implemented " << endl;
        CHANGE_DATABASE(is);
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
    cout << "Type the name of the newsgroup you want to create (or type exit): " << endl;
    auto title = readInputString(is);
    RETURN_IF_ERROR(title);
    //Outputs
    auto reply = comhand.CREATE_NG(*title);
    printReply(reply);

}

 void Client_commanddecoder::DELETE_NG(std::istream& is) {
    //Input
    cout << "Type the Index number of the newsgroup you want to delete (or type exit): " << endl;
    auto Id = readInputId(is);
    RETURN_IF_ERROR(Id);
    //Output
    auto reply = comhand.DELETE_NG(*Id);
    printReply(reply);
} 

void Client_commanddecoder::LIST_ART(std::istream& is) {
    //Input
    cout << "Type the Index number of the newsgroup you want to see (or type exit): " << endl;
    auto Id = readInputId(is);
    RETURN_IF_ERROR(Id);
    //Output
    auto reply = comhand.LIST_ART(*Id);
    printReply(reply);
}

void Client_commanddecoder::CREATE_ART(std::istream& is) {
    //Input
    cout << "Type the Index number of the newsgroup, where you want your article created (or type exit): " << endl;
    auto Id = readInputId(is);
    RETURN_IF_ERROR(Id);
    cout << "Type the Title (or type exit): " << endl;
    auto title = readInputString(is);
    RETURN_IF_ERROR(title);
    cout << "Type the author (or type exit): " << endl;
    auto author = readInputString(is);
    RETURN_IF_ERROR(author);
    cout << "Type the text (or type exit) (Type a string for now): " << endl;
    auto text = readInputString(is);
    RETURN_IF_ERROR(text);
    //Output
    auto reply = comhand.CREATE_ART(*Id, *title, *author, *text);
    printReply(reply);
}

void Client_commanddecoder::DELETE_ART(std::istream& is) {
    //Input
    cout << "Type the Index number of the newsgroup, where article is located (or type exit): " << endl;
    auto Id = readInputId(is);
    RETURN_IF_ERROR(Id);
    cout << "Type the Index number of the article to be deleted (or type exit): " << endl;
    auto IdArt = readInputId(is);
    RETURN_IF_ERROR(IdArt);
    //Output
    auto reply = comhand.DELETE_ART(*Id, *IdArt);
    printReply(reply);
}

void Client_commanddecoder::GET_ART(std::istream& is) {
    //Input
    cout << "Type the Index number of the newsgroup, where article is located (or type exit): " << endl;
    auto Id = readInputId(is);
    RETURN_IF_ERROR(Id);
    cout << "Type the Index number of the article to be retreived (or type exit): " << endl;
    auto IdArt = readInputId(is);
    RETURN_IF_ERROR(IdArt);
    //Output
    auto reply = comhand.GET_ART(*Id, *IdArt);
    printReply(reply);
}

void Client_commanddecoder::CHANGE_DATABASE(std::istream& is) {
    //Input
    cout << "Type the Index number of the database you want to switch to " << endl;
    auto Index = readInputId(is);
    //Output
    auto reply = comhand.CHANGE_DATABASE(*Index);
    printReply(reply);
}

void Client_commanddecoder::printReply(const Expected<std::vector<std::string>, Status>& reply) const{
    if (!reply && reply.error())
    {
        printConnectionError(reply.error());
        return;
        
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

    std::string str;
    std::getline(is, str);
    if (str.empty())
    {
        printInputError(InputStatus::EmptyInput);
        return readInputString(is); //recursive call untill correct input
    }
    else if (str == "exit")
    {
        printInputError(InputStatus::Exit);
        return InputStatus::Exit;
    }
    cout << "Client string is: " << str << endl;
    return str;
}

Expected<int, InputStatus> Client_commanddecoder::readInputId(std::istream& is) const {
    //ReadString
    auto str = readInputString(is);
    if (!str)
    {
        return str.error();
    }
    //Convert to int
    auto value = stringToInt(*str);
    if (!value)
    {
        printInputError(InputStatus::IdNotNumber);
        return readInputId(is); //recursive call untill correct input
    }
    int valueInt = *value;
    if (valueInt < ONE_INDEXING)
    {
        printInputError(InputStatus::IdTooBigIndex);
        return readInputId(is); //recursive call untill correct input
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
    cout << "change database: CHANGE_DATABASE" << endl; 
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
    case InputStatus::IdTooBigIndex:
        cout << "Please input Id bigger than " << (ONE_INDEXING -1) << endl;
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
