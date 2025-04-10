#include "article.h"
#include <string>
#include <list>

class DatabaseDS
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
    DatabaseDS(/* args */);
    ~DatabaseDS();
};

DatabaseDS::DatabaseDS(/* args */)
{
}

DatabaseDS::~DatabaseDS()
{
}
