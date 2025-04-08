#ifndef DATABASEDS_H
#define DATABASEDS_H

#include "Article.h"
#include <string>
#include <list>
#include <filesystem>

class DatabaseDS
{
public:
    DatabaseDS(/* args */);
    ~DatabaseDS() = default;

    std::string listGroup();
    bool makeGroup();
    bool removeGroup();

    std::list<Article> listArticle();
    bool makeArticle();
    bool removeArticle();
    Article getArticle();
private:
    /* data */
    std::list<std::string> newsGroups;
    std::list<Article> articles;
    Article temp;
};
#endif