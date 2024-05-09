#include <fstream>
using namespace std;

const int ascii_a = 97;
const int MAX_ENGLISH_WORD_LENGTH = 100;

struct VocabNode {
    VocabNode* children [26];
    bool is_end_of_word;
};
typedef VocabNode* VocabNodePtr;

VocabNode* new_node() {
    VocabNode* x = new VocabNode;
    *x = {{0},0};
    return x;
}

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

void VocabTree::add_word(char* word) {
    char*   letter = word;
    VocabNodePtr branch = root;
    int letter_idx;
    while (*letter) {
        letter_idx = *(letter++)-ascii_a;
        if (!branch->children[letter_idx]) branch->children[letter_idx] = new_node();
        branch = branch->children[letter_idx];
    }
    branch->is_end_of_word = 1;
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
    VocabNodePtr branch = root;
    VocabNodePtr next_branch = root;
    int letter_idx;
    
    while (*i) {
        letter_idx = *(i++)-ascii_a;
        next_branch = branch->children[letter_idx];
        if (next_branch) branch = next_branch;
        else return 0;
    }
    if (branch->is_end_of_word) return 1;
    return 0;
}

VocabTree::~VocabTree() {
    delete_subtree(root);
}