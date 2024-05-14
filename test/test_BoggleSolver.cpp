#include <cassert>
#include <iostream>
#include "BoggleSolver.h"
#include "mergesort.h"
#include "test_BoggleSolver_fixtures.h"

using std::cout;

void test_board0(const VocabTree t)
{
    char board0[4][4] = {
        {'a', 'r', 'g', 't'},
        {'n', 'e', 'v', 'r'},
        {'d', 'f', 'b', 'a'},
        {'t', 'w', 'e', 'n'}
    };

    BoggleSolver bs = BoggleSolver(board0, t);
    word_set ws = bs.solve_board();
    assert(ws == ws3);
}

void test_board1(const VocabTree t)
{
    char board1[4][4] = {
        {'e', 'e', 'p', 't'},
        {'a', 'r', 'a', 'u'},
        {'w', 't', 'y', 'u'},
        {'c', 'y', 'j', 'l'}
    };

    BoggleSolver bs = BoggleSolver(board1, t);
    word_set ws = bs.solve_board();
    assert(ws == ws3);
}

void test_board2(const VocabTree t)
{
    char board2[4][4] = {
        {'w', 'a', 't', 'u'},
        {'u', 'i', 'g', 'b'},
        {'h', 't', 'y', 'z'},
        {'e', 'i', 'd', 'o'}
    };

    BoggleSolver bs = BoggleSolver(board2, t);
    word_set ws = bs.solve_board();
    assert(ws == ws2);
}

void test_board3(const VocabTree t)
{
    char board3[4][4] = {
        {'n', 't', 'o', 'b'},
        {'f', 'a', 'x', 'm'},
        {'r', 'o', 'e', 'g'},
        {'r', 'n', 'h', 's'}
    };

    BoggleSolver bs = BoggleSolver(board3, t);
    word_set ws = bs.solve_board();
    assert(ws == ws3);
}

int main()
{
    char input_file [100] = "boggleWords.txt";
    VocabTree t = VocabTree(input_file);

    test_board0(t);
    test_board1(t);
    test_board2(t);
    test_board3(t);

    return 0;
}