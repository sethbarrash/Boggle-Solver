#include <algorithm>
#include <chrono>
#include <cassert>
#include <chrono>
#include <iostream>
#include "BoggleSolver.h"
#include "mergesort.h"
#include "test_BoggleSolver_fixtures.h"

using std::cout;
using namespace std::chrono;

void test_board(char board [][4], word_set expected_words)
{
    BoggleSolver bs = BoggleSolver(board);
    word_set ws = bs.solve_board();
    if (ws != expected_words)
    {
        vector<string> missing_from_found;
        vector<string> missing_from_expected;
        vector<string>::iterator i, j;
        i = set_difference(
            ws.begin(),
            ws.end(),
            expected_words.begin(),
            expected_words.end(),
            missing_from_found.begin()
        );

        j = set_difference(
            expected_words.begin(),
            expected_words.end(),
            ws.begin(),
            ws.end(),
            missing_from_expected.begin()
        );

        cout << "The following words were expected but not found by the BoggleSolver:\n";
        for (i = missing_from_found.begin(); i != missing_from_found.end(); i++)
        {
            if (!(*i).empty()) cout << *i << '\n';
        }
        
        cout << "The following words were found by the BoggleSolver but not expected:\n";
        for (j = missing_from_expected.begin(); j != missing_from_expected.end(); j++)
        {
            if (!(*j).empty()) cout << *j << '\n';
        }
    }
}

int main()
{
    // char input_file [100] = "boggleWords.txt";
    // VocabTree t = VocabTree(input_file);
    // BoggleSolver bs = BoggleSolver(board0);

    auto start_time = high_resolution_clock::now();

    cout << "Solving board 0\n";
    test_board(board0, ws0);
    cout << "Solving board 1\n";
    test_board(board1, ws1);
    cout << "Solving board 2\n";
    test_board(board2, ws2);
    cout << "Solving board 3\n";
    test_board(board3, ws3);

    auto stop_time = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop_time - start_time);

    cout << "Took " << duration.count() / 1e6 << " seconds to solve 4 boggle boards.\n";

    return 0;
}