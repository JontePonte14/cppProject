#include "databaseDS.h"
#include "article.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json.hpp>
namespace fs=std::filesystem;
using json = nlohmann::json;

DatabaseDS::DatabaseDS(const std::filesystem::path& basePath){
    root = basePath;
    fs::create_directory(root);
    return;
}

std::string DatabaseDS::listGroup(){
    return "-1";
}

bool DatabaseDS::makeGroup(const std::string& name){

    return false;
}

bool DatabaseDS::removeGroup(const std::string& name){

    return false;
}

std::vector<Article> DatabaseDS::listArticle(){
    // Ordningen för skötas av interface tycker jag.
    return articles;
}

bool DatabaseDS::makeArticle(Article& article){

    return false;
}

bool DatabaseDS::removeArticle(std::string articleGroup, std::string articleName, int articleID){

    return false;
}

Article DatabaseDS::getArticle(std::string articleGroup, std::string articleName, int articleID){
    return articles[0];
}


