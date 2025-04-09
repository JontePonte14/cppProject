#ifndef DATABASEDS_H
#define DATABASEDS_H

#include "Article.h"
#include <string>
#include <vector>
#include <filesystem>

class DatabaseDS
{
public:
    DatabaseDS(const std::filesystem::path& basePath);
    ~DatabaseDS() = default;

    std::vector<std::string> listGroup();
    bool makeGroup(const std::string& groupName);
    bool removeGroup(const std::string& groupName);

    std::vector<Article> listArticle();
    bool makeArticle(const Article& article);
    bool removeArticle(std::string articleGroup, std::string articleName, int articleID);
    Article getArticle(std::string articleGroup, std::string articleName, int articleID);
private:
    /* data */
    std::filesystem::path root;

    // Fast access?
    std::vector<std::string> newsGroups;
    std::vector<Article> articles;
    Article temp;
};

#endif