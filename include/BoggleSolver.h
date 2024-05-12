#include <cstring>
#include <queue>
#include <set>
#include <string>
#include "BoggleTree.h"

using std::set;
using std::queue;

typedef set<string> word_set;

int XADJ [8] = {-1, -1, -1,  0,  0,  1,  1,  1};
int YADJ [8] = {-1,  0,  1, -1,  1, -1,  0,  1};

void harvest_node(BoggleNodePtr bn, word_set& ws, int depth) {
    // Gather words from subtree pointed to by bn and put them into the list ws
    bn->word_so_far[depth] = bn->letter;
    if (bn->is_end_of_word) {
        string word_copy = bn->word_so_far;
        ws.insert(word_copy);
    }
    for (int k=0; k<8; k++) {
        BoggleNodePtr bk = bn->children[k];
        if (bk) {
            strcpy(bk->word_so_far,bn->word_so_far);
            harvest_node(bk, ws, depth+1);
        }
    }
}

void harvest(BoggleTree& bt, word_set& ws) {
    harvest_node(bt.root,ws,0);
}

word_set harvest(BoggleTree& bt) {
    word_set ws;
    BoggleNodePtr bn = bt.root;
    harvest_node(bn, ws, 0);

    return ws;
}

void add_children_to_queue(BoggleNodePtr bn, queue<BoggleNodePtr>& q) {
    for (int k=0; k<8; k++) if (bn->children[k]) q.push(bn->children[k]);
}

class BoggleSolver {
    public:
        char board [4][4];
        VocabTree t;

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

BoggleSolver::BoggleSolver(char input_board [][4], VocabTree wt) {
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            board[i][j] = input_board[i][j];
    t = wt;
}

void BoggleSolver::add_board(char (*input_board)[4]) {
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            board[i][j] = input_board[i][j];
}

void BoggleSolver::add_VocabTree(VocabTree wt) {
    t = wt;
}

BoggleNodePtr BoggleSolver::create_child(BoggleNodePtr b, int x, int y, char l) {
    BoggleNodePtr child = new_BoggleNode();
    child->letter = l;
    child->x = x;
    child->y = y;
    child->parent = b;
    child->vnode = b->vnode->children[l-ascii_a];
    child->is_end_of_word = child->vnode->is_end_of_word;
    return child;
}

void BoggleSolver::populateChildren(BoggleNodePtr b) {
    int i, j, xnew, ynew;
    char lnew;

    for (int k=0; k<8; k++) {
        i = XADJ[k];
        j = YADJ[k];
        xnew = b->x+i;
        ynew = b->y+j;
        if (xnew >= 0 && ynew >= 0 && xnew < 4 && ynew < 4 && !is_ancestor(b,xnew,ynew)) {
            lnew = board[xnew][ynew];
            if (b->vnode->children[lnew-ascii_a])
                b->children[k] = create_child(b,xnew,ynew,lnew);
        }
    }
}

void BoggleSolver::initialize_BoggleTree(BoggleTree& bt, int x, int y) {
    bt.root = new_BoggleNode();
    bt.root->letter = board[x][y];
    bt.root->x = x;
    bt.root->y = y;
    int letter_idx = bt.root->letter-ascii_a;
    bt.root->vnode = t.root->children[letter_idx];
}

void BoggleSolver::build_BoggleTree(BoggleTree& bt) {
    BoggleNodePtr b = bt.root;

    queue<BoggleNodePtr> q;
    populateChildren(b);
    add_children_to_queue(b,q);
    while (!q.empty()) {
        b = q.front();
        q.pop();
        populateChildren(b);
        add_children_to_queue(b,q);
    }
}

void BoggleSolver::build_BoggleTree(BoggleTree& bt, int x, int y) {
    initialize_BoggleTree(bt, x, y);
    build_BoggleTree(bt);
}

word_set BoggleSolver::solve_board() {
    BoggleTree* bt;
    word_set ws;
    add_board(board);
    
    for (int i=0; i<4; i++) {
      for (int j=0; j<4; j++) {
        bt = new BoggleTree;
        build_BoggleTree(*bt,i,j);
        harvest(*bt,ws);
        delete bt;
      }
    }

    return ws;
}

word_set BoggleSolver::solve_board(char (*board)[4]) {
    add_board(board);
    word_set ws = solve_board();
    return ws;
}
