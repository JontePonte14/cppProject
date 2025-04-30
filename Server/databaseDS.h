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
    // Default contructur creates a root folder called "Newsgroup"
    DatabaseDS();
    // Custom constructur makes it possible to decide the name of the root folder
    DatabaseDS(const std::filesystem::path& basePath);
    ~DatabaseDS() = default;

    std::string listGroup();
    bool makeGroup(const std::string& name);
    bool removeGroup(const std::string& name);

    std::vector<std::pair<std::string, int>> listArticle(std::string name);
    bool makeArticle(Article& article);
    bool removeArticle(std::string articleGroup, std::string articleName, int articleID);
    Article getArticle(std::string articleGroup, std::string articleName, int articleID);
private:
    /* data */
    std::filesystem::path root;
    static int IDnbr;
    // increment id for each new article
    void idIncr();

    //Help functions
    bool groupExist(const std::filesystem::path& groupName);
    void saveIdNbr();
    void loadIdNbr();
};

#endif