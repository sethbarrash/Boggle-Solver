#include <queue>
#include "WordTree.h"

using std::queue;

int XADJ [8] = {-1, -1, -1,  0,  0,  1,  1,  1};
int YADJ [8] = {-1,  0,  1, -1,  1, -1,  0,  1};

struct BoggleNode {
    char letter;
    int x;
    int y;
    char tentative_word [17];
    BoggleNode* children [8];
    BoggleNode* parent;
    Node* branch;
    bool is_end_of_word;
};

typedef BoggleNode* BoggleNodePtr;

class BoggleSolver {
    public:
        char** board;
        WordTree t;
        queue<BoggleNodePtr> q;
        BoggleNodePtr btree;

        void populateChildren(BoggleNodePtr b);
        BoggleNodePtr buildBoggleTree(int x0, int y0);
};

void BoggleSolver::populateChildren(BoggleNodePtr b) {
    int i,j,xnew,ynew,letter_idx;
    char lnew;
    BoggleNodePtr bk;

    for (int k=0; k<8; k++) {
        i = XADJ[k];
        j = YADJ[k];
        xnew = b->x+i;
        ynew = b->y+j;
        if (xnew >= 0 && ynew >= 0 /* Check that it hasn't been used before */) {
            lnew = board[xnew][ynew];
            letter_idx = lnew-ascii_a;
            if (b->branch->children[letter_idx]) {
                b->children[k] = new BoggleNode;
                bk = b->children[k];

                q.push(bk);
                bk->letter = lnew;
                bk->x = i;
                bk->y = j;
                bk->parent = b;
                bk->branch = b->branch->children[letter_idx];
                bk->is_end_of_word = bk->branch->is_end_of_word;
            }
        }
    }
}

BoggleNodePtr BoggleSolver::buildBoggleTree(int x0, int y0) {
    BoggleNodePtr root = new BoggleNode;
    BoggleNodePtr b = root;
    root->letter = board[x0][y0];
    root->x = x0;
    root->y = y0;
    int letter_idx = root->letter-ascii_a;
    root->branch = t.root->children[letter_idx];
    
    populateChildren(root);
    while (!q.empty()) {
        b = q.front();
        q.pop();
        populateChildren(b);
    }

    return root;
}