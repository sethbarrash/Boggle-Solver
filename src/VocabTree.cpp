#include "VocabTree.h"

VocabNode* new_node() {
    VocabNode* x = new VocabNode;
    *x = {{0},0};
    return x;
}

void VocabTree::add_word(char* word) {
    char* letter = word;
    VocabNodePtr vnode = root;
    int letter_idx;
    while (*letter) {
        letter_idx = *(letter++)-ascii_a;
        if (!vnode->children[letter_idx]) vnode->children[letter_idx] = new_node();
        vnode = vnode->children[letter_idx];
    }
    vnode->is_end_of_word = 1;
}

void VocabTree::add_file(char* inputFile) {
    ifstream in_stream;
    in_stream.open(inputFile);

    char word [MAX_ENGLISH_WORD_LENGTH];
    while (!in_stream.eof()) {
        in_stream >> word;
        add_word(word);
    }

    in_stream.close();    
}

void VocabTree::delete_subtree(VocabNodePtr subtree) {
    if (subtree) for (int i=0; i<26; i++) delete_subtree(subtree->children[i]);
}

VocabTree::VocabTree() {
    root = new_node();
}

VocabTree::VocabTree(char* inputFile) {
    root = new_node();
    add_file(inputFile);
}

bool VocabTree::is_word(char* w) {
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

VocabTree::~VocabTree() {
    delete_subtree(root);
}