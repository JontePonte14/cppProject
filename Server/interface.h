#ifndef INTERFACE_H
#define INTERFACE_H
#include "article.h"
#include "databaseMS.h"
#include "databaseDS.h"
#include "database.h"
#include <string>
#include <list>

class Interface
{
private:
    /* data */
    Database * db;    
    DatabaseMS db1;
    DatabaseDS db2;
    int activeDB;

public:
    
    std::vector<std::string> listGroup();
    bool makeGroup(std::string groupName);
    bool removeGroup(int groupID);

    std::vector<std::string> listArticle(int groupID);
    bool makeArticle(int groupNBR,std::string articleTitle, std::string articleAuthor, std::string text);
    bool removeArticle(int groupID, int articleID);
    Article getArticle(int groupID, int articleID);

    int switchDateBase();

    Interface(/* args */);
    Interface(int activeDB);
    ~Interface() = default;
};



#endif