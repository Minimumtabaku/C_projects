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
    
    std::string test = "milt";
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
    
    std::cout << "------------------TIME-------------------" << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    
    
    ///THIS PART IS IN PARELLEL
    std::vector<std::promise<autocorrector::vectorOfWords>> promisesVector;
    std::vector<std::future<autocorrector::vectorOfWords>> futureVector;
    std::vector<std::thread> threadsVector;
    
    start = std::chrono::high_resolution_clock::now();
    
    for (auto word : words) {
        //pushni novou promise a future do vectoru
        std::promise<std::vector<std::string>> promise;
        //nabinduj promise a future
        std::future<std::vector<std::string>> future = promise.get_future();
        std::thread th(&autocorrector::correctWordParallel,&ac,std::ref(word),std::move(promise));
        th.join();
        std::cout << "1";
        future.wait();
        const autocorrector::vectorOfWords vec = future.get();
        
        for (auto const& correction : vec) {
            std::cout << correction << " ";
        }
//        futureVector.push_back(std::move(future));
//        //tady nekde asi zacne thread
//        threadsVector.push_back();
    }
//    for ( auto& future : futureVector) {
//        threadsVector.at(0).join();
//        std::cout << "1";
//        const autocorrector::vectorOfWords vec = future.get();
//        future.wait();
//        for (auto const& correction : vec) {
//            std::cout << correction << " ";
//        }
//    }
    
    end = std::chrono::high_resolution_clock::now();
    std::cout << "------------------TIME-------------------" << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    
    return 0;
}
