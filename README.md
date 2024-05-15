# Introduction #

Boggle is a board game where players have two minutes to find as many words as they can from a random 4x4 array of letters.  This library provides a class that quickly finds all the words on a Boggle board.

# Code overview #

The file `boggleWords.txt` contains a large set of English words.  The class `VocabTree` is a tree instantiated from this list.  For any string of letters, it is very fast to see if it is present in a `VocabTree`.  The class `BoggleSolver` efficiently searches for the subtree of the `VocabTree` which contains all the words from `boggleWords.txt` in the board.

# Example #

```
#include "BoggleSolver.h"
#include "VocabTree.h"

char input_file [100] = "boggleWords.txt";
VocabTree t = VocabTree(input_file);
char board0[4][4] = {
    {'a', 'r', 'g', 't'},
    {'n', 'e', 'v', 'r'},
    {'d', 'f', 'b', 'a'},
    {'t', 'w', 'e', 'n'}
};

BoggleSolver bs = BoggleSolver(board0, t);
word_set ws = bs.solve_board();
```