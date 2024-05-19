#ifndef BOGGLETREE_H
#define BOGGLETREE_H
#include "VocabTree.h"

static const int MAX_WORD_LENGTH = 17;

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

BoggleNode* new_BoggleNode();
bool is_ancestor(BoggleNodePtr b, int x0, int y0);

class BoggleTree {
  public:
    BoggleNodePtr root;
    void delete_subtree(BoggleNodePtr t);
    BoggleTree();
    ~BoggleTree();
};

#endif