#ifndef DATABASEDS_H
#define DATABASEDS_H

#include "Article.h"
#include <string>
#include <vector>
#include <filesystem>

class DatabaseDS
{
public:
    DatabaseDS(/* args */);
    ~DatabaseDS() = default;

    std::string listGroup();
    bool makeGroup(std::string groupName);
    bool removeGroup();

    std::vector<Article> listArticle();
    bool makeArticle();
    bool removeArticle();
    Article getArticle();
private:
    /* data */
    std::vector<std::string> newsGroups;
    std::vector<Article> articles;
    Article temp;
};
#endif