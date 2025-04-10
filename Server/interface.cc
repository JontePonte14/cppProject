#include "interface.h"
#include <string>
#include <list>

std::string interface::listGroup()
{
    if(activeDB == 1)
    {
        return db1.listGroup();
    }
    else
    {
        return db2.listGroup();
    }


    return std::string();
}

bool interface::makeGroup()
{
    if(activeDB == 1)
    {
        return db1.makeGroup();
    }
    else
    {
        return db2.makeGroup();
    }
    return false;
}

bool interface::removeGroup()
{
    if(activeDB == 1)
    {
        return db1.removeGroup();
    }
    else
    {
        return db2.removeGroup();
    }
    
}

std::string interface::listArticle(int groupID)
{
    if(activeDB == 1)
    {
        return db1.listGroup();
    }
    else
    {
        return db2.listGroup();
    }
    
}
{  
    std::list<Article> articles;
    if(activeDB == 1)
    {
        articles = db1.listArticle();
    }
    else
    {
        articles = db2.listArticle();
    }
    if(articles.size() > 0)
    {
        std::string result;
        for(auto it = articles.begin(); it != articles.end(); ++it)
        {
            result += it->getTitle() + "\n";
        }
        return result;
    }
    else
    {
        return "No articles found";
    }

   
}

bool interface::makeArticle(int groupID, int articleID)
{
    if(activeDB == 1)
    {
        return db1.makeArticle();
    }
    else
    {
        return db2.makeArticle();
    }
    
}
{
    if(activeDB == 1)
    {
        return db1.makeArticle();
    }
    else
    {
        return db2.makeArticle();
    }


}

bool interface::removeArticle(int groupID, int articleID)
{
    if(activeDB == 1)
    {
        return db1.removeArticle();
    }
    else
    {
        return db2.removeArticle();
    }
    return false;
}

Article interface::getArticle()
{
    if(activeDB == 1)
    {
        return db1.getArticle();
    }
    else
    {
        return db2.getArticle();
    }
    
    return Article();
}
int interface::switchDateBase()
{
    if(activeDB == 1)
    {
        activeDB = 2;
    }
    else
    {
        activeDB = 1;
    }
    return activeDB;
}
interface::interface(/* args */)
{
    activeDB = 1;
}
interface::~interface()
{
}
// interface::interface(/* args */)
// {
// }
// }
//
// interface::~interface()              
