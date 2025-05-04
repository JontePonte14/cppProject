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
    
    std::vector<std::pair<std::string, int>> listGroup() override;
    // Cretes a group as a folder with the name : "name_groupID"
    bool makeGroup(const std::string& name)override;
    bool removeGroup(int groupID)override;

    std::vector<std::pair<std::string, int>> listArticle(int groupID) override;
    bool makeArticle( int group, Article article) override;
    bool removeArticle(int groupID, int articleID) override;
    Article getArticle(int groupID, int articleID) override;


private:
    /* data */
    std::filesystem::path root;
    static int groupIDnbr;
    static int groupIDnbrMax;

    // increment id for each new article
    void idIncr();

    //Help functions

    //Check to see if a group already exists.
    bool groupNameExists(const std::string& name);
    // Finds group with the id and return the full name of the folder as a string
    // Returns "" (empty string) if no group was found
    std::string findGroupWithID(const int& groupID);

    void saveGroupIdNbr();
    void loadGroupIdNbr();
    
    // saves the next articleID in the given news group folder
    void saveArticleIdNbr(const std::string& groupFolderName, const int& currentID);
    // loads the current articleID in the given news group folder
    int loadArticleIdNbr(const std::string& groupFolderName);
};