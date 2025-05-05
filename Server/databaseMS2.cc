// #include "databaseMS.h"
// #include "database.h"
// #include "article.h" 
// #include <map>
// #include <string>
// #include <vector>
// #include <iostream>



// using namespace std;

// // unordered_map<int, vector<pair<Article, int>>> articleMap;


// // vector< pair<string, int>> groupIDName;

// // map<int, vector<Article>> gIDtoArticles;
// // map<string,int> groupID;
// size_t groupID = 1;
// size_t articleID = 1;




// struct Group{
//     string name;

//     map<int, Article> articles;
//     Group() : name(""), articles() {}
//     Group(const string& groupName)
//     : name(groupName) {}
// };

// // groupID to name and articles, atricles by ID , coparitor ensuring they are sorted by date (thoght right now its not possible to add at at date diffrent than the currnet one) 
// map<int, Group> memory;

// vector<pair<int, Group>> mem;



// template <typename T>
// bool containsFirst(const vector<pair<int , T >>& vec, const T& key) {
//     return any_of(vec.begin(), vec.end(), [&](const pair<int, T>& pair) {
//         return pair.first == key;
//     });
// }
// template <typename T>
// bool containsSecond(const std::vector<std::pair<int, T>>& vec, int id) {
//     return any_of(vec.begin(), vec.end(), [&](const pair<int, T>& pair) {
//         return pair.second == id;
//     });
// }
// vector<pair<string, int>> DatabaseMS::listGroup(){
//     //making sureits sorted by date
//     // sort(  groupIDName.begin(), groupIDName.end(), [](const auto& a, const auto& b) {
//     //     return groupIDArticleList[a.second].getDate() <groupIDArticleList[b.second].getDate(); });
//     vector<pair<string, int>> groups;

//     for (const auto& group : memory) {
//         groups.emplace_back(group.second.name, group.first); // pair<name, groupID>
//     }
//     //map is sorted by key, and key is groupID, wich is increasing by time so the order is already correct



//     // std::sort(groups.begin(), groups.end(), [](const auto& a, const auto& b) {
//     //     return memory.at(a.second).date < memory.at(b.second).date;
//     // });

//     return groups;
// }

// bool  DatabaseMS::makeGroup(const std::string& name){
//     for (const auto& group : memory) {
//         if (group.second.name == name) { // Compare the pairs first element (group name)
//             cerr << "Group already exists" << endl;
//             return false; 
//         }
//     }
//     // string date = "2023-10-01"; // Placeholder for the date, should be set to the current date i guess?
//     memory[groupID] = Group(name);
//     groupID++;
//     return true;
// }

// bool  DatabaseMS::removeGroup(int groupID){
//     auto groupIt = memory.find(groupID); //pointer looking for the groupID
//     if (groupIt == memory.end()) {
//         std::cerr << "Group with ID: " << groupID << " not found.\n";
//         return false;
//     }
//     memory.erase(groupIt); 

//     return true;
// }

// vector<pair<string, int>> DatabaseMS::listArticle(int groupID){
//     if (memory.find(groupID) == memory.end())  {
//         std::cerr << "Group with ID: " << groupID << " not found.\n";
//         return {};
//     }
//     vector<pair<string, int>> result;
//     std::map<int, Article>& articles =memory[groupID].articles;
//     for (const auto& article : articles) { 
//         result.emplace_back(article.second.getTitle(), article.first); // pair<title, articleID>
//     }
//     //map is sorted by key, and key is groupID, wich is increasing by time so the order is already correct
    
//     // std::sort(result.begin(), result.end(), [&articles](const auto& a, const auto& b) {
//     //     return articles.at(a.second).getDate() < articles.at(b.second).getDate();
//     // });
//     return result;
// }

// bool  DatabaseMS::makeArticle(int groupID, Article article){
//     if (memory.find(groupID) == memory.end())  {
//         std::cerr << "Group with ID: " << groupID << " not found.\n";
//         return false;
//     }

//     article.setID(articleID);
//     memory[groupID].articles[articleID] = article;
//     // articleMap[groupID].push_back(make_pair(article, articleID));
//     articleID++;
//     return true;
// }
// bool  DatabaseMS::removeArticle(int groupID, int articleID){
//     auto groupIt = memory.find(groupID); //pointer looking for the groupID
//     if (groupIt == memory.end()) {
//         std::cerr << "Group with ID: "<< groupID <<" not found.\n";
//         return false;
//     }

//     auto& articles = groupIt->second.articles; // map<int, Article>
//     auto articleIt = articles.find(articleID); // pointer looking for the articleID
//     if (articleIt == groupIt->second.articles.end()) {
//         std::cerr << "Article with ID: " <<articleID << " not found in group with ID : "<< groupID <<".\n";
//         return false;
//     }
//     articles.erase(articleIt); //ersaing with the iterator using the pointer
//     return true;


// }
// Article  DatabaseMS::getArticle(int groupID, int articleID){
//     auto groupIt = memory.find(groupID); //pointer looking for the groupID
//     if (groupIt == memory.end()) {
//         throw runtime_error("Article not found");
//     }

//     auto& articles = groupIt->second.articles; // map<int, Article>
//     auto articleIt = articles.find(articleID); // pointer looking for the articleID
//     if (articleIt == groupIt->second.articles.end()) {
//         throw runtime_error("Article not found");
//     }
    
//     return memory[groupID].articles[articleID]; //returning the article

// };

