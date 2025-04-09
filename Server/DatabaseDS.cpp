#include "DatabaseDS.h"
#include "Article.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json.hpp>
namespace fs=std::filesystem;
using json = nlohmann::json;

DatabaseDS::DatabaseDS(const std::filesystem::path& basePath){
    root = basePath;
    fs::create_directory(basePath);
    return;
}

std::vector<std::string> DatabaseDS::listGroup(){
    return newsGroups;
}

bool DatabaseDS::makeGroup(const std::string& name){
    fs::path newGroup = root / name;

    if (fs::exists(newGroup)) {
        std::cout << "Group exist already" << std::endl;
        return false;
    }
    fs::create_directory(newGroup);
    return true;
}

bool DatabaseDS::removeGroup(const std::string& name){
    fs::path groupName = root / name;

    if (!fs::exists(groupName)){
        // Group doesn't exist, nothing was removed
        std::cout << "Group doesn't exist, nothing was removed" << std::endl;
        return false;
    }
    return fs::remove_all(groupName);
}

std::vector<Article> DatabaseDS::listArticle(){
    return articles;
}

bool DatabaseDS::makeArticle(Article& article){
    fs::path groupName = root / article.getGroupName();

    if (!fs::exists(groupName)) {
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
        std::cout << "Error couldn't open file" << filePath << std::endl;
        return false;
    }

    outFile << newArticleFile.dump(4);
    outFile.close();

    return true;
}

bool DatabaseDS::removeArticle(std::string articleGroup, std::string articleName, int articleID){
    return false;
}

Article DatabaseDS::getArticle(std::string articleGroup, std::string articleName, int articleID){
    return temp;
}


