#ifndef DATABASE_DS_H
#define DATABASE_DS_H

#include "json.hpp"
#include "article.h"
#include "database.h"
#include <string>
#include <vector>
#include <filesystem>
using json = nlohmann::json;


class DatabaseDS : public Database
{
public:
    // Default contructur creates a root folder called "Newsgroup"
    DatabaseDS();
    ~DatabaseDS() = default;
    
    std::vector<Database::ListObject> listGroup() override;
    // Cretes a group as a folder with the name : "name_groupID"
    bool makeGroup(const std::string& name)override;
    bool removeGroup(int groupID)override;

    std::vector<Database::ListObject> listArticle(int groupID) override;
    bool makeArticle( int group, Article article) override;
    bool removeArticle(int groupID, int articleID) override;
    Article getArticle(int groupID, int articleID) override;


private:
    /* data */
    std::filesystem::path root;
    static int groupIDnbr;

    // increment id for each new group
    void idIncr();

    //Help functions

    //Check to see if a group already exists.
    bool groupNameExists(const std::string& name);
    // Finds group with the id and return the full name of the folder as a string
    // Returns "" (empty string) if no group was found
    std::string findGroupWithID(const int& groupID);
    // Checks if an article exist within a group given its groupID and articleID
    // Returns "" (empty string) if it couldn't be found
    std::filesystem::path findArticlePath(const int& groupID, const int& articleID);

    void saveGroupIdNbr();
    void loadGroupIdNbr();
    
    // saves the next articleID in the given news group folder
    void saveArticleIdNbr(const std::string& groupFolderName, const int& currentID);
    // loads the current articleID in the given news group folder
    int loadArticleIdNbr(const std::string& groupFolderName);
};
#endif // DATABASE_MS_H