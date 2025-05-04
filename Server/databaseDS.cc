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
#include <charconv> // for std::from_chars

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

std::vector<std::pair<std::string, int>> DatabaseDS::listGroup(){
    std::vector<std::pair<std::string, int>> listOfGroups;
    // std::string tempGroupName = "temp";
    int tempIdNbr;

    for (auto const& dir_entry : fs::directory_iterator(root)){
        if (!dir_entry.is_directory()) {
            continue;
        } else {
            std::string folderName = dir_entry.path().filename().string();
            auto underscorePos = folderName.rfind("_");
            // Splitting the string to create a pair
            std::string tempGroupName = folderName.substr(0, underscorePos);
            std::string stringIdNbr = folderName.substr(underscorePos + 1);
            std::from_chars(stringIdNbr.data(), stringIdNbr.data() + stringIdNbr.size(), tempIdNbr); // Maybe add check to see it works
            listOfGroups.emplace_back(tempGroupName, tempIdNbr);
        }
    }

    std::sort(listOfGroups.begin(), listOfGroups.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });

    return listOfGroups;
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
    saveArticleIdNbr(groupName, 1);
    return true;
}

bool DatabaseDS::removeGroup(int groupID){
    std::string folderName = findGroupWithID(groupID);
    if (folderName == "") {
        std::cerr << "No group was found" << std::endl;
        return false;
    }
    fs::path pathToFolder = root / folderName;
    return fs::remove_all(pathToFolder);
}

std::vector<std::pair<std::string, int>> DatabaseDS::listArticle(int groupID){
    std::vector<std::pair<std::string, int>> sortedArticles;
    std::string groupFolder = findGroupWithID(groupID);

    if (groupFolder == "") {
        std::cerr << "No group was found";
        return {};
    }

    return sortedArticles;
}

bool DatabaseDS::makeArticle(int group, Article article){
    std::string groupFolder = findGroupWithID(group);

    if (groupFolder == "") {
        std::cerr << "No group was found: ";
        return false;
    }
    
    int articleID = loadArticleIdNbr(groupFolder);
    article.setID(articleID);
    // Overloading function in article.h
    json newArticleFile = article;

    // Saves the file
    std::string filename =  article.getTitle() + "_" + std::to_string(articleID) + ".json";
    fs::path filePath = root / groupFolder / filename;
    
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "Error couldn't open file" << filePath << std::endl;
        return false;
    }

    outFile << newArticleFile.dump(4);
    outFile.close();

    saveArticleIdNbr(groupFolder, articleID + 1);
    return true;
}

bool DatabaseDS::removeArticle(int groupID, int articleID){
    fs::path articlePath = findArticlePath(groupID, articleID);

    if (articlePath.empty()) {
        return false; // Couldn't find group or article check error message
    }
    return fs::remove(articlePath);
}

Article DatabaseDS::getArticle(int groupID, int articleID){
    Article article;
    fs::path articlePath = findArticlePath(groupID, articleID);
    if (articlePath.empty()) {
        return article; // Couldn't find group or article check error message
    }

    json articleJson;
    std::ifstream inFile(articlePath);

    if (!inFile) {
        std::cerr << "File was not found" << std::endl;
        return article;
    }

    inFile >> articleJson;

    // Overloading function in article.
    article = articleJson;
    
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
            if ((underscorePos != std::string::npos)){
                std::string existingGroupName = folderName.substr(0, underscorePos);
                if (existingGroupName == name){
                    return true; // Found a group with the same name
                }
            }   
        }

    }
    return false; // Did not find a group with the same name
}

std::string DatabaseDS::findGroupWithID(const int& groupID){
    // iterate to find the group with the correct ID
    for (const auto& entry : fs::directory_iterator(root)){
        if (!entry.is_directory()){
            continue;
        } else {
            std::string folderName = entry.path().filename().string();
            auto underscorePos = folderName.rfind("_");
            if ((underscorePos != std::string::npos)){
                std::string folderGroupID = folderName.substr(underscorePos+1);
                if (folderGroupID == std::to_string(groupID)){
                    return folderName; // Found group ID
                }
            }   
        }

    }
    return ""; // Did not find a group with the same name
}

fs::path DatabaseDS::findArticlePath(const int& groupID, const int& articleID){
    std::string groupName = findGroupWithID(groupID);

    if (groupName == "") {
        std::cerr << "Couldn't find group" << std::endl;
        return fs::path{};
    }

    fs::path folderPath = root / groupName;

    for (const auto& entry : fs::directory_iterator(folderPath)){
        fs::path filePath = entry.path();
        if (filePath.extension() == ".json") {
            std::string stemName = filePath.stem().string();
            auto underscorePos = stemName.rfind("_");
            if ((underscorePos != std::string::npos)) {
                std::string tempArticleID = stemName.substr(underscorePos+1);

                if (tempArticleID == std::to_string(articleID)) {
                    return filePath;
                }

            }

        }
    }
    std::cerr << "Didn't find the article in the given group" << std::endl;
    return fs::path{};
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

void DatabaseDS::saveArticleIdNbr(const std::string& groupFolderName,  const int& currentID){
    std::string fileName = "articleID_number.txt";

    std::ofstream outFile(root/groupFolderName/fileName);
    if (!outFile) {
        std::cerr << "There was a problem saving " << fileName << std::endl;
    }

    outFile << currentID;
    outFile.close();
}


int DatabaseDS::loadArticleIdNbr(const std::string& groupFolderName){
    std::string fileName = "articleID_number.txt";
    std::ifstream inFile(root / groupFolderName / fileName);
    int articleIDnbr; 

    if (!inFile) {
        std::cerr << fileName << " was not found" << std::endl;
    }

    inFile >> articleIDnbr;

    return articleIDnbr;
}

