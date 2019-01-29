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
#include <thread>
#include <future>
#include <chrono>
#include "Autocorrector.hpp"
#include "termcolor.hpp"
#include "utils.hpp"

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}


int main(int argc, const char * argv[]) {
    autocorrector ac = autocorrector();
    
    std::string test = "There is uselly no pace to recomend, to clarigy don't you dare";
    std::string w;
    std::stringstream ss(test);
    std::vector<std::string> words;
    std::vector<std::string> wordsPunc;
    
    while (ss >> w) {
        wordsPunc.push_back(w);
        utils::removePunctuation(w);
        words.push_back(w);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
   
    /// THIS IS STANDARD WAY OF DOING SHIT
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
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "------------------TIME-------------------" << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    
    
    
    /// THIS IS STANDARD WAY OF DOING SHIT 22222
    start = std::chrono::high_resolution_clock::now();
    std::cout << test << std::endl;
    
    for (auto word : words) {
        auto ret = ac.correctWord2(word);
        
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
    end = std::chrono::high_resolution_clock::now();
    std::cout << "------------------TIME-------------------" << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    
    
    ///THIS PART IS IN PARELLEL
    std::vector<std::promise<std::string>> promisesVector;
    std::vector<std::future<std::string>> futureVector;
    std::vector<std::thread> threadsVector;
    
    
    
    for (auto word : words) {
        //pushni novou promise a future do vectoru
        //nabinduj promise a future
        //tady nekde asi zacne thread
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
