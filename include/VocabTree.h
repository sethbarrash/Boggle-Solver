#ifndef VOCABTREE_H
#define VOCABTREE_H

#include <fstream>
using namespace std;

static const int ascii_a = 97;
static const int MAX_EXPECTED_WORD_LENGTH = 100;
static const int LENGTH_OF_ALPHABET = 26;
static const int MIN_BOGGLE_WORD_LENGTH = 3;
static const int N_SQUARES_ON_BOGGLE_BOARD = 16;

struct VocabNode {
    VocabNode* children [LENGTH_OF_ALPHABET];
    bool is_end_of_word;
};
typedef VocabNode* VocabNodePtr;

VocabNode* new_node();

bool is_valid_boggle_word(char* word);

class VocabTree {
    public:
        VocabNodePtr root;
        uint8_t max_word_length;

        VocabTree();
        VocabTree(char* inputFile);
        ~VocabTree();

    private:
        void add_word(char* word);
        void add_file(char* inputFile);
        void delete_subtree(VocabNodePtr subtree);
        bool is_word(char* w);
};

#endif