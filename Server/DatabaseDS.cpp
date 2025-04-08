#include "DatabaseDS.h"
#include "Article.h"
#include <string>
#include <filesystem>

DatabaseDS::DatabaseDS(){
    return;
}

std::string DatabaseDS::listGroup(){
    return newsGroups[0];
}

bool DatabaseDS::makeGroup(){
    return false;
}

bool DatabaseDS::removeGroup(){
    return false;
}

std::vector<Article> DatabaseDS::listArticle(){
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


