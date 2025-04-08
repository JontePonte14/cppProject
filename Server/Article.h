#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>

class Article
{
private:
    std::string title;
    std::string author;
    std::string date; // Format: year-month-day
    int idNbr;
    std::string body;
public:
    Article() = default;
    Article(std::string t, std::string a, std::string d, int id, std::string b);
    ~Article();
    
};

Article::Article(/* args */)


{
}

Article::~Article()


{
}
#endif