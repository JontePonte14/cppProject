#include "databaseDS.h"
#include "article.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <map>
#include <ctime>
namespace fs=std::filesystem;
using json = nlohmann::json;

DatabaseDS::DatabaseDS(const std::filesystem::path& basePath){
    root = basePath;
    fs::create_directory(root);
    return;
}

std::string DatabaseDS::listGroup(){
    std::vector<std::string> newsGroups;
    std::string newsGroupSorted;

    std::map<std::time_t, std::string> newsGroupsMap;

    for (auto const& dir_entry : fs::directory_iterator{root}) {
        if (dir_entry.is_directory()) {
            fs::path createdFilePath = dir_entry.path() / ".created";

            if (fs::exists(createdFilePath)) {
                // Getting the time stamp from the .created file
                std::ifstream createdFile(createdFilePath);
                std::string timeStamp;
                std::getline(createdFile, timeStamp);

                // convert times stamp to time_t
                std::tm tm = {};
                std::istringstream ss(timeStamp);
                ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
                std::time_t timestamp = std::mktime(&tm);

                newsGroupsMap[timestamp] = dir_entry.path().filename().string();
            }
        }

    }

    // Appending the order oldest to newest to a string
    for (const auto& [timestamp, group] : newsGroupsMap) {
        newsGroupSorted = newsGroupSorted + group + " ";
    }

   return newsGroupSorted;
}

bool DatabaseDS::makeGroup(const std::string& name){
    fs::path newGroup = root / name;

    if (groupExist(newGroup)){
        std::cerr << "Error: Group already exist" << std::endl;
        return false;
    }

    // creates new folder with a .created file
    fs::create_directory(newGroup);
    std::ofstream createdFile(newGroup / ".created");
    createdFile << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    createdFile.close();

    return true;
}

bool DatabaseDS::removeGroup(const std::string& name){
    fs::path groupName = root / name;

    if (!groupExist(groupName)) {
        return false;
    }
    return fs::remove_all(groupName);
}

std::vector<Article> DatabaseDS::listArticle(){
    // Ordningen för skötas av interface tycker jag.
    return articles;
}

bool DatabaseDS::makeArticle(Article& article){
    fs::path groupName = root / article.getGroupName();

    if (!groupExist(groupName)){
        return false;
    }

    article.setID(999);
    // Overloading function in article.h
    json newArticleFile = article;

    // Saves the file
    std::string filename = std::to_string(article.getID()) + "_" + article.getTitle();
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

bool DatabaseDS::removeArticle(std::string articleGroup, std::string articleName, int articleID){
    fs::path groupName = root / articleGroup;

    if (!groupExist(groupName)) {
        return false;
    }

    std::string filename = std::to_string(articleID) + "_" + articleName;
    fs::path filePath = groupName / filename;
    
    if (!fs::exists(filePath)) {
        std::cerr << "The article doesn't exist, Article wasn't removed" << std::endl;
        return false;
    }
    // if return false so was the articleID or articleName wrong
    return fs::remove(filePath);
}

Article DatabaseDS::getArticle(std::string articleGroup, std::string articleName, int articleID){
    fs::path groupName = root / articleGroup;
    Article article;

    if (!groupExist(groupName)) {
        return article;
    }

    std::string filename = std::to_string(articleID) + "_" + articleName;
    fs::path filePath = groupName / filename;

    json articleJson;
    std::ifstream inFile(filePath);

    if (!inFile) {
        std::cerr << "File was not found" << std::endl;
        return article;
    }

    inFile >> articleJson;

    // Overloading function in article.
    article = articleJson;
    
    return article;
}

// help functions
bool DatabaseDS::groupExist(const fs::path& groupName) {
    if (!fs::exists(groupName) && groupName != dataFilePath) {
        std::cerr << "Error: Group doesn't exist" << std::endl;
        return false;
    }
    return true;
}


