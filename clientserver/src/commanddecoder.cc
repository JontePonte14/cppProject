#include "commanddecoder.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using std::string;
using std::cout;
using std::cin;
using std::endl;


commanddecoder::commanddecoder(const Connection& conn){

}

void commanddecoder::com_decode(std::istream& input){
    string command;
    input >> command;

std::transform(command.begin(), command.end(), command.begin(),
    [](unsigned char c){ return std::tolower(c); });


    if (input.fail())
    {
        cout << "FAIL! command needs to be string" << endl;
    }
    else
    {
        if (command == "help_com")
        {
            HELP_COM();
        }
        //add more commands
        else
        {
            cout << "FAIL! no such command exists, type help_com for command list" << endl;
        }
        
    }
    
}

void commanddecoder::HELP_COM(){
    cout << "List of commands: " << endl;
}
