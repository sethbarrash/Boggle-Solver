#include "WordTree.h"

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
  for (int k=0; k<8; k++) delete_subtree(t->children[k]);
}

BoggleTree::BoggleTree() {
  root = NULL;
}

BoggleTree::~BoggleTree() {
  delete_subtree(root);
}
