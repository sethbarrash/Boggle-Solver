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
    if (ws != expected_words && !expected_words.empty() && !ws.empty())
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
    else if (ws != expected_words && ws.empty())
    {
        cout << "No words found.  Expected words were:\n";
        for (word_set::iterator i = expected_words.begin(); i != expected_words.end(); i++)
            if (!(*i).empty()) cout << *i << '\n';
    }
    else if (ws != expected_words && expected_words.empty())
    {
        cout << "No words were expected.  The following words were found:\n";
        for (word_set::iterator i = ws.begin(); i != ws.end(); i++)
            if (!(*i).empty()) cout << *i << '\n';
    }
}

int main()
{
    auto start_time = high_resolution_clock::now();

    test_board(board0, ws0);
    test_board(board1, ws1);
    test_board(board2, ws2);
    test_board(board3, ws3);
    test_board(board4, ws4);
    // if (ws3.end() == ws4.end()) cout << 1 << '\n';
    // else cout << 0 << '\n';

    auto stop_time = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop_time - start_time);

    cout << "Took " << duration.count() / 1e6 << " seconds to solve 4 boggle boards.\n";

    return 0;
}