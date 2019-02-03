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
    std::vector<std::string> words;
    //std::stringstream wordsToCorrect;
    autocorrector ac;
    bool parallel = false;
    bool file = false;
    bool dict = false;
    for(int i = 1; i < argc; i++){
        std::string argument(argv[i]);
        if(argument == "-p" || argument == "--parallel"){
            parallel = true;
        } else if(argument == "-f" || argument == "--file"){
            file = true;
            std::string path = argv[++i];
            ac = autocorrector(path);
        }else if(argument == "-d" || argument == "--dictionary"){
            dict = true;
            if (file == true) {
                std::cerr << "you can either provide file with words of the dictionary or use words as input, not both" << std::endl;
                return -1;
            }
            std::map<char,std::set<std::string>> letterToWordMap;
            //TODO: check for i increment
            std::string nextArgument = argv[++i];
            while ( nextArgument.find(":end") == std::string::npos && nextArgument.find("-") == std::string::npos ) {
                
                auto it = letterToWordMap.find(nextArgument[0]);
                //if keys is in the dictionary
                if (it == letterToWordMap.end()) {
                    std::set<std::string> newSet;
                    newSet.insert(nextArgument);
                    letterToWordMap.insert(std::pair<char,std::set<std::string>>(nextArgument[0], newSet));
                }else{
                    (*it).second.insert(nextArgument);
                }
                nextArgument = argv[++i];
            }
            //to not read ":end" as a word, just skip it
//            i++;
            ac = autocorrector(letterToWordMap);
        }else if(argument == "-h" || argument == "--help"){
            std::string help = "Autocorrect HW PJC\nThis is a command line tool for simple autocorrection using Levenstein distance and SIFT3 algorithm\nUsage: autocorrector [options] [words to correct] \nOptions:\n -p, --parallel parallel execution of algorithm\n -d --dictionary followed by the words of the dictionary, use \":end\" to indicate end of the dictionary\n-f --file followed by the path to the file with dictionary";
            std::cout << help << std::endl;
            return -1;
        }else{
            if (argument.find("-") != std::string::npos) {
                std::cerr << "option not supported" << std::endl;
                return -1;
            }else{
                words.push_back(argument);
            }
        }
    }
    
    if (!dict && !file) {
        ac = autocorrector();
    }
    
    if (words.size() == 0) {
        std::cerr << "you have to provide words to correct, use -h or --help to see help" << std::endl;
        return -1;
    }
    
//    std::string test = wordsToCorrect.str();
//    std::string w;
//    std::stringstream ss(test);
    
//    std::vector<std::string> wordsPunc;
    
//    while (ss >> w) {
//        wordsPunc.push_back(w);
//        utils::removePunctuation(w);
//        words.push_back(w);
//    }
    for (auto word : words) {
        utils::removePunctuation(word);
    }
    if (parallel) {
        std::vector<std::promise<autocorrector::vectorOfWords>> promisesVector;
        std::vector<std::future<autocorrector::vectorOfWords>> futureVector;
        std::vector<std::thread> threadsVector;
        
        auto start = std::chrono::high_resolution_clock::now();
        
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
//                std::cout << "nothing to do" << std::endl;
                threadsVector[i].join();
            }else{
                for (auto const& correction : vec) {
                    std::cout << correction << " ";
                }
                std::cout << std::endl;
                threadsVector[i].join();
            }
            
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "------------------TIME-------------------4444444" << std::endl;
        std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    }else{
        auto start = std::chrono::high_resolution_clock::now();
        
        /// THIS IS STANDARD WAY OF DOING SHIT
        
        for (auto word : words) {
            auto ret = ac.correctWord(word);
            
            if (ret.size() == 0) {
                std::cout << word << std::endl;
            } else {
//                std::cout << word << " corrections: ";
                for (auto correction : ret) {
                    std::cout << correction << " ";
                }
                std::cout << std::endl;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "------------------TIME-------------------11111" << std::endl;
        std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
        
        
         start = std::chrono::high_resolution_clock::now();
        
        /// THIS IS STANDARD WAY OF DOING SHIT
        
        for (auto word : words) {
            auto ret = ac.correctWord2(word);
            
            if (ret.size() == 0) {
                std::cout << word << std::endl;
            } else {
                //                std::cout << word << " corrections: ";
                for (auto correction : ret) {
                    std::cout << correction << " ";
                }
                std::cout << std::endl;
            }
        }
         end = std::chrono::high_resolution_clock::now();
        std::cout << "------------------TIME-------------------2222222" << std::endl;
        std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
        
        start = std::chrono::high_resolution_clock::now();
        
        /// THIS IS STANDARD WAY OF DOING SHIT
        
        for (auto word : words) {
            auto ret = ac.correctWord3(word);
            
            if (ret.size() == 0) {
                std::cout << word << std::endl;
            } else {
                //                std::cout << word << " corrections: ";
                for (auto correction : ret) {
                    std::cout << correction << " ";
                }
                std::cout << std::endl;
            }
        }
        end = std::chrono::high_resolution_clock::now();
        std::cout << "------------------TIME-------------------33333333" << std::endl;
        std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
        
    }
    
    
//
//
//    /// THIS IS STANDARD WAY OF DOING SHIT 22222
//    start = std::chrono::high_resolution_clock::now();
//    std::cout << test << std::endl;
//
//    for (auto word : words) {
//        auto ret = ac.correctWord2(word);
//
//        if (ret.size() == 0) {
//            std::cout << word << std::endl;
//        } else {
//            std::cout << word << " corrections: ";
//            for (auto correction : ret) {
//                std::cout << correction << " ";
//            }
//            std::cout << std::endl;
//        }
//    }
//    end = std::chrono::high_resolution_clock::now();
//    std::cout << "------------------TIME-------------------222222222" << std::endl;
//    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
//
//
//    /// THIS IS STANDARD WAY OF DOING SHIT 3333333
//    start = std::chrono::high_resolution_clock::now();
//    std::cout << test << std::endl;
//
//    for (auto word : words) {
//        auto ret = ac.correctWord3(word);
//
//        if (ret.size() == 0) {
//            std::cout << word << std::endl;
//        } else {
//            std::cout << word << " corrections: ";
//            for (auto correction : ret) {
//                std::cout << correction << " ";
//            }
//            std::cout << std::endl;
//        }
//    }
//    end = std::chrono::high_resolution_clock::now();
//    std::cout << "------------------TIME-------------------33333333333" << std::endl;
//    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
//
//
//    ///THIS PART IS IN PARELLEL
//
    

    return 0;
}
