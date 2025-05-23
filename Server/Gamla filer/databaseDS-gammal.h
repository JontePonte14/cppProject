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

    std::vector<std::string> listGroup();
    bool makeGroup(const std::string& name);
    bool removeGroup(int groupID);

    std::vector<std::pair<std::string, int>> listArticle(int groupID);
    bool makeArticle(Article& article);
    bool removeArticle(int groupID, int articleID);
    Article getArticle(int groupID, int articleID);
        


private:
    /* data */
    std::filesystem::path root;
    static int groupIDnbr;
    static int groupIDnbrMax;
    // increment id for each new article
    void idIncr();

    //Help functions
    bool groupExists(const std::filesystem::path& groupName);
    void saveIdNbr();
    void loadIdNbr();
};

#endif