#include <cstring>
#include <iostream>
#include "VocabTree.h"

VocabNode* VocabTree::new_node()
{
    VocabNode* x = new VocabNode;
    *x = {{0}, 0};
    return x;
}

bool is_valid_boggle_word(char* word)
{
    if (strlen(word) < MIN_BOGGLE_WORD_LENGTH) return false;
    char* letter_ptr = word;
    uint8_t n_boggle_squares = 0;

    while (*letter_ptr)
    {
        if (*letter_ptr == 'q' && *(++letter_ptr) != 'u') return false;
        n_boggle_squares++;
        letter_ptr++;
    }

    if (n_boggle_squares > N_SQUARES_ON_BOGGLE_BOARD) return false;
    return true;
}

void VocabTree::add_word(char* word)
{
    char* letter_ptr = word;
    VocabNodePtr vnode = root;
    int letter_idx, word_length = 0;

    while (*letter_ptr) {
        letter_idx = *(letter_ptr++) - ascii_a;
        if (!vnode->children[letter_idx])
            vnode->children[letter_idx] = new_node();
        vnode = vnode->children[letter_idx];
        word_length++;
    }

    if (word_length > max_word_length) max_word_length = word_length;
    vnode->is_end_of_word = 1;
}

void VocabTree::add_file(char* inputFile)
{
    ifstream in_stream;
    in_stream.open(inputFile);

    char word [MAX_EXPECTED_WORD_LENGTH];
    while (!in_stream.eof()) {
        in_stream >> word;
        if (is_valid_boggle_word(word)) add_word(word);
    }

    in_stream.close();    
}

void VocabTree::delete_subtree(VocabNodePtr subtree)
{
    for (int i = 0; i < LENGTH_OF_ALPHABET; i++)
    {
        if (subtree->children[i]) delete_subtree(subtree->children[i]);
    }
    delete subtree;
}

VocabTree::VocabTree()
{
    root = new_node();
    max_word_length = 0;
}

VocabTree::VocabTree(char* inputFile)
{
    root = new_node();
    add_file(inputFile);
}

bool VocabTree::is_word(char* w)
{
    if (!root) return 0;
    char* i = w;
    VocabNodePtr vnode = root;
    VocabNodePtr next_vnode = root;
    int letter_idx;
    
    while (*i) {
        letter_idx = *(i++)-ascii_a;
        next_vnode = vnode->children[letter_idx];
        if (next_vnode) vnode = next_vnode;
        else return 0;
    }
    if (vnode->is_end_of_word) return 1;
    return 0;
}

VocabTree::~VocabTree() 
{
    if (root) delete_subtree(root);
}