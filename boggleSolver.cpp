#include "WordTree.h"

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

void populateChildren(char** board, BoggleNodePtr b) {
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

BoggleNodePtr buildBoggleTree(char** board, WordTree t, int x0, int y0) {
    BoggleNodePtr root = new BoggleNode;
    BoggleNodePtr b = root;
    root->letter = board[x0][y0];
    root->x = x0;
    root->y = y0;
    int letter_idx = root->letter-ascii_a;
    root->branch = t.root->children[letter_idx];
    
    // Populate children in either breadth-first or depth-first fashion

    return root;
}