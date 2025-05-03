#include "databaseMS.h"
#include "database.h"
#include <map>
#include <string>
#include <vector>
#include "article.h"
#include <algorithm> 
#include <iostream>


using namespace std;

map<int, vector<pair<Article, int>>> articleMap;


// vector< pair<string, int>> groupIDName;

// map<int, vector<Article>> gIDtoArticles;
// map<string,int> groupID;
size_t groupID = 1;
size_t articleID = 1;


struct ArticleComparator {
    bool operator()(const std::pair<int, Article>& lhs, const std::pair<int, Article>& rhs) const {
        return lhs.second.getDate() < rhs.second.getDate();  // Compare by date
    }
};

struct Group{
    string name;
    string date;
    map<int, Article, ArticleComparator> articles;
    Group(const string& groupName, const string& groupDate)
    : name(groupName), date(groupDate) {}
};
struct GroupComparator {
    bool operator()(const std::pair<int, Group>& lhs, const std::pair<int, Group>& rhs) const {
        return lhs.second.date < rhs.second.date;  // Compare by group date
    }
};
// groupID to name and articles, atricles by ID , coparitor ensuring they are sorted by date (thoght right now its not possible to add at at date diffrent than the currnet one) 
map<int, Group, GroupComparator> memory;



template <typename T>
bool containsFirst(const vector<pair<int , T >>& vec, const T& key) {
    return any_of(vec.begin(), vec.end(), [&](const pair<int, T>& pair) {
        return pair.first == key;
    });
}
template <typename T>
bool containsSecond(const std::vector<std::pair<int, T>>& vec, int id) {
    return any_of(vec.begin(), vec.end(), [&](const pair<int, T>& pair) {
        return pair.second == id;
    });
}
vector<pair<string, int>> listGroup(){
    //making sureits sorted by date
    // sort(  groupIDName.begin(), groupIDName.end(), [](const auto& a, const auto& b) {
    //     return groupIDArticleList[a.second].getDate() <groupIDArticleList[b.second].getDate(); });
    vector<pair<string, int>> groups;
    for (const auto& group : memory) {
        groups.push_back(make_pair(group.second.name, group.first)); // pair<name, groupID>
    }
    //inte i kronologisk ordnign än utan troligen alabetisk? 
    //är det värt att ha en grupp struct som innehåller både namn map med artiklar och date så kan den vara sorterad på date?
    //boorde vara löst nu?? 
    return groups;
}

bool makeGroup(string name){
    for (const auto& group : memory) {
        if (group.second.name == name) { // Compare the pairs first element (group name)
            cerr << "Group already exists" << endl;
            return false; 
        }
    }
    string date = "2023-10-01"; // Placeholder for the date, should be set to the current date i guess?
    memory[groupID] = Group(name, date);

    groupID++;
    return true;
}

bool removeGroup(int groupID){
    auto groupIt = memory.find(groupID); //pointer looking for the groupID
    if (groupIt == memory.end()) {
        std::cerr << "Group ID" << groupID << "not found.\n";
        return false;
    }
    memory.erase(groupIt); 

    return true;
}

vector<pair<string, int>> listArticle(int groupID){
    vector<pair<string, int>> articles;
    for (const auto& article : memory[groupID].articles) { // should be in order as map is sorted by date
        articles.push_back(make_pair(article.second.getTitle(), article.first)); // pair<title, articleID>
    }
    return articles;
}

bool makeArticle(int groupID, Article article){

    
    
    //lite extra kommentarer då jag gissar den kan bli lite förvirrande 

    article.setID(articleID);
    memory[groupID].articles[articleID] = article;
    // articleMap[groupID].push_back(make_pair(article, articleID));
    articleID++;
    return false;
}
bool removeArticle(int groupID, int articleID){
    auto groupIt = memory.find(groupID); //pointer looking for the groupID
    if (groupIt == memory.end()) {
        std::cerr << "Group ID "<< groupID <<" not found.\n";
        return false;
    }

    auto& articles = groupIt->second.articles; // map<int, Article>
    auto articleIt = articles.find(articleID); // pointer looking for the articleID
    if (articleIt == groupIt->second.articles.end()) {
        std::cerr << "Article ID " <<articleID << " not found in group.\n";
        return false;
    }
    articles.erase(articleIt); //ersaing with the iterator using the pointer
    return true;


}
Article getArticle(int groupID, int articleID){
    auto groupIt = memory.find(groupID); //pointer looking for the groupID
    if (groupIt == memory.end()) {
        throw runtime_error("Article not found");
    }

    auto& articles = groupIt->second.articles; // map<int, Article>
    auto articleIt = articles.find(articleID); // pointer looking for the articleID
    if (articleIt == groupIt->second.articles.end()) {
        throw runtime_error("Article not found");
    }
    
    return memory[groupID].articles[articleID]; //returning the article

};
DatabaseMS::DatabaseMS(/* args */)
{
}
DatabaseMS::~DatabaseMS()
{
}

