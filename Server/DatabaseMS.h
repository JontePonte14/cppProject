
#include "Article.h"
#include <string>
#include <list>
class DatabaseMS
{
private:
    /* data */
    
public:
    std::string listGroup();
    bool makeGroup();
    bool removeGroup();

    std::list<Article> listArticle();
    bool makeArticle();
    bool removeArticle();
    Article getArticle();

    DatabaseMS(/* args */);
    ~DatabaseMS();
};

DatabaseMS::DatabaseMS(/* args */)
{
}

DatabaseMS::~DatabaseMS()
{
}
