#include "Article.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;

int main(){
    std::string g = "Newsletter";
    std::string t = "Title";
    std::string a = "Jonathan";
    std::string d = "2025-04-09";
    int id = 1;
    std::string b = "Hejsansvensan";

    Article art(g, t, a, d, id, b);

    Article art2 = art.getArticle();

    cout << "Groupname: " << art.getGroupName() << endl;
    cout << "Title: " << art.getTitle() << endl;
    cout << "Author: " << art.getAuthor() << endl;
    cout << "Date: " << art.getDate() << endl;
    cout << "ID: " << art.getID() << endl;
    cout << "Body: " << art.getBody() << endl;
    cout << endl;

    cout << "Copy of Article" << endl;

    cout << "Groupname: " << art2.getGroupName() << endl;
    cout << "Title: " << art2.getTitle() << endl;
    cout << "Author: " << art2.getAuthor() << endl;
    cout << "Date: " << art2.getDate() << endl;
    cout << "ID: " << art2.getID() << endl;
    cout << "Body: " << art2.getBody() << endl;



}