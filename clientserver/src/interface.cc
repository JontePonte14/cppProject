#include "interface.h"
#include <string>
#include <list>
#include <ctime>



Interface::Interface(/* args */){
    activeDB = 1;
    db = & db1;


}

std::vector<std::string> Interface::listGroup()
{
    return db->listGroup();
}

bool Interface::makeGroup(std::string groupName)
{
    

    return db->makeGroup(groupName);
}

bool Interface::removeGroup(int groupID)
{
    return db->removeGroup(groupID);
    
}

std::string Interface::listArticle(int groupID){
    std::vector<std::pair<std::string, int>> list = db1.listArticle(groupID);
    std::vector<std::string> sortedNames;
    for (const auto& pair : list) {
        sortedNames.push_back(pair.first + " " + std::to_string(pair.second));
    }
    return "";
}


bool Interface::makeArticle(int groupNBR,std::string articleTitle, std::string articleAuthor, std::string text)
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::string date =  std::to_string(now->tm_year + 1900) + "-" + std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_mday);
   
    Article article = Article(articleTitle, date, articleAuthor, text);
  
    return db1.makeArticle(groupNBR, article);


    
}

bool Interface::removeArticle(int groupID, int articleID)
{
   
    return db->removeArticle(groupID, articleID);;
}

Article Interface::getArticle(int groupID, int articleID)
{

    return db->getArticle(groupID, articleID);
}
int Interface::switchDateBase()
{
    if(activeDB == 1)
    {
        activeDB = 2;
        // db = &db2;
    }
    else
    {
        activeDB = 1;
        db = &db1;
    }
    return activeDB;
}        
