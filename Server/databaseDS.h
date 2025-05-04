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
    
    std::vector<std::string> listGroup() override;
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
    bool fileExists(const std::filesystem::path& groupName);

    void saveGroupIdNbr();
    void loadGroupIdNbr();
    
    void saveArticleIdNbr(const std::filesystem::path& groupFolder);
    void loadArticleIdNbr(const std::filesystem::path& groupFolder);
};