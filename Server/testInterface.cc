#include "databaseMS.h" 
#include "databaseDS.h" 
#include "interface.h"
#include "article.h"
#include <string>
#include <iostream>

using namespace std;

Article article1(
    "testArticleIntercas",               // title
    "Per",                   // author                          /                                 
    "woow alot ofdf text here, this is a test article, it should be long enough to test the system. we need to make sure it works, and that it is long enough to test the system. "
);
Article article2(
    "AI Breakt5",               // title
    "Jonathan von Bergen",                   // author                          /                                 
    "In a grouninterfacereaking announcement today, researchers at the Global AI Institute revealed a new artificial intelligence model that surpasses previous benchmarks in both reasoning and creativity. "
    "Dubbed 'Aurora', the model demonstrates a remarkable ability to understand context, generate human-like dialogue, and even compose original music and poetry. Experts say this represents a major leap forward, "
    "not just in terms of computational power, but in the sophistication of the underlying architecture, which integrates multimodal learning and reinforcement strategies.\n\n"
    "The project, which began in early 2023, was a collaborative effort between academic institutions, private tech companies, and government-funded research agencies. Over 3,000 contributors worked on training and refining the model, "
    "utilizing over 1.5 million GPU hours and an unprecedented corpus of curated data. The developers emphasized their commitment to safety and ethics, noting that Aurora has built-in alignment protocols and robust content filters.\n\n"
    "Reactions from the global tech community have been mixed—some celebrating the possibilities for innovation, while others express concern over misuse and the potential displacement of creative professions. "
    "As debates continue, one thing is clear: AI is no longer just a tool for automation—it's becoming a collaborator in shaping the future."
);

string printList(const vector<string>& vec) {
    string result;
    for (const auto& s: vec) {
        result += "[" + s + "]\n";
    }
    return result;
}
void testInterface(Interface& interface) {
     // 1 for memory, 2 for disk, or default constructor for user input

    //almost the same as the one in databaseMS
    cout << " \nTEST INTERFACE on DB ["<<interface.getAtiveDB()<<"] : Adding groups \n\n";
    cout << "TEST 1 : Adding groups \n \n";
    cout << "Adding group1 : " << interface.makeGroup("group1") << endl;
    cout << "Adding group1 again : " << interface.makeGroup("group1") << endl;
    cout << "Adding group2 : " << interface.makeGroup("group2") << endl;
    cout << "List groups : \n" <<printList( interface.listGroup()) << endl;
    
    //removing groups
    cout << "TEST 2 : Removing groups \n \n";
    cout <<"removing group with ID 1 : " << interface.removeGroup(1) << endl;
    cout <<"removing group with ID 3 : " << interface.removeGroup(3) << endl;
    cout << "List groups : \n" <<printList( interface.listGroup()) << endl;
    
    //adding articles to groups
    
    cout << "TEST 3 : Adding Articles \n \n";
    cout << "Adding group3 : " << interface.makeGroup("group3") << endl;
    
   
    cout << "List Article in group ID 1 (doesnt exist): \n"<< printList( interface.listArticle(1)) << endl;
    cout << "List Article in group ID 2 : \n"<< printList( interface.listArticle(2)) << endl;
    
    cout << "Make article : " << interface.makeArticle(2, article1.getTitle(), article1.getAuthor(), article1.getBody()) << endl;
    cout << "Make article2 : " << interface.makeArticle(2, article2.getTitle(), article2.getAuthor(), article2.getBody()) << endl;
    cout << "List Articule in group ID 2 : \n"<< printList( interface.listArticle(2)) << endl;
    cout << "List Articule in group ID 3 : \n"<< printList( interface.listArticle(3)) << endl;
    
    cout << "removing article with ID 1 : " << interface.removeArticle(2, 1) << endl;
    cout << "removing article with ID 3 : " << interface.removeArticle(2, 3) << endl;
    
    cout << "List Articule in group ID 2 : \n"<< printList( interface.listArticle(2)) << endl;
    
    //remaking old group, gets new ID
    /*
    cout << "TEST 4 : Remaking group \n \n";
    cout << "Make group1 : " << interface.makeGroup("group1") << endl;
    cout << "List groups : \n" <<printList( interface.listGroup()) << endl;
    
    cout << "TEST 5 : Multiple copys \n \n";
    cout << "Make article : " << interface.makeArticle(3, article1.getTitle(), article1.getAuthor(), article1.getBody()) << endl;
    cout << "Make article : " << interface.makeArticle(3, article1.getTitle(), article1.getAuthor(), article1.getBody()) << endl;
    cout << "Make article : " << interface.makeArticle(3, article1.getTitle(), article1.getAuthor(), article1.getBody()) << endl;
    cout << "List Article in group ID 3 : \n"<< printList( interface.listArticle(3)) << endl;

    cout << "TEST 5 : Get Articles \n \n";
    try{
        cout<< "Getting article with ID 2 : " << interface.getArticle(2, 2).getTitle() << endl;
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    try{
        cout<< "Getting article with ID 2, from wrong group : " << interface.getArticle(3, 2).getTitle() << endl;
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }
        */
}

