#ifndef BOGGLETREE_H
#define BOGGLETREE_H
#include "VocabTree.h"

const int MAX_WORD_LENGTH = 17;

struct BoggleNode {
  char letter;
  int x;
  int y;
  char word_so_far [MAX_WORD_LENGTH];
  BoggleNode* children [8];
  BoggleNode* parent;
  VocabNode* vnode;
  bool is_end_of_word;
};

typedef BoggleNode* BoggleNodePtr;

BoggleNode* new_BoggleNode() {
  BoggleNode* x = new BoggleNode;
  *x = {0, 0, 0, {0}, {0}, 0, 0, 0};
  return x;
}

bool is_ancestor(BoggleNodePtr b, int x0, int y0);

class BoggleTree {
  public:
    BoggleNodePtr root;
    void delete_subtree(BoggleNodePtr t);
    BoggleTree();
    ~BoggleTree();
};

bool is_ancestor(BoggleNodePtr b, int x0, int y0) {
  while (b->parent) {
    b = b->parent;
    if (b->x == x0 && b->y == y0) return 1;
  }
  return 0;
}

void BoggleTree::delete_subtree(BoggleNodePtr t) {
  for (int k=0; k<8; k++) 
    if (t->children[k]) 
      delete_subtree(t->children[k]);
  delete t;
}

BoggleTree::BoggleTree() {
  root = NULL;
}

BoggleTree::~BoggleTree() {
  delete_subtree(root);
}

#endif