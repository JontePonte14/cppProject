#include "DatabaseDS.h"
#include "Article.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include <filesystem>
namespace fs=std::filesystem;

int main(){
    fs::create_directory("Data");

    // const std::filesystem::path root{"Newsgroup"};


    // for (auto const& dir_entry : std::filesystem::directory_iterator{root}) 
    //     std::cout << dir_entry.path() << '\n';
    DatabaseDS DS("Newsgroup");
    cout << DS.makeGroup("Sweden") << endl;
    cout << DS.makeGroup("Sweden") << endl;
    cout << DS.makeGroup("Finland") << endl;


    cout << DS.removeGroup("Sweden") << endl;
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

    DS.makeArticle(article);






}