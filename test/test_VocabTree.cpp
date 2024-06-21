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

void test_simple_words()
{
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
    VocabNodePtr c_node = t.root->children[2];
    VocabNodePtr a_node = c_node->children[0];
    VocabNodePtr n_node = a_node->children[13];
    for (int i = 0; i < 26; i++) if (i != 2) assert(!t.root->children[i]);
    for (int i = 1; i < 26; i++) assert(!c_node->children[i]);
    for (int i = 0; i < 26; i++) if (i != 13) assert(!a_node->children[i]);
    for (int i = 0; i < 26; i++) assert(!n_node->children[i]);
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
    VocabNodePtr p_node = t.root->children[15];
    VocabNodePtr o_node = p_node->children[14];
    VocabNodePtr r_node = o_node->children[17];
    VocabNodePtr t_node = r_node->children[19];
    for (int i = 0; i < 26; i++) if (i != 2 && i != 15) assert(!t.root->children[i]);
    for (int i = 0; i < 26; i++) if (i != 14) assert(!p_node->children[i]);
    for (int i = 0; i < 26; i++) if (i != 17) assert(!o_node->children[i]);
    for (int i = 0; i < 26; i++) if (i != 19) assert(!r_node->children[i]);
    for (int i = 0; i < 26; i++) assert(!t_node->children[i]);
    assert(t.is_word(port));

    for (int i = 0; i < 26; i++) if (i != 2 && i != 15) assert(!t.root->children[i]);
    for (int i = 1; i < 26; i++) assert(!c_node->children[i]);
    for (int i = 0; i < 26; i++) if (i != 13) assert(!a_node->children[i]);
    for (int i = 0; i < 26; i++) assert(!n_node->children[i]);
}

void test_several_words()
{
    char can   [MAX_EXPECTED_WORD_LENGTH] = "can";
    char cans  [MAX_EXPECTED_WORD_LENGTH] = "cans";
    char cant  [MAX_EXPECTED_WORD_LENGTH] = "cant";
    char cart  [MAX_EXPECTED_WORD_LENGTH] = "cart";
    char carts [MAX_EXPECTED_WORD_LENGTH] = "carts";
    char cap   [MAX_EXPECTED_WORD_LENGTH] = "cap";
    char caps  [MAX_EXPECTED_WORD_LENGTH] = "caps";
    char carp  [MAX_EXPECTED_WORD_LENGTH] = "carp";
    char carps [MAX_EXPECTED_WORD_LENGTH] = "carps";
    char cot   [MAX_EXPECTED_WORD_LENGTH] = "cot";
    char cots  [MAX_EXPECTED_WORD_LENGTH] = "cots";
    char corp  [MAX_EXPECTED_WORD_LENGTH] = "corp";
    char corps [MAX_EXPECTED_WORD_LENGTH] = "corps";
    char cuts  [MAX_EXPECTED_WORD_LENGTH] = "cuts";
    char cut   [MAX_EXPECTED_WORD_LENGTH] = "cut";

    VocabTree t;
    t.add_word(can);
    t.add_word(cans);
    t.add_word(cant);
    t.add_word(cart);
    t.add_word(carts);
    t.add_word(cap);
    t.add_word(caps);
    t.add_word(carp);
    t.add_word(carps);
    t.add_word(cot);
    t.add_word(cots);
    t.add_word(corp);
    t.add_word(corps);
    t.add_word(cut);
    t.add_word(cuts);
}

void test_boggle_words()
{
    char input_file [100] = "boggleWords.txt";
    VocabTree t = VocabTree(input_file);
    // char bathrooms [20] = "bathrooms";
    // assert(t.is_word(bathrooms));
    // char characterization [20] = "characterization";
    // assert(t.is_word(characterization));
    // cout << "Max word length = " << t.max_word_length << '\n';
    // assert(t.max_word_length == 16);
}

int main() {
    test_simple_words();
    test_several_words();
    test_boggle_words();
}