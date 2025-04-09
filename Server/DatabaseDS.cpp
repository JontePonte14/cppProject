#include "DatabaseDS.h"
#include "Article.h"
#include <string>
#include <filesystem>
namespace fs=std::filesystem;

DatabaseDS::DatabaseDS(const std::filesystem::path& basePath){
    root = basePath;
    fs::create_directory(basePath);
    return;
}

std::vector<std::string> DatabaseDS::listGroup(){
    return newsGroups;
}

bool DatabaseDS::makeGroup(const std::string& groupName){
    return false;
}

bool DatabaseDS::removeGroup(const std::string& groupName){
    return false;
}

std::vector<Article> DatabaseDS::listArticle(){
    return articles;
}

bool DatabaseDS::makeArticle(const Article& article){
    return false;
}

bool DatabaseDS::removeArticle(std::string articleGroup, std::string articleName, int articleID){
    return false;
}

Article DatabaseDS::getArticle(std::string articleGroup, std::string articleName, int articleID){
    return temp;
}


