#include "Article.h"
#include <string>

Article::Article(
    const std::string t, 
    const std::string a, 
    const std::string d, // Format: year-month-day
    int id, 
    const std::string b){
        title = t;
        author = a;
        date = d;
        idNbr = id;
        body = b;
    }

Article Article::getArticle() const {
    return *this; // returns a copy of the current object
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