#include "databaseMS.h" // include the header
#include "article.h"
#include <string>
#include <iostream>

using namespace std;


   
    Article article1(
        "testArticle",               // title
        "Pelle",                   // author                          /                                 
        "woow alot ofdf text here, this is a test article, it should be long enough to test the system. we need to make sure it works, and that it is long enough to test the system. "
    );
    Article article2(
        "AI Breakthrough in 2025",               // title
        "Jonathan von Bergen",                   // author                          /                                 
        "In a groundbreaking announcement today, researchers at the Global AI Institute revealed a new artificial intelligence model that surpasses previous benchmarks in both reasoning and creativity. "
        "Dubbed 'Aurora', the model demonstrates a remarkable ability to understand context, generate human-like dialogue, and even compose original music and poetry. Experts say this represents a major leap forward, "
        "not just in terms of computational power, but in the sophistication of the underlying architecture, which integrates multimodal learning and reinforcement strategies.\n\n"
        "The project, which began in early 2023, was a collaborative effort between academic institutions, private tech companies, and government-funded research agencies. Over 3,000 contributors worked on training and refining the model, "
        "utilizing over 1.5 million GPU hours and an unprecedented corpus of curated data. The developers emphasized their commitment to safety and ethics, noting that Aurora has built-in alignment protocols and robust content filters.\n\n"
        "Reactions from the global tech community have been mixed—some celebrating the possibilities for innovation, while others express concern over misuse and the potential displacement of creative professions. "
        "As debates continue, one thing is clear: AI is no longer just a tool for automation—it's becoming a collaborator in shaping the future."
    );
 
string pairToString(const vector<pair<string, int>>& vec) {
    string result;
    for (const auto& pair : vec) {
        result += pair.first + " " + to_string(pair.second) + "\n";
    }
    return result;

}
void printListObjects(const std::vector<Database::ListObject>& groups) {
    for (const auto& g : groups) {
        std::cout << g.toString() + "\n";
    }
}
int main() {
    DatabaseMS db = DatabaseMS();
    //adding groups
    cout << "TEST 1 : Adding groups \n \n ";
    cout << "Adding group1 : " << db.makeGroup("group1") << endl;
    cout << "Adding group1 again : " << db.makeGroup("group1") << endl;
    cout << "Adding group2 : " << db.makeGroup("group2") << endl;
    cout << "List groups : \n";
    printListObjects(db.listGroup());
    
    //removing groups
    cout << "TEST 2 : Removing groups \n \n ";
    cout <<"removing group with ID 1 : " << Database::toString(db.removeGroup(1)) << endl;
    cout <<"removing group with ID 3 : " << Database::toString(db.removeGroup(3)) << endl;
    cout << "List groups : \n";
    printListObjects(db.listGroup());
    
    //adding articles to groups
    
    cout << "TEST 3 : Adding Articles \n \n ";
    cout << "Adding group3 : " << db.makeGroup("group3") << endl;
    
    cout << "List Article in group ID 1 : \n"; 
    printListObjects( db.listArticle(1));
    cout << "List Article in group ID 2 : \n";
    printListObjects( db.listArticle(2));
    
    cout << "make article : " << db.makeArticle(2, article1) << endl;
    cout << "make article2 : " << db.makeArticle(2, article2) << endl;
    cout << "List Articule in group ID 2 : \n";
    printListObjects( db.listArticle(2));
    cout << "List Articule in group ID 3 : \n";
    printListObjects( db.listArticle(3));
    
    cout << "removing article with ID 1 : " << Database::toString(db.removeArticle(2, 1)) << endl;
    cout << "removing article with ID 3 : " << Database::toString(db.removeArticle(2, 3)) << endl;
    
    cout << "List Articule in group ID 2 : \n";
    printListObjects( db.listArticle(2));
    //remaking old group, gets new ID
    
    cout << "TEST 4 : Remaking group \n \n ";
    cout << "Make group1 : " << db.makeGroup("group1") << endl;
    cout << "List groups : \n";
    printListObjects(db.listGroup());
    
    
    cout << "TEST 5 : Multiplke copys \n \n ";
    cout << "Make article : " << db.makeArticle(3, article1) << endl;
    cout << "Make article : " << db.makeArticle(3, article1) << endl;
    cout << "Make article : " << db.makeArticle(3, article1) << endl;
    cout << "List Articule in group ID 3 : \n";
    printListObjects( db.listArticle(3));
    cout << "TEST 5 : Get Articles \n \n ";
    try{
        cout<< "Getting article with ID 2 : " << db.getArticle(2, 2).getTitle() << endl;
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    try{
        cout<< "Getting article with ID 2, from wrong group : " << db.getArticle(3, 2).getTitle() << endl;
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    
    return 0;
}