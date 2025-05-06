#include "interface.h"
#include <string>
#include <list>
#include <ctime>
#include <iostream>


int Interface::getAtiveDB()
{
    return activeDB;
}

Interface::Interface(int activeDB) //send in the stating database
{
    this->activeDB = activeDB;
    if(activeDB == 1)
    {
        db = &db1; //MS
    }
    else
    {
        db = &db2;//DS
    }
}
Interface::Interface(){ //default constructor, user input
    activeDB = 1;
    db = & db1;
    int input;
    while (true) {
        std::cout << "Enter which database you want to connect to : \n"
        "[1] Memory storage\n"
        "[2] Disk storage\n";
        if (std::cin >> input && (input == 1 || input == 2)) {
            break; // valid input
        }else {
            std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        }
    }
    if (input == 1) {
        db = &db1;
        activeDB = 1;
        std::cout << "Interface conected to DB 1 (Memory storage)" << std::endl;
    } else {
        std::cout << "Interface conected to DB 2 (Disk storage)" << std::endl;
        db = &db2;
        activeDB = 2;
    }

  
}

std::vector<Database::ListObject> Interface::listGroup(){return db->listGroup();}

bool Interface::makeGroup(std::string groupName){ return db->makeGroup(groupName);}

Database::RemoveStatus Interface::removeGroup(int groupID){    return db->removeGroup(groupID);}

std::vector<Database::ListObject>   Interface::listArticle(int groupID){ return db->listArticle(groupID);}


bool Interface::makeArticle(int groupNBR,std::string articleTitle, std::string articleAuthor, std::string text)
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::string date =  std::to_string(now->tm_year + 1900) + "-" + std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_mday);
   
    Article article = Article(articleTitle, articleAuthor, text);
  
    return db->makeArticle(groupNBR, article);


    
}

Database::RemoveStatus Interface::removeArticle(int groupID, int articleID){    return db->removeArticle(groupID, articleID);}
Expected<Article, Database::RemoveStatus> Interface::getArticle(int groupID, int articleID){    return db->getArticle(groupID, articleID);}
int Interface::switchDateBase()
{
    if(activeDB == 1)
    {
        activeDB = 2;
        db = &db2;
    }
    else
    {
        activeDB = 1;
        db = &db1;
    }
    return activeDB;
}        
