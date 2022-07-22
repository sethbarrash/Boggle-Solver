#include <queue>
#include "BoggleTree.h"

using std::queue;

int XADJ [8] = {-1, -1, -1,  0,  0,  1,  1,  1};
int YADJ [8] = {-1,  0,  1, -1,  1, -1,  0,  1};

class BoggleSolver {
    public:
        char** board;
        WordTree t;
        queue<BoggleNodePtr> q;
        // List of words

        void add_board(char** board);
        void add_WordTree(WordTree t);
        BoggleNodePtr create_child(BoggleNodePtr b, int x, int y, char l);
        void populateChildren(BoggleNodePtr b);
        BoggleTree initialize_BoggleTree(int x, int y, char l);
        BoggleTree buildBoggleTree(int x0, int y0);
        // harvest(BoggleTree btree, List);
        // List findWords();
};

void add_board(char** board) {
    board = board;
}

void add_WordTree(WordTree t) {
    t = t;
}

BoggleNodePtr BoggleSolver::create_child(BoggleNodePtr b, int x, int y, char l) {
    BoggleNodePtr child = new BoggleNode;
    child->letter = l;
    child->x = x;
    child->y = y;
    child->parent = b;
    child->branch = b->branch->children[l-ascii_a];
    child->is_end_of_word = child->branch->is_end_of_word;
    return child;
}

void BoggleSolver::populateChildren(BoggleNodePtr b) {
    int i,j,xnew,ynew;
    char lnew;

    for (int k=0; k<8; k++) {
        i = XADJ[k];
        j = YADJ[k];
        xnew = b->x+i;
        ynew = b->y+j;
        if (xnew >= 0 && ynew >= 0 && !is_ancestor(b,xnew,ynew)) {
            lnew = board[xnew][ynew];
            if (b->branch->children[lnew-ascii_a])
                b->children[k] = create_child(b,xnew,ynew,lnew);
        }
    }
}

BoggleTree BoggleSolver::initialize_BoggleTree(int x, int y, char l) {
    BoggleNodePtr root = new BoggleNode;
    root->letter = board[x][y];
    root->x = x;
    root->y = y;
    int letter_idx = root->letter-ascii_a;
    root->branch = t.root->children[letter_idx];
}

BoggleTree BoggleSolver::buildBoggleTree(int x0, int y0) {
    char l = board[x0][y0];
    BoggleTree bt = initialize_BoggleTree(x0,y0,l);
    BoggleNodePtr b = bt.root;

    populateChildren(b);
    while (!q.empty()) {
        b = q.front();
        q.pop();
        populateChildren(b);
        for (int k=0; k<8; k++) if (b->children[k]) q.push(b->children[k]);
    }

    return bt;
}