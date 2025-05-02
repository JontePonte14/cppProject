#include "databaseMS.h"
#include "database.h"
#include <map>
#include <string>
#include <vector>
#include "article.h"




std::map<int, std::vector<Article>> groupIDArticleList;
std::vector< std::pair<int, std::string>> groupIDName;

// std::map<int, std::vector<Article>> gIDtoArticles;
// std::map<std::string,int> groupID;
size_t groupID = 0;
size_t articleID = 0;
std::vector<std::string> listGroup(){

    std::sort(  groupIDName.begin(), groupIDName.end(), [](const auto& a, const auto& b) {
        return groupIDArticleList[a.first].getDate() <groupIDArticleList[b.first].getDate(); });
    

    return ;
}

bool makeGroup(std::string name){
    if(std::find(groupName.begin(), groupName.end(), name) != groupName.end()){
        return false;
    }
    groupName.insert( groupName.begin()+ groupID, name);
    return true;
}

bool removeGroup(int groupID){
    return false;
}

std::vector<std::pair<std::string, int>> DatabaseMS::listArticle(int groupID){
    return std::vector<std::pair<std::string, int>>();
}

bool makeArticle(int groupID, Article article){

    return false;
}
bool removeArticle(int groupID, int articleID){
    return false;
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

