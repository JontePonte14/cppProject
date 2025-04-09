#ifndef DATABASEDS_H
#define DATABASEDS_H

#include "json.hpp"
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
    bool makeGroup(const std::string& name);
    bool removeGroup(const std::string& name);

    std::vector<Article> listArticle();
    bool makeArticle(Article& article);
    bool removeArticle(std::string articleGroup, std::string articleName, int articleID);
    Article getArticle(std::string articleGroup, std::string articleName, int articleID);
private:
    /* data */
    std::filesystem::path root;

    // Fast access?
    std::vector<std::string> newsGroups;
    std::vector<Article> articles;
};

#endif