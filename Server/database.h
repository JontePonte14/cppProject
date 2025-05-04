#ifndef DATABASE_H
#define DATABASE_H


#include "article.h"
#include <string>
#include <list>


class Database {
    public:
        virtual ~Database() = default;
    
        virtual std::vector<std::string> listGroup() = 0;
        virtual bool makeGroup(const std::string& name) = 0;
        virtual bool removeGroup(int groupID) = 0;
    
        virtual std::vector<std::pair<std::string, int>> listArticle(int groupID) = 0;
        virtual bool makeArticle(int groupID, Article article) = 0;
        virtual bool removeArticle(int groupID, int articleID) = 0;
        virtual Article getArticle(int groupID, int articleID) = 0;
    };
    

#endif