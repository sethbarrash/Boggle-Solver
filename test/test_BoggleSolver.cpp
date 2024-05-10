#include <cassert>
#include <iostream>
#include "BoggleSolver.h"
#include "mergesort.h"

using std::cout;

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
    VocabTree t = VocabTree(input_file);
    BoggleSolver bs = BoggleSolver(board3,t);
    word_list wl = bs.solve_board();

    word_list::iterator iter;
    for (iter = wl.begin(); iter != wl.end(); iter++) cout << *iter << '\n';

    return 0;
}