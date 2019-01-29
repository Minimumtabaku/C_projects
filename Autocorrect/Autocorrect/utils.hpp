//
//  utils.cpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/27/19.
//  Copyright © 2019 Yevgen Ponomarenko. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
class utils{
public:
    /**
     *Function to erase punctuation. Remove doesn't reallocate, so you have to use it accompanied by string::eraase method.
     */
    static void removePunctuation(std::string &word){
        auto pred = [](char c){
            return c != '\'' && !isalpha(c);
        };
        word.erase (std::remove_if (word.begin (), word.end (), pred), word.end ());
    }
    /**
     *Creates a string containing only whitespaces.
     *@params number : number of whitespaces to be produced
     *@returns: string of whitespaces
     */
    static std::string makeWhitespaces(size_t number){
        size_t counter = 0;
        std::string stringToReturn = "";
        while(counter < number){
            stringToReturn += " ";
            counter++;
        }
        return stringToReturn;
    }
    
};

