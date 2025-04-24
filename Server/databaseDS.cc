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
    fs::path newGroup = root / name;

    if (groupExist(newGroup)){
        std::cerr << "Error: Group already exist" << std::endl;
        return false;
    }

    fs::create_directory(newGroup);
    return true;
}

bool DatabaseDS::removeGroup(const std::string& name){
    fs::path groupName = root / name;

    if (groupExist(groupName)) {
        return false;
    }
    return fs::remove_all(groupName);
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

// help functions
bool DatabaseDS::groupExist(const std::string& name) {
    fs::path groupName = root / name;

    if (!fs::exists(groupName) && groupName != dataFilePath) {
        std::cerr << "Error: Group doesn't exist" << std::endl;
        return false;
    }
    return true;
}


