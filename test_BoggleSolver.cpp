#include <cassert>
#include <iostream>
#include "BoggleSolver.h"

using std::cout;

int max(int* x, int length) {
  int maxx = x[0];
  for (int i=1; i<length; i++) if (x[i] > maxx) maxx = x[i];
  return maxx;
}

int get_depth(BoggleNode* n) {
  int depths [8];
  for (int i=0; i<8; i++) 
    if (n->children[i]) depths[i] = get_depth(n->children[i]);
    else depths[i] = 0;
  return 1+max(depths, 8);
}

int get_size(BoggleNode* n) {
  int size = 1;
  for (int i=0; i<8; i++)
    if (n->children[i]) size+= get_size(n->children[i]);
  return size;
}

int main() {
    char board0[4][4] = {
        {'a', 'r', 'g', 't'}, 
        {'n', 'e', 'v', 'r'}, 
        {'d', 'f', 'b', 'a'}, 
        {'t', 'w', 'e', 'n'}
    };
    char board1[4][4] = {
        {'e', 'e', 'p', 't'}, 
        {'a', 'r', 'a', 'u'}, 
        {'w', 't', 'y', 'u'}, 
        {'c', 'y', 'j', 'l'}
    };
    char board2[4][4] = {
        {'w', 'a', 't', 'u'}, 
        {'u', 'i', 'g', 'b'}, 
        {'h', 't', 'y', 'z'}, 
        {'e', 'i', 'd', 'o'}
    };
    char board3[4][4] = {
        {'n', 't', 'o', 'b'}, 
        {'f', 'a', 'x', 'm'}, 
        {'r', 'o', 'e', 'g'}, 
        {'r', 'n', 'h', 's'}
    };
    char input_file [100] = "boggleWords.txt";
    WordTree t = WordTree(input_file);
    BoggleSolver bs = BoggleSolver(board3,t);
    BoggleTree* bt;
    word_list wl;
    
    for (int i=0; i<4; i++) {
      for (int j=0; j<4; j++) {
        bt = new BoggleTree;
        bs.initialize_BoggleTree(*bt,i,j);
        bs.buildBoggleTree(*bt);
        harvest(*bt,wl);
        delete bt;
      }
    }

    // BoggleTree bt = bs.buildBoggleTree(0,0);
    // assert(bt.root->children[4]);
    // assert(bt.root->children[6]);
    // assert(bt.root->children[7]);
    // assert(bt.root->children[4]->children[6]);
    // assert(bt.root->children[6]->children[6]);


    cout << "Words on this board:\n";
    word_list::iterator iter;
    for (iter = wl.begin(); iter != wl.end(); iter++)
      cout << *iter << '\n';
  
    return 0;
}