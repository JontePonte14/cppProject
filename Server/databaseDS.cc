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
    
    fs::path temp {"data"};
    dataFilePath = root / temp;
    std::cout << "dataFile is : " << fs::exists(dataFilePath) << std::endl;
    if (!fs::exists(dataFilePath)) {
        std::cout << "data file is gone" << std::endl;
        // If the data file is gone. Then we have lost track of the 
        // newsgroup info date. So we'll just clear everything out.
        fs::remove_all(root);
        fs::create_directory(basePath);

        json jsonData;
        jsonData["current_id"] = -1;

        std::string filename = "data";
        std::ofstream outFile(root);
        if (!outFile) {
            std::cerr << "Error couldn't open file" << root << std::endl;
            return;
        }

        outFile << jsonData.dump(4);
        outFile.close();
    }
    return;
}

std::string DatabaseDS::listGroup(){
    std::vector<std::string> newsGroups;

    // Måste lägga till så att ordningen är äldst grupp först
    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : std::filesystem::directory_iterator{root}) {
         //std::cout << dir_entry.path() << '\n';
        if (dir_entry.is_directory()) {
            std::string newsGroup = dir_entry.path().filename().string();
            newsGroups.push_back(newsGroup);
        }
    }
    return newsGroups[0];
}

bool DatabaseDS::makeGroup(const std::string& name){
    fs::path newGroup = root / name;

    if (fs::exists(newGroup) && (dataFilePath != newGroup)) {
        std::cerr << "Group exist already" << std::endl;
        return false;
    }
    fs::create_directory(newGroup);
    return true;
}

bool DatabaseDS::removeGroup(const std::string& name){
    fs::path groupName = root / name;

    if (!fs::exists(groupName) && (dataFilePath != groupName)){
        // Group doesn't exist, nothing was removed
        std::cerr << "Group doesn't exist, nothing was removed" << std::endl;
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

    if (!fs::exists(groupName) && groupName != dataFilePath) {
        std::cout << "Group doesn't exist, create one first" << std::endl;
        return false;
    }
    article.setID(999);
    json newArticleFile;
    newArticleFile["id"] = article.getID();
    newArticleFile["groupName"] = article.getGroupName();
    newArticleFile["title"] = article.getTitle();
    newArticleFile["author"] = article.getAuthor();
    newArticleFile["date"] = article.getDate();
    newArticleFile["body"] = article.getBody();

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

    if (!fs::exists(groupName)) {
        std::cerr << "Group doesn't exist, Article wasn't removed" << std::endl;
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

    if (!fs::exists(groupName)) {
        std::cerr << "Group doesn't exist, couldn't get article" << std::endl;
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
    
    article = Article(
        articleJson["groupname"],
        articleJson["title"],
        articleJson["author"],
        articleJson["date"],
        articleJson["id"],
        articleJson["body"]
    );
    return article;
}


