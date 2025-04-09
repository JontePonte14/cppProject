#include "DatabaseDS.h"
#include "Article.h"
#include <string>
#include <filesystem>
#include <iostream>
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
    fs::path newGroup = root / groupName;

    if (fs::exists(newGroup)) {
        std::cout << "Group exist already" << std::endl;
        return false;
    }
    fs::create_directory(newGroup);
    return true;
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


