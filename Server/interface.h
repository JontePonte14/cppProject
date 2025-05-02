#ifndef INTERFACE_H
#define INTERFACE_H
#include "article.h"
#include "databaseMS.h"
#include "databaseDS.h"
#include <string>
#include <list>

class Interface
{
private:
    /* data */
    DatabaseDS db1;
    DatabaseMS db2;
    

    int activeDB;

public:
    
    std::string listGroup();
    bool makeGroup(std::string groupName);
    bool removeGroup(int groupID);

    std::string listArticle(int groupID);
    bool makeArticle(int groupNBR,std::string artivleTitle, std::string articleAuthor, std::string text);
    bool removeArticle(int groupID, int articleID);
    Article getArticle(int groupID, int articleID);

    int switchDateBase();

    Interface(/* args */);
    ~Interface();
};

Interface::Interface(/* args */)
{
}

Interface::~Interface()
{
}
#endif