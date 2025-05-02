#include "databaseMS.h"
#include "database.h"
#include <map>
#include <string>
#include <vector>
#include "article.h"




std::map<int, std::vector<Article>> gIDtoArticles;
std::map<std::string,int> groupID;
std::string listGroup(){
    return "";
}
bool makeGroup(const std::string& name){
    return false;
}

bool removeGroup(const std::string& name){
    return false;
}

std::vector<std::pair<std::string, int>> DatabaseMS::listArticle(int groupID){
    return std::vector<std::pair<std::string, int>>();
}

bool makeArticle(Article& article){
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

