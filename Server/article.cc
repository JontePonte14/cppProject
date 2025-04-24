#include "article.h"
#include <string>
#include "json.hpp"
using json = nlohmann::json;

Article::Article(
    const std::string g,
    const std::string t, 
    const std::string a, 
    const std::string d, // Format: year-month-day
    int id, 
    const std::string b){
        groupName = g;
        title = t;
        author = a;
        date = d;
        idNbr = id;
        body = b;
    }

Article Article::getArticle() const {
    return *this;
}    

std::string Article::getGroupName() const {
    return groupName;
}

std::string Article::getTitle() const {
    return title;
}

std::string Article::getAuthor() const {
    return author;
}

std::string Article::getDate() const {
    return date;
}

int Article::getID() const {
    return idNbr;
}

std::string Article::getBody() const {
    return body;
}

void Article::setID(const int& newID) {
    idNbr = newID;
}

void to_json(json& jFile, const Article& article){
    jFile["id"] = article.getID();
    jFile["groupname"] = article.getGroupName();
    jFile["title"] = article.getTitle();
    jFile["author"] = article.getAuthor();
    jFile["date"] = article.getDate();
    jFile["body"] = article.getBody();
}

void from_json(const json& jFile, Article& article){
    article = Article(
        jFile["groupname"],
        jFile["title"],
        jFile["author"],
        jFile["date"],
        jFile["id"],
        jFile["body"]
    );
}