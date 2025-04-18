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
    
    std::list<std::string> listGroup();
    bool makeGroup();
    bool removeGroup();

    std::list<Article> listArticle();
    bool makeArticle();
    bool removeArticle();
    Article getArticle();

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