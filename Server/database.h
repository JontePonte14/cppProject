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


    virtual std::vector<std::string> listGroup();
    virtual bool makeGroup(const std::string& name);
    virtual bool removeGroup(int groupID);

    virtual std::vector<std::pair<std::string, int>> listArticle(int groupID);
    virtual bool makeArticle(int groupID, Article article);
    virtual bool removeArticle(int groupID, int articleID);
    virtual Article getArticle(int groupID, int articleID);
    
private:
    /* data */

    static int IDnbr;
    // increment id for each new article
    void idIncr();

    //Help functions
};

#endif