#ifndef BOGGLESOLVER_H
#define BOGGLESOLVER_H

#include <cstring>
#include <queue>
#include <set>
#include <string>
#include "BoggleTree.h"


using std::set;
using std::queue;

typedef set<string> word_set;

static char DEFAULT_VOCAB_FILE [100] = "boggleWords.txt";
static int XADJ [8] = {-1, -1, -1,  0,  0,  1,  1,  1};
static int YADJ [8] = {-1,  0,  1, -1,  1, -1,  0,  1};

void harvest_node(BoggleNodePtr bn, word_set& ws, int depth);
void harvest(BoggleTree& bt, word_set& ws);
word_set harvest(BoggleTree& bt);
void add_children_to_queue(BoggleNodePtr bn, queue<BoggleNodePtr>& q);

class BoggleSolver {
    public:
        char board [4][4];
        VocabTree t;

        BoggleSolver(char board [][4]);
        BoggleSolver(char board [][4], VocabTree t);
        void add_board(char (*board)[4]);
        void add_VocabTree(VocabTree t);
        BoggleNodePtr create_child(BoggleNodePtr b, int x, int y, char l);
        void populateChildren(BoggleNodePtr b);
        void initialize_BoggleTree(BoggleTree& bt, int x, int y);
        void build_BoggleTree(BoggleTree& bt);
        void build_BoggleTree(BoggleTree& bt, int x, int y);
        word_set solve_board();
        word_set solve_board(char (*board)[4]);
};

#endif