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
                :  name(groupName), id(groupID) {} 
                
            std::string toString() const {return name + " [" + std::to_string(id) + "]";}
        };
    
        enum class RemoveStatus { OK = 1, GROUP_NOT_FOUND = 2 , ARTICLE_NOT_FOUND  = 3, UNKNOWN_ERROR = 4};
        static std::string toString(Database::RemoveStatus status) {
            switch (status) {
                case Database::RemoveStatus::OK: return "OK";
                case Database::RemoveStatus::GROUP_NOT_FOUND: return "GROUP_NOT_FOUND";
                case Database::RemoveStatus::ARTICLE_NOT_FOUND: return "ARTICLE_NOT_FOUND";
                case Database::RemoveStatus::UNKNOWN_ERROR: return "UNKNOWN_ERROR";
                default: return "UNKNOWN_STATUS";
            }
        }

        virtual ~Database() = default;
    
        virtual std::vector<ListObject>  listGroup() = 0;
        virtual bool makeGroup(const std::string& name) = 0;
        virtual RemoveStatus removeGroup(int groupID) = 0;
    
        virtual std::vector<ListObject>  listArticle(int groupID) = 0;
        virtual bool makeArticle(int groupID, Article article) = 0;
        virtual RemoveStatus removeArticle(int groupID, int articleID) = 0;
        virtual Article getArticle(int groupID, int articleID) = 0;
    };
    

#endif