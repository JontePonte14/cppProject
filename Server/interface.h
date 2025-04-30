#ifndef INTERFACE_H
#define INTERFACE_H
#include "article.h"
#include "databaseMS.h"
#include "databaseDS.h"
#include <string>
#include <list>

class interface
{
private:
    /* data */
    DatabaseDS db1;
    DatabaseMS db2;
    

    int activeDB;

public:

    interface ();
    ~interface() = default;
    
    std::string listGroup();
    bool makeGroup(const std::string& name);
    bool removeGroup(const std::string& name);

    std::vector<std::pair<std::string, int>> listArticle(std::string name);
    bool makeArticle(Article& article);
    bool removeArticle(std::string articleGroup, std::string articleName, int articleID);
    Article getArticle(std::string articleGroup, std::string articleName, int articleID);

    int switchDateBase();

    interface(/* args */);
    ~interface();
};
#endif