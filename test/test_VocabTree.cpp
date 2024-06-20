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
    char can  [MAX_EXPECTED_WORD_LENGTH] = "can";
    char port [MAX_EXPECTED_WORD_LENGTH] = "port";
    VocabTree t;
    assert(!t.is_word(can));
    t.add_word(can);
    assert(t.root->children[2]);
    assert(!t.root->children[2]->is_end_of_word);
    assert(t.root->children[2]->children[0]);
    assert(!t.root->children[2]->children[0]->is_end_of_word);
    assert(t.root->children[2]->children[0]->children[13]);
    assert(t.root->children[2]->children[0]->children[13]->is_end_of_word);
    for (int i = 0; i < 26; i++) if (i != 2) assert(!t.root->children[i]);
    assert(t.is_word(can));

    assert(!t.is_word(port));
    t.add_word(port);
    assert(t.root->children[15]);
    assert(!t.root->children[15]->is_end_of_word);
    assert(t.root->children[15]->children[14]);
    assert(!t.root->children[15]->children[14]->is_end_of_word);
    assert(t.root->children[15]->children[14]->children[17]);
    assert(!t.root->children[15]->children[14]->children[17]->is_end_of_word);
    assert(t.root->children[15]->children[14]->children[17]->children[19]);
    assert(t.root->children[15]->children[14]->children[17]->children[19]->is_end_of_word);
    for (int i = 0; i < 26; i++) 
        if (i != 2 && i != 15) assert(!t.root->children[i]);
    assert(t.is_word(port));

    char input_file [100] = "boggleWords.txt";
    VocabTree t1 = VocabTree(input_file);
    t.add_file(input_file);
    char bathrooms [20] = "bathrooms";
    assert(t.is_word(bathrooms));
    char characterization [20] = "characterization";
    assert(t.is_word(characterization));
    cout << "Max word length = " << t.max_word_length << '\n';
    assert(t.max_word_length == 16);
}
