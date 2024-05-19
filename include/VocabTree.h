#ifndef VOCABTREE_H
#define VOCABTREE_H
#include <fstream>
using namespace std;

static const int ascii_a = 97;
static const int MAX_ENGLISH_WORD_LENGTH = 100;

struct VocabNode {
    VocabNode* children [26];
    bool is_end_of_word;
};
typedef VocabNode* VocabNodePtr;

VocabNode* new_node();

class VocabTree {
    public:
        VocabNodePtr root;

        void add_word(char* word);
        void add_file(char* inputFile);
        void delete_subtree(VocabNodePtr subtree);
        VocabTree();
        VocabTree(char* inputFile);
        ~VocabTree();
        bool is_word(char* w);
};

#endif