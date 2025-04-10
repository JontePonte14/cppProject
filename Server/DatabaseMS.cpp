#include "DatabaseMS.h"

std::string DatabaseMS::listGroup()
{
    return std::string();
}

bool DatabaseMS::makeGroup()
{
    return false;
}

bool DatabaseMS::removeGroup()
{
    return false;
}

std::list<Article> DatabaseMS::listArticle()
{  

    return std::list<Article>();
}

bool DatabaseMS::makeArticle()
{
    return false;
}

bool DatabaseMS::removeArticle()
{
    return false;
}

Article DatabaseMS::getArticle()
{
    return Article();
}
DatabaseMS::DatabaseMS(/* args */)
{
}
DatabaseMS::~DatabaseMS()
{
}
// Compare this snippet from Server/DatabaseDS.h:
// #include "Article.h"
// #include <string>  
