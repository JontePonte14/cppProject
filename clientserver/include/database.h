#ifndef DATABASE_H
#define DATABASE_H


#include "article.h"
#include <string>
#include <list>
#include <map>

class Database {
  
    public:
            struct ListObject{
                std::string name;
                int id;
                ListObject(const std::string& groupName, int groupID)
                    : id(groupID), name(groupName) {} 
                    
                std::string toString() const {return name + " [" + std::to_string(id) + "]";}
            };

        virtual ~Database() = default;
    
        virtual std::vector<ListObject>  listGroup() = 0;
        virtual bool makeGroup(const std::string& name) = 0;
        virtual bool removeGroup(int groupID) = 0;
    
        virtual std::vector<ListObject>  listArticle(int groupID) = 0;
        virtual bool makeArticle(int groupID, Article article) = 0;
        virtual bool removeArticle(int groupID, int articleID) = 0;
        virtual Article getArticle(int groupID, int articleID) = 0;
    };
    

#endif