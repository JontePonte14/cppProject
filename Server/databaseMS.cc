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


vector< pair<string, int>> groupIDName;

// map<int, vector<Article>> gIDtoArticles;
// map<string,int> groupID;
size_t groupID = 1;
size_t articleID = 1;

struct ArticleComparator {
    bool operator()(const std::pair<int, Article>& lhs, const std::pair<int, Article>& rhs) const {
        return lhs.second.getDate() < rhs.second.getDate();  // Compare by date
    }
};
// groupID to name and articles, atricles by ID , coparitor ensuring they are sorted by date (thoght right now its not possible to add at at date diffrent than the currnet one) 
map<int, pair<string, map<int, Article, ArticleComparator>>> memory;



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
    sort(  groupIDName.begin(), groupIDName.end(), [](const auto& a, const auto& b) {
        return groupIDArticleList[a.second].getDate() <groupIDArticleList[b.second].getDate(); });
    
    return groupIDName ;
}

bool makeGroup(string name){
    for (const auto& group : memory) {
        if (group.second.first == name) { // Compare the pairs first element (group name)
            cerr << "Group already exists" << endl;
            return false; 
        }
    }
    memory[groupID] = pair(name, map<int, Article, ArticleComparator>());

    
    // groupIDName.push_back( pair(name, groupID ));
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

vector<pair<string, int>> DatabaseMS::listArticle(int groupID){

    return vector<pair<string, int>>();
}

bool makeArticle(int groupID, Article article){

    //Wanted to check if aricle exist when adding but when we add it will get a diffrent id and therefor not be the same article... and maybe you should be able to add the same article twice?
    //But now ts quite pointless to have a general function for this ... 
    // if(containsFirst(articleMap[groupID], article)){  
    //     cerr << "Article already exists in the group" << endl;
    //     return false;
    // } //gammal
    
    
    //lite extra kommentarer då jag gissar den kan bli lite förvirrande 

    article.setID(articleID);
    memory[groupID].second[articleID] = article;
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

    auto& articles = groupIt->second.second; // map<int, Article>
    auto articleIt = articles.find(articleID); // pointer looking for the articleID
    if (articleIt == groupIt->second.second.end()) {
        std::cerr << "Article ID " <<articleID << " not found in group.\n";
        return false;
    }
    articles.erase(articleIt); //ersaing with the iterator using the pointer
    return true;


}
Article getArticle(int groupID, int articleID){
    return Article();
};
DatabaseMS::DatabaseMS(/* args */)
{
}
DatabaseMS::~DatabaseMS()
{
}

