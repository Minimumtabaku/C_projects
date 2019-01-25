//
//  Trie.hpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <iostream>
class trie{
private:
    
    class trieNode{
    protected:
        char n_character;
        bool isEnd;
        trieNode(char character):n_character(character){
            isEnd = false;
        };
        
        };
};
#endif /* Trie_hpp */
