#include "databaseDS.h"
#include "article.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <map>
#include <ctime>
#include <utility>
#include <algorithm>

namespace fs=std::filesystem;
using json = nlohmann::json;

DatabaseDS::DatabaseDS(){
    root = "Newsgroup";
    if (fs::create_directory(root)) {
        // We create a new IDnbr
        groupIDnbr = 1;
        groupIDnbrMax = 1;
        saveIdNbr();

    } else {
        // We load the old IDnbr
        loadIdNbr();
    }
    return;
}

DatabaseDS::DatabaseDS(const std::filesystem::path& basePath){
    root = basePath;
    if (fs::create_directory(root)) {
        // We create a new IDnbr
        groupIDnbr = 1;
        groupIDnbrMax = 1;
        saveIdNbr();

    } else {
        // We load the old IDnbr
        loadIdNbr();
    }
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

std::vector<std::pair<std::string, int>> DatabaseDS::listArticle(int groupID){
    std::vector<std::pair<std::string, int>> sortedArticles;
    return sortedArticles;
}

bool DatabaseDS::makeArticle(Article& article){
    fs::path groupName = root / article.getGroupName();

    if (!fileExists(groupName)){
        return false;
    }

    article.setID(groupIDnbr);
    idIncr();
    saveIdNbr();
    // Overloading function in article.h
    json newArticleFile = article;

    // Saves the file
    std::string filename = std::to_string(article.getID()) + "_" + article.getTitle() + article.getDate() + "_" + ".json";
    fs::path filePath = groupName / filename;
    
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "Error couldn't open file" << filePath << std::endl;
        return false;
    }

    outFile << newArticleFile.dump(4);
    outFile.close();

    return true;
}

bool DatabaseDS::removeArticle(int groupID, int articleID){
    return false;
}

Article DatabaseDS::getArticle(int groupID, int articleID){
    Article article;

    return article;
}

void DatabaseDS::idIncr(){
    groupIDnbr++;
}

int DatabaseDS::groupIDnbr = -1;  // Initial value (will be overridden by loading)
int DatabaseDS::groupIDnbrMax = -1; // Initial value


// help functions
bool DatabaseDS::groupExists(const fs::path& fileName) {
    if (!fs::exists(fileName)) {
        std::cerr << "Error: Group doesn't exist" << std::endl;
        return false;
    }
    return true;
}

void DatabaseDS::saveIdNbr(){
    std::string fileName = "groupId_number.txt";

    std::ofstream outFile(root/fileName);
    if (!outFile) {
        std::cerr << "There was a problem saving groupId_number.txt file" << std::endl;
    }

    outFile << groupIDnbr;
    outFile.close();
}

void DatabaseDS::loadIdNbr(){
    std::string fileName = "groupId_number.txt";
    std::ifstream inFile(root / fileName);

    if (!inFile) {
        std::cerr << fileName << " was not found" << std::endl;
    }

    inFile >> groupIDnbr;
}

