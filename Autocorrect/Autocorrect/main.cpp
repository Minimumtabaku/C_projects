//
//  main.cpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <stack>
#include "Autocorrector.hpp"
#include "termcolor.hpp"
#include "utils.hpp"

int main(int argc, const char * argv[]) {
    autocorrector ac = autocorrector();
    
    std::string test = "Car w:as mo.ving dir,ectly into the voi, nevtheles;s I ws dru'nk";
    std::string w;
    std::stringstream ss(test);
    std::vector<std::string> words;
    std::vector<std::string> wordsPunc;
    std::vector<std::stack<std::string>> results;
    
    while (ss >> w) {
        wordsPunc.push_back(w);
        utils::removePunctuation(w);
        words.push_back(w);
    }
    std::cout << test << std::endl;
    
    for (auto word : words) {
        auto ret = ac.correctWord(word);
        if (ret.size() == 0) {
            std::cout << word << std::endl;
        } else {
            std::cout << word << " corrections: ";
            for (auto correction : ret) {
                std::cout << correction << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
