#include "databaseDS.h"
#include "article.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include <filesystem>
namespace fs=std::filesystem;

int main(){
    DatabaseDS DS;
    cout << "TEST 1: makegroup()" << endl;
    cout << DS.makeGroup("Sweden") << endl;
    cout << DS.makeGroup("Sweden") << endl;
    cout << DS.makeGroup("Finland") << endl;

    cout << "-----------------" << endl;
    cout << "TEST 2: removegroup()" << endl;
    cout << DS.removeGroup(1) << endl;
    cout << DS.removeGroup(6) << " = 0" << endl;
    cout << DS.makeGroup("Technology") << endl;
    
    cout << "-----------------" << endl;
    cout << "TEST 3: listGroup()" << endl;
    std::vector<std::pair<std::string, int>> allGroups;
    allGroups = DS.listGroup();
    for (const auto& [groupname, id] : allGroups) {
        cout << "ID: " << id << ", Groupname: " << groupname << endl;
    }

    cout << "-----------------" << endl;
    cout << "TEST 4: makeArticle()" << endl;
    
    Article article(
        "AI Breakthrough in 2025",               // title
        "Jonathan von Bergen",                   // author
        "In a groundbreaking announcement today, researchers at the Global AI Institute revealed a new artificial intelligence model that surpasses previous benchmarks in both reasoning and creativity. "
        "Dubbed 'Aurora', the model demonstrates a remarkable ability to understand context, generate human-like dialogue, and even compose original music and poetry. Experts say this represents a major leap forward, "
        "not just in terms of computational power, but in the sophistication of the underlying architecture, which integrates multimodal learning and reinforcement strategies.\n\n"
        "The project, which began in early 2023, was a collaborative effort between academic institutions, private tech companies, and government-funded research agencies. Over 3,000 contributors worked on training and refining the model, "
        "utilizing over 1.5 million GPU hours and an unprecedented corpus of curated data. The developers emphasized their commitment to safety and ethics, noting that Aurora has built-in alignment protocols and robust content filters.\n\n"
        "Reactions from the global tech community have been mixed—some celebrating the possibilities for innovation, while others express concern over misuse and the potential displacement of creative professions. "
        "As debates continue, one thing is clear: AI is no longer just a tool for automation—it's becoming a collaborator in shaping the future."
    );

    cout << DS.makeArticle(3, article) << " = 1 " << endl;
    cout << DS.makeArticle(999, article) << " = 0" << endl;


    Article article2(
        "AI is good",                            // title
        "Jonathan von Bergen",                   // author
        "AI is good this is body"
    );

    cout << DS.makeArticle(2, article) << endl;
    cout << DS.makeArticle(3, article2) << endl;

    cout << "-----------------" << endl;
    cout << "TEST 5: removeArticle()" << endl;
    cout << DS.removeArticle(3, 2) << endl;
    cout << DS.makeArticle(2, article2) << " We then back to Finland instead" << endl;


    cout << "-----------------" << endl;
    cout << "TEST 6: getArticle()" << endl;
    Article fetchedArticle = DS.getArticle(2, 2);
    cout << "Title of fetched article: " << fetchedArticle.getTitle() << endl;

    cout << "TEST 7: listArticle()" << endl;
    std::vector<std::pair<std::string, int>> articlesInFinland;
    articlesInFinland = DS.listArticle(2);
    cout << "Iterating in the folder Finland_2" << endl;
    for (const auto& [title, id] : articlesInFinland) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }
    /*
    //cout << "remove article: " << DS.removeArticle("Technology", "AI Breakthrough in 2025", 999) << endl;

    cout << "remove article: " << DS.removeArticle("Technology", "AI Breakthrough in 2025", 129) << endl;


    cout << "List newsgroup: ";
    cout << DS.listGroup() << endl;

    cout << "Tesing to get unavailable file: ";
    Article testGet;
    testGet = DS.getArticle("Technology", "AI Breakthrough in 2025", 129);

    
    std::vector<std::pair<std::string, int>> sortedArticles;
    sortedArticles = DS.listArticle("Technology");
    cout << "Iterating over articles in the group Technology: " << endl;
    for (const auto& [title, id] : sortedArticles) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }

    cout << "----------" << endl;

    cout << "Adding a third article" << endl;

    Article article3(
        "Technology",                            // groupName
        "AI is very bad",                            // title
        "Jenny von Bergen",                   // author
        "2020-11-28",                            // date
        1,                                       // idNbr
        "AI is not so good people though, and I think it should be destroyed"
    );


    cout << "The end" << endl;
    cout << "make article3 " << DS.makeArticle(article3) << endl;

    sortedArticles = DS.listArticle("Technology");
    cout << "Iterating over articles in the group Technology (again): " << endl;
    for (const auto& [title, id] : sortedArticles) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }
    */

    






}