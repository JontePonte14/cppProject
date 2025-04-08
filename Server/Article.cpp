#include "Article.h"
#include <string>

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