void testDatabaseDS(DatabaseDS DS) {
    // JUST DOING DS
    cout << "-----------------TESTING DS HERE ONLY--------------" << endl;     
    //almost the same as the one in databaseMS
    cout << "TEST 1 : Adding groups \n \n";
    cout << "Adding group1 : " << DS.makeGroup("group1") << endl;
    cout << "Adding group1 again : " << DS.makeGroup("group1") << endl;
    cout << "Adding group2 : " << DS.makeGroup("group2") << endl;
    cout << "List groups : \n";
    std::vector<std::pair<std::string, int>> tempPairVector;
    tempPairVector = DS.listGroup();
    for (const auto& [groupname, id] : tempPairVector) {
        cout << "ID: " << id << ", Groupname: " << groupname << endl;
    }
    
    //removing groups
    cout << "" << endl;
    cout << "TEST 2 : Removing groups \n \n";
    cout <<"removing group with ID 1 : " << DS.removeGroup(1) << endl;
    cout <<"removing group with ID 3 : " << DS.removeGroup(3) << endl;
    cout << "List groups : \n";
    tempPairVector = DS.listGroup();
    for (const auto& [groupname, id] : tempPairVector) {
        cout << "ID: " << id << ", Groupname: " << groupname << endl;
    }
    
    //adding articles to groups
    cout << "" << endl;
    cout << "TEST 3 : Adding Articles \n \n";
    cout << "Adding group3 : " << DS.makeGroup("group3") << endl;
    cout << "List Article in group ID 1 (doesnt exist): \n";
    tempPairVector = DS.listArticle(1);
    for (const auto& [title, id] : tempPairVector) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }

    cout << "List Article in group ID 2 : \n";
    tempPairVector = DS.listArticle(2);
    for (const auto& [title, id] : tempPairVector) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }
    
    cout << "Make article : " << DS.makeArticle(2, article1) << endl;
    cout << "Make article2 : " << DS.makeArticle(2, article2) << endl;
    cout << "List Articule in group ID 2 : \n";
    tempPairVector = DS.listArticle(2);
    for (const auto& [title, id] : tempPairVector) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }
    cout << "List Articule in group ID 3 : \n";
    tempPairVector = DS.listArticle(3);
    for (const auto& [title, id] : tempPairVector) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }
    
    cout << "removing article with ID 1 : " << DS.removeArticle(2, 1) << endl;
    cout << "removing article with ID 3 : " << DS.removeArticle(2, 3) << endl;
    
    cout << "List Articule in group ID 2 : \n";
    tempPairVector = DS.listArticle(2);
    for (const auto& [title, id] : tempPairVector) {
        cout << "Title: " << title << ", ID: " << id << endl;
    }
}

int main() {
    Interface interface(2); // 1 for memory, 2 for disk, or default constructor for user input
    testInterface(interface);
    // interface.switchDateBase();
    // testInterface(interface);
    // DatabaseDS DS;
    // testDatabaseDS(DS);

   

    // Use functions from databaseMS and interface here
    return 0;
}
