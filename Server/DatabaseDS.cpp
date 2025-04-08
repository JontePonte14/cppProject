#include "DatabaseDS.h"
#include "Article.h"
#include <string>
#include <filesystem>

DatabaseDS::DatabaseDS(){
    return;
}

std::string DatabaseDS::listGroup(){
    return "temp";
}

bool DatabaseDS::makeGroup(){
    return false;
}

bool DatabaseDS::removeGroup(){
    return false;
}

std::list<Article> DatabaseDS::listArticle(){
    return articles;
}

bool DatabaseDS::makeArticle(){
    return false;
}

bool DatabaseDS::removeArticle(){
    return false;
}

Article DatabaseDS::getArticle(){
    return temp;
}


