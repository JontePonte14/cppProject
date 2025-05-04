#include "article.h"
#include <string>
#include "json.hpp"
using json = nlohmann::json;

Article::Article(
    const std::string t, 
    const std::string a, 
    const std::string b){
        title = t;
        author = a;
        idNbr = -1;
        body = b;
    }

Article Article::getArticle() const {
    return *this;
}    

std::string Article::getTitle() const {
    return title;
}

std::string Article::getAuthor() const {
    return author;
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
    jFile["title"] = article.getTitle();
    jFile["author"] = article.getAuthor();
    jFile["body"] = article.getBody();
}

void from_json(const json& jFile, Article& article){
    article = Article(
        jFile["title"],
        jFile["author"],
        jFile["body"]

    );
    article.setID(jFile["id"]);
}