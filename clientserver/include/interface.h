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
    
    std::vector<Database::ListObject> listGroup();
    bool makeGroup(std::string groupName);
    Database::RemoveStatus removeGroup(int groupID);

    std::vector<Database::ListObject> listArticle(int groupID);
    bool makeArticle(int groupNBR,std::string articleTitle, std::string articleAuthor, std::string text);
    Database::RemoveStatus removeArticle(int groupID, int articleID);
    auto getArticle(int groupID, int articleID) -> Expected<Article, Database::RemoveStatus>;

    bool switchDateBase(int dataBaseIndex);
    int getAtiveDB();

    Interface(/* args */);
    Interface(int activeDB);
    ~Interface() = default;
};



#endif