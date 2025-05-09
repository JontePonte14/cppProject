#include "databaseMS.h"
#include "database.h"
#include "article.h" 
#include <map>
#include <string>
#include <vector>
#include <iostream>



using namespace std;


size_t groupID = 1;
size_t articleID = 1;




struct Group{
    string name;

    map<int, Article> articles;
    Group() : name(""), articles() {}
    Group(const string& groupName)
    : name(groupName) {}
};

 
map<int, Group> memory;






vector<Database::ListObject> DatabaseMS::listGroup(){

    vector<Database::ListObject> groups;

    for (const auto& group : memory) {
        groups.emplace_back(group.second.name, group.first); // pair<name, groupID>
    }

    return groups;
}

bool  DatabaseMS::makeGroup(const std::string& name){
    for (const auto& group : memory) {
        if (group.second.name == name) { // Compare the pairs first element (group name)
            cerr << "Group already exists" << endl;
            return false; 
        }
    }

    memory[groupID] = Group(name);
    groupID++;
    return true;
}

Database::RemoveStatus DatabaseMS::removeGroup(int groupID){
    auto groupIt = memory.find(groupID); //pointer looking for the groupID
    if (groupIt == memory.end()) {
        std::cerr << "Group with ID: " << groupID << " not found.\n";
        return Database::RemoveStatus::GROUP_NOT_FOUND;
    }
    memory.erase(groupIt); 

    return Database::RemoveStatus::SUCCESS;
}

Expected<std::vector<Database::ListObject>, Database::RemoveStatus> DatabaseMS::listArticle(int groupID){
    if (memory.find(groupID) == memory.end())  {
        std::cerr << "Group with ID: " << groupID << " not found.\n";
        return  Database::RemoveStatus::GROUP_NOT_FOUND;
    }
    vector<Database::ListObject> result;
    std::map<int, Article>& articles =memory[groupID].articles;
    for (const auto& article : articles) { 
        result.emplace_back(article.second.getTitle(), article.first); // pair<title, articleID>
    }
 
    return result;
}

bool  DatabaseMS::makeArticle(int groupID, Article article){
    if (memory.find(groupID) == memory.end())  {
        std::cerr << "Group with ID: " << groupID << " not found.\n";
        return false;
    }

    article.setID(articleID);
    memory[groupID].articles[articleID] = article;
  
    articleID++;
    return true;
}
Database::RemoveStatus  DatabaseMS::removeArticle(int groupID, int articleID){
    auto groupIt = memory.find(groupID); //pointer looking for the groupID
    if (groupIt == memory.end()) {
        std::cerr << "Group with ID: "<< groupID <<" not found.\n";
        return Database::RemoveStatus::GROUP_NOT_FOUND;
    }

    auto& articles = groupIt->second.articles; // map<int, Article>
    auto articleIt = articles.find(articleID); // pointer looking for the articleID
    if (articleIt == groupIt->second.articles.end()) {
        std::cerr << "Article with ID: " <<articleID << " not found in group with ID : "<< groupID <<".\n";
        return Database::RemoveStatus::ARTICLE_NOT_FOUND;
    }
    articles.erase(articleIt); //ersaing with the iterator using the pointer
    return Database::RemoveStatus::SUCCESS;


}
Expected<Article, Database::RemoveStatus>  DatabaseMS::getArticle(int groupID, int articleID){
    auto groupIt = memory.find(groupID); //pointer looking for the groupID
    if (groupIt == memory.end()) {
        return Database::RemoveStatus::GROUP_NOT_FOUND;
    }

    auto& articles = groupIt->second.articles; // map<int, Article>
    auto articleIt = articles.find(articleID); // pointer looking for the articleID
    if (articleIt == groupIt->second.articles.end()) {
        return Database::RemoveStatus::ARTICLE_NOT_FOUND;
    }
    
    return memory[groupID].articles[articleID]; //returning the article

};

