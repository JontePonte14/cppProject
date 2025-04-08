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

