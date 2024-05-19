#include "BoggleTree.h"

BoggleNode* new_BoggleNode() {
  BoggleNode* x = new BoggleNode;
  *x = {0, 0, 0, {0}, {0}, 0, 0, 0};
  return x;
}

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