#ifndef DATABASE_H
#define DATABASE_H


#include "article.h"
#include <string>
#include <list>


class Database
{
    
public:
    // Default contructur creates a root folder called "Newsgroup"
    Database();
    // Custom constructur makes it possible to decide the name of the root folder


    std::string listGroup();
    bool makeGroup(const std::string& name);
    bool removeGroup(const std::string& name);

    std::vector<std::pair<std::string, int>> listArticle(int groupID);
    bool makeArticle(Article& article);
    bool removeArticle(int groupID, int articleID);
    Article getArticle(int groupID, int articleID);
    
private:
    /* data */

    static int IDnbr;
    // increment id for each new article
    void idIncr();

    //Help functions
};

#endif