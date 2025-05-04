
#ifndef DATABASE_MS_H
#define DATABASE_MS_H
#include "article.h"
#include <string>
#include <list>
#include "database.h"
class DatabaseMS : public Database
{
public:
 
    std::vector<std::pair<std::string, int>>  listGroup() override;
    bool makeGroup(const std::string& name)override;
    bool removeGroup(int groupID)override;
    std::vector<std::pair<std::string, int>>  listArticle(int groupID) override;
    bool makeArticle( int group, Article article) override;
    bool removeArticle(int groupID, int articleID) override;
    Article getArticle(int groupID, int articleID) override;
};
#endif 