#include <cassert>
#include <iostream>
#include "WordTree.h"

int main() {
    char adam [5] = "adam";
    char eve  [4] = "eve";
    WordTree t;
    assert(!t.is_word(adam));
    t.add_word(adam);
    assert(t.root->children[0]);
    assert(t.root->children[0]->children[3]);
    assert(t.root->children[0]->children[3]->children[0]);
    assert(t.root->children[0]->children[3]->children[0]->children[12]);
    assert(t.root->children[0]->children[3]->children[0]->children[12]->is_end_of_word);
    for (int i=1; i<26; i++) assert(!t.root->children[i]);
    assert(t.is_word(adam));
    assert(!t.is_word(eve));

    char input_file [100] = "boggleWords.txt";
    WordTree t1 = WordTree(input_file);
    t.add_file(input_file);
    char bathrooms [20] = "bathrooms";
    assert(t.is_word(bathrooms));
}
