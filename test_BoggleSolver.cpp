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
    char input_file [100] = "boggleWords.txt";
    WordTree t = WordTree(input_file);
    BoggleSolver bs = BoggleSolver(board0,t);
    BoggleTree bt = bs.buildBoggleTree(0,0);
    assert(bt.root->children[4]);
    assert(bt.root->children[6]);
    assert(bt.root->children[7]);
    assert(bt.root->children[4]->children[6]);
    assert(bt.root->children[6]->children[6]);

    cout << "Before harvest:\n";
    cout << "Depth of boggle tree is " << get_depth(bt.root) << ".\n";
    cout << "Size of boggle tree is "  << get_size(bt.root)  << ".\n";

    word_list wl = harvest(bt);
    
    cout << "After harvest:\n";
    cout << "Depth of boggle tree is " << get_depth(bt.root) << ".\n";
    cout << "Size of boggle tree is "  << get_size(bt.root)  << ".\n";

    return 0;
}