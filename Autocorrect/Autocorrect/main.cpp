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
    
    std::string test = "Instead, lazy evaluaation";
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
    std::cout << "------------------TIME-------------------11111" << std::endl;
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
    std::cout << "------------------TIME-------------------222222222" << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    
    
    /// THIS IS STANDARD WAY OF DOING SHIT 3333333
    start = std::chrono::high_resolution_clock::now();
    std::cout << test << std::endl;
    
    for (auto word : words) {
        auto ret = ac.correctWord3(word);
        
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
    std::cout << "------------------TIME-------------------33333333333" << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    
    
    ///THIS PART IS IN PARELLEL
    std::vector<std::promise<autocorrector::vectorOfWords>> promisesVector;
    std::vector<std::future<autocorrector::vectorOfWords>> futureVector;
    std::vector<std::thread> threadsVector;
    
    start = std::chrono::high_resolution_clock::now();
    
    for (auto& word : words) {
        //pushni novou promise a future do vectoru
        std::promise<std::vector<std::string>> promise;
        //nabinduj promise a future
        std::future<std::vector<std::string>> future = promise.get_future();
        futureVector.push_back(std::move(future));
        threadsVector.push_back(std::thread(&autocorrector::correctWordParallel,&ac,std::ref(word),std::move(promise)));
       
    }
    for (size_t i = 0; i < threadsVector.size(); i++) {
        futureVector[i].wait();
        const autocorrector::vectorOfWords vec = futureVector[i].get();
        if(vec.size() == 0){
            std::cout << "nothing to do" << std::endl;
            threadsVector[i].join();
        }else{
            for (auto const& correction : vec) {
                std::cout << correction << "::";
            }
            threadsVector[i].join();
        }
        
    }
    
    end = std::chrono::high_resolution_clock::now();
    std::cout << "------------------TIME-------------------4444444" << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    

    return 0;
}
