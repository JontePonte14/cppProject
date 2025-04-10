#ifndef INTERFACE_H
#define INTERFACE_H
#include "Article.h"
#include "DatabaseMS.h"
#include "DatabaseDS.h"
#include <string>
#include <list>

class interface
{
private:
    /* data */
    DatabaseDS db1;
    DatabaseMS db2;
    //db2
    int activeDB;

public:
    
    std::string listGroup();
    bool makeGroup();
    bool removeGroup();

    std::string listArticle(int groupID);
    bool makeArticle(int groupID);
    bool removeArticle();
    Article getArticle(int groupID, int articleID);

    int switchDateBase();

    interface(/* args */);
    ~interface();
};

interface::interface(/* args */)
{
}

interface::~interface()
{
}
#endif