#include <cassert>
#include <iostream>
#include "VocabTree.h"

void test_is_valid_boggle_word()
{
    char test_word0 [100] = "quo";
    assert(is_valid_boggle_word(test_word0) == 1);
    char test_word1 [100] = "computer";
    assert(is_valid_boggle_word(test_word1) == 1);
    char test_word2 [100] = "united";
    assert(is_valid_boggle_word(test_word1) == 1);
    char test_word3 [100] = "a";
    assert(is_valid_boggle_word(test_word1) == 0);
    char test_word4 [100] = "ab";
    assert(is_valid_boggle_word(test_word1) == 0);
    char test_word5 [100] = "ad";
    assert(is_valid_boggle_word(test_word1) == 0);
    char test_word6 [100] = "administrators";
    assert(is_valid_boggle_word(test_word1) == 1);
    char test_word7 [100] = "i";
    assert(is_valid_boggle_word(test_word1) == 0);
    char test_word8 [100] = "characterization";
    assert(is_valid_boggle_word(test_word1) == 1);
    char test_word9 [100] = "responsibilities";
    assert(is_valid_boggle_word(test_word1) == 1);
    char test_word10 [100] = "telecommunications";
    assert(is_valid_boggle_word(test_word1) == 0);
}

int main() {
    char adam [5] = "adam";
    char eve  [4] = "eve";
    VocabTree t;
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
    VocabTree t1 = VocabTree(input_file);
    t.add_file(input_file);
    char bathrooms [20] = "bathrooms";
    assert(t.is_word(bathrooms));
}
