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

    const std::filesystem::path root{"Newsgroup"};


    for (auto const& dir_entry : std::filesystem::directory_iterator{root}) 
        std::cout << dir_entry.path() << '\n';
    //DatabaseDS DS("Newsgroup");


}