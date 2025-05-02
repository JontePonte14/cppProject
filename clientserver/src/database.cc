#include "database.h"
#include <string>
#include <list>

Database::Database(/* args */){
    activeDB = 1;
    db1 = DatabaseDS("Newsgroup");
    db2 = DatabaseMS();
}

std::string Database::listGroup()
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

bool Database::makeGroup(const std::string& name)
{
    if(activeDB == 1)
    {
        return db1.makeGroup(name);
    }
    else
    {
        return db2.makeGroup();
    }
    return false;
}

bool Database::removeGroup(const std::string& name)
{
    if(activeDB == 1)
    {
        return db1.removeGroup(name);
    }
    else
    {
        return db2.removeGroup();
    }
    
}

std::vector<std::pair<std::string, int>> Database::listArticle(std::string name)
{
    if(activeDB == 1)
    {
        return db1.listArticle(name);
    }
    else
    {
        //return db2.listGroup();

        //temp
        return db1.listArticle(name);
    }
    
}
// {  
//     std::list<Article> articles;
//     if(activeDB == 1)
//     {
//         articles = db1.listArticle();
//     }
//     else
//     {
//         articles = db2.listArticle();
//     }
//     if(articles.size() > 0)
//     {
//         std::string result;
//         for(auto it = articles.begin(); it != articles.end(); ++it)
//         {
//             result += it->getTitle() + "\n";
//         }
//         return result;
//     }
//     else
//     {
//         return "No articles found";
//     }

   
// }

bool Database::makeArticle(Article& article)
{
    if(activeDB == 1)
    {
        return db1.makeArticle(article);
    }
    else
    {
        return db2.makeArticle();
    }
    
}

bool Database::removeArticle(std::string articleGroup, std::string articleName, int articleID)
{
    if(activeDB == 1)
    {
        return db1.removeArticle(articleGroup, articleName, articleID);
    }
    else
    {
        return db2.removeArticle();
    }
    return false;
}

Article Database::getArticle(std::string articleGroup, std::string articleName, int articleID)
{
    if(activeDB == 1)
    {
        return db1.getArticle(articleGroup, articleName, articleID);
    }
    else
    {
        return db2.getArticle();
    }
    
    return Article();
}
int Database::switchDateBase()
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
