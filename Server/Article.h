#ifndef ARTICLE_H
#define ARTICLE_H
#include <string>

class Article
{
public:
    Article() = default;
    Article(
        const std::string t, 
        const std::string a, 
        const std::string d, // Format: year-month-day
        int id, 
        const std::string b);
    ~Article() = default;

    Article getArticle() const;
    std::string getArticleName() const;
    std::string getArticleDate() const;
    int getArticleID() const;

private:
    std::string title;
    std::string author;
    std::string date; // Format: year-month-day
    int idNbr;
    std::string body;

    
};

#endif