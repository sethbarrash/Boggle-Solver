#include <fstream>
using namespace std;

int ascii_a = 97;
int MAX_WORD_LENGTH = 100;

struct Node {
    Node* children [26];
    bool is_end_of_word;
};
typedef Node* NodePtr;

Node* new_node() {
    Node* x = new Node;
    *x = {{0},0};
    return x;
}

class WordTree {
    public:
        NodePtr root;

        void add_word(char* word);
        void add_file(char* inputFile);
        void delete_subtree(NodePtr subtree);
        WordTree();
        WordTree(char* inputFile);
        ~WordTree();
        bool is_word(char* w);
};

void WordTree::add_word(char* word) {
    char*   letter = word;
    NodePtr branch = root;
    int letter_idx;
    while (*letter) {
        letter_idx = *(letter++)-ascii_a;
        if (!branch->children[letter_idx]) branch->children[letter_idx] = new_node();
        branch = branch->children[letter_idx];
    }
    branch->is_end_of_word = 1;
}

void WordTree::add_file(char* inputFile) {
    ifstream in_stream;
    in_stream.open(inputFile);

    char word [MAX_WORD_LENGTH];
    while (!in_stream.eof()) {
        in_stream >> word;
        add_word(word);
    }

    in_stream.close();    
}

void WordTree::delete_subtree(NodePtr subtree) {
    if (subtree) for (int i=0; i<26; i++) delete_subtree(subtree->children[i]);
}

WordTree::WordTree() {
    root = new_node();
}

WordTree::WordTree(char* inputFile) {
    root = new_node();
    add_file(inputFile);
}

bool WordTree::is_word(char* w) {
    if (!root) return 0;
    char* i = w;
    NodePtr branch = root;
    NodePtr next_branch = root;
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

WordTree::~WordTree() {
    delete_subtree(root);
}