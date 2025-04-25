#ifndef ARTICLE_H
#define ARTICLE_H

#include <vector>
#include <string>
#include "json.hpp"
using json = nlohmann::json;

class Article
{
public:
    Article() = default;
    Article(
        const std::string g,
        const std::string t, 
        const std::string a, 
        const std::string d, // Format: year-month-day
        int id, 
        const std::string b);
    ~Article() = default;

    Article getArticle() const;
    std::string getGroupName() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getDate() const;
    int getID() const;
    std::string getBody() const;
    void setID(const int& newID);

private:
    std::string groupName;
    std::string title;
    std::string author;
    std::string date; // Format: year-month-day
    int idNbr;
    std::string body;
};

    // converting to/from json file (overloading function)
    void to_json(json& jFile, const Article& article);
    void from_json(const json& jFile, Article& article);

#endif