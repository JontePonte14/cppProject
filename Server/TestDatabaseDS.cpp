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
    DatabaseDS DS("Newsgroup");
    cout << DS.makeGroup("Sweden") << endl;
    cout << DS.makeGroup("Sweden") << endl;
    cout << DS.makeGroup("Finland") << endl;


    //cout << DS.removeGroup("Sweden") << endl;
    //cout << DS.removeGroup("Sweden") << endl;
    cout << DS.makeGroup("Technology") << endl;

    Article article(
        "Technology",                            // groupName
        "AI Breakthrough in 2025",               // title
        "Jonathan von Bergen",                   // author
        "2025-04-08",                            // date
        101,                                     // idNbr
        "In a groundbreaking announcement today, researchers at the Global AI Institute revealed a new artificial intelligence model that surpasses previous benchmarks in both reasoning and creativity. "
        "Dubbed 'Aurora', the model demonstrates a remarkable ability to understand context, generate human-like dialogue, and even compose original music and poetry. Experts say this represents a major leap forward, "
        "not just in terms of computational power, but in the sophistication of the underlying architecture, which integrates multimodal learning and reinforcement strategies.\n\n"
        "The project, which began in early 2023, was a collaborative effort between academic institutions, private tech companies, and government-funded research agencies. Over 3,000 contributors worked on training and refining the model, "
        "utilizing over 1.5 million GPU hours and an unprecedented corpus of curated data. The developers emphasized their commitment to safety and ethics, noting that Aurora has built-in alignment protocols and robust content filters.\n\n"
        "Reactions from the global tech community have been mixed—some celebrating the possibilities for innovation, while others express concern over misuse and the potential displacement of creative professions. "
        "As debates continue, one thing is clear: AI is no longer just a tool for automation—it's becoming a collaborator in shaping the future."
    );

    Article article2(
        "Technology",                            // groupName
        "AI is good",                            // title
        "Jonathan von Bergen",                   // author
        "2024-04-08",                            // date
        1,                                       // idNbr
        "AI is good this is body"
    );

    cout << "make article " << DS.makeArticle(article) << endl;
    cout << "make article2 " << DS.makeArticle(article2) << endl;

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

    






}