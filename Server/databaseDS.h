#ifndef DATABASEDS_H
#define DATABASEDS_H

#include "json.hpp"
#include "article.h"
#include <string>
#include <vector>
#include <filesystem>
using json = nlohmann::json;


class DatabaseDS
{
public:
    DatabaseDS(const std::filesystem::path& basePath);
    ~DatabaseDS() = default;

    std::string listGroup();
    bool makeGroup(const std::string& name);
    bool removeGroup(const std::string& name);

    std::vector<Article> listArticle(std::string groupName);
    bool makeArticle(Article& article);
    bool removeArticle(std::string articleGroup, std::string articleName, int articleID);
    Article getArticle(std::string articleGroup, std::string articleName, int articleID);
private:
    /* data */
    std::filesystem::path root;

    //Help functions
    bool groupExist(const std::filesystem::path& groupName);
};

#endif