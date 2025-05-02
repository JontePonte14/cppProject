#include "databaseMS.h"
#include <map>
#include <string>
#include <vector>
#include "article.h"




std::map<int, std::vector<Article>> gIDtoArticles;
std::map<std::string,int> groupID;
std::string listGroup();
bool makeGroup(const std::string& name);
bool removeGroup(const std::string& name);

std::vector<std::pair<std::string, int>> listArticle(int groupID);
bool makeArticle(Article& article);
bool removeArticle(int groupID, int articleID);
Article getArticle(int groupID, int articleID);
DatabaseMS::DatabaseMS(/* args */)
{
}
DatabaseMS::~DatabaseMS()
{
}

