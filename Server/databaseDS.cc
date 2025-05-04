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
        saveGroupIdNbr();

    } else {
        // We load the old IDnbr
        loadGroupIdNbr();
    }
    return;
}

std::vector<std::string> listGroup(){
    return;
}

bool DatabaseDS::makeGroup(const std::string& name){
    if (groupNameExists(name)) {
        std::cerr << "Group already exist" << std::endl;
        return false;
    }

    std::string groupName = name + "_" + std::to_string(groupIDnbr);
    idIncr();
    saveGroupIdNbr();
    fs::path fullPathToGroup = root / groupName;
    
    // creates new folder with a .created file
    fs::create_directory(fullPathToGroup);
    std::ofstream createdFile(fullPathToGroup / ".created");
    createdFile << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    createdFile.close();

    return true;
}

bool DatabaseDS::removeGroup(int groupID){
    return false;
}

std::vector<std::pair<std::string, int>> DatabaseDS::listArticle(int groupID){
    std::vector<std::pair<std::string, int>> sortedArticles;
    return sortedArticles;
}

bool DatabaseDS::makeArticle(int group, Article article){
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
bool DatabaseDS::groupNameExists(const std::string& name) {
    // iterate to compare that the group doesn't exists.
    for (const auto& entry : fs::directory_iterator(root)){
        if (!entry.is_directory()){
            continue;
        } else {
            std::string folderName = entry.path().filename().string();
            auto underscorePos = folderName.rfind("_");
            if (underscorePos =! std::string::npos){
                std::string existingGroupName = folderName.substr(0, underscorePos);
                if (existingGroupName == name){
                    return true; // Found a group with the same name
                }
            }   
        }

    }
    return false; // Did not find a group with the same name
}

void DatabaseDS::saveGroupIdNbr(){
    std::string fileName = "groupId_number.txt";

    std::ofstream outFile(root/fileName);
    if (!outFile) {
        std::cerr << "There was a problem saving groupId_number.txt file" << std::endl;
    }

    outFile << groupIDnbr;
    outFile.close();
}

void DatabaseDS::loadGroupIdNbr(){
    std::string fileName = "groupId_number.txt";
    std::ifstream inFile(root / fileName);

    if (!inFile) {
        std::cerr << fileName << " was not found" << std::endl;
    }

    inFile >> groupIDnbr;
}

