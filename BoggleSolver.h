#include <queue>
#include "BoggleTree.h"

using std::queue;

int XADJ [8] = {-1, -1, -1,  0,  0,  1,  1,  1};
int YADJ [8] = {-1,  0,  1, -1,  1, -1,  0,  1};

class BoggleSolver {
    public:
        char board [4][4];
        WordTree t;
        // List of words

        BoggleSolver(char board [][4], WordTree t);
        void add_board(char (*board)[4]);
        void add_WordTree(WordTree t);
        BoggleNodePtr create_child(BoggleNodePtr b, int x, int y, char l);
        void populateChildren(BoggleNodePtr b);
        BoggleTree initialize_BoggleTree(int x, int y, char l);
        BoggleTree buildBoggleTree(int x0, int y0);
        // harvest(BoggleTree btree, List);
        // List findWords();
};

BoggleSolver::BoggleSolver(char input_board [][4], WordTree wt) {
    for (int i=0; i<4; i++) 
        for (int j=0; j<4; j++) board[i][j] = input_board[i][j];
    t = wt;
}

void BoggleSolver::add_board(char (*input_board)[4]) {
    for (int i=0; i<4; i++) 
        for (int j=0; j<4; j++) board[i][j] = input_board[i][j];
}

void BoggleSolver::add_WordTree(WordTree wt) {
    t = wt;
}

BoggleNodePtr BoggleSolver::create_child(BoggleNodePtr b, int x, int y, char l) {
    BoggleNodePtr child = new_BoggleNode();
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
    BoggleTree bt;
    bt.root = new_BoggleNode();
    bt.root->letter = board[x][y];
    bt.root->x = x;
    bt.root->y = y;
    int letter_idx = bt.root->letter-ascii_a;
    bt.root->branch = t.root->children[letter_idx];
    return bt;
}

BoggleTree BoggleSolver::buildBoggleTree(int x0, int y0) {
    char l = board[x0][y0];
    BoggleTree bt = initialize_BoggleTree(x0,y0,l);
    BoggleNodePtr b = bt.root;

    queue<BoggleNodePtr> q;
    populateChildren(b);
    while (!q.empty()) {
        b = q.front();
        q.pop();
        populateChildren(b);
        for (int k=0; k<8; k++) if (b->children[k]) q.push(b->children[k]);
    }

    return bt;
}