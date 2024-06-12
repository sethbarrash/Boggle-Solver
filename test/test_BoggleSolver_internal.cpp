#include <cassert>
#include <iostream>
#include "BoggleSolver.h"
#include "test_BoggleSolver_fixtures.h"

using std::cout;

void test_is_not_on_board() {
    assert(is_not_on_board(-1, -1) == 1);
    assert(is_not_on_board(-1, 0) == 1);
    assert(is_not_on_board(-1, 1) == 1);
    assert(is_not_on_board(-1, 2) == 1);
    assert(is_not_on_board(-1, 3) == 1);
    assert(is_not_on_board(-1, 4) == 1);
    assert(is_not_on_board(0, -1) == 1);
    assert(is_not_on_board(0, 0) == 0);
    assert(is_not_on_board(0, 1) == 0);
    assert(is_not_on_board(0, 2) == 0);
    assert(is_not_on_board(0, 3) == 0);
    assert(is_not_on_board(0, 4) == 1);
    assert(is_not_on_board(2, -1) == 1);
    assert(is_not_on_board(2, 0) == 0);
    assert(is_not_on_board(2, 1) == 0);
    assert(is_not_on_board(2, 2) == 0);
    assert(is_not_on_board(2, 3) == 0);
    assert(is_not_on_board(2, 4) == 1);
    assert(is_not_on_board(3, -1) == 1);
    assert(is_not_on_board(3, 0) == 0);
    assert(is_not_on_board(3, 1) == 0);
    assert(is_not_on_board(3, 2) == 0);
    assert(is_not_on_board(3, 3) == 0);
    assert(is_not_on_board(3, 4) == 1);
    assert(is_not_on_board(4, -1) == 1);
    assert(is_not_on_board(4, 0) == 1);
    assert(is_not_on_board(4, 1) == 1);
    assert(is_not_on_board(4, 2) == 1);
    assert(is_not_on_board(4, 3) == 1);
    assert(is_not_on_board(4, 4) == 1);
}

void test_make_first_step_0() {
    BoggleSolver bs(board0);
    assert(bs.ws.empty());
    assert(bs.q.empty());
    SolutionStep first_step = bs.make_first_step(0, 0);
    set<pair<uint8_t, uint8_t>> expected_squares_used;
    assert(expected_squares_used.empty());
    expected_squares_used.insert({0, 0});

    assert(first_step.x == 0);
    assert(first_step.y == 0);
    assert(first_step.depth == 0);
    assert(first_step.v);
    assert(first_step.word_so_far == "a");
    assert(first_step.squares_used == expected_squares_used);
    assert(bs.ws.empty());

    SolutionStep step_0_1 = bs.make_step(0, 1, first_step);
    expected_squares_used.insert({0, 1});

    assert(bs.could_lead_to_new_words(0, 1, first_step));

    assert(step_0_1.x == 0);
    assert(step_0_1.y == 1);
    assert(step_0_1.depth == 1);
    assert(step_0_1.v);
    assert(step_0_1.word_so_far == "ar");
    assert(step_0_1.squares_used == expected_squares_used);
    assert(bs.ws.empty());
}

int main() {
    test_is_not_on_board();
    test_make_first_step_0();
}