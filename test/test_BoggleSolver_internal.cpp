#include <cassert>
#include <iostream>
#include "BoggleSolver.h"
#include "test_BoggleSolver_fixtures.h"

using std::cout;

void test_is_not_on_board()
{
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

void test_initialize_simple_words()
{
    char can   [MAX_EXPECTED_WORD_LENGTH] = "can";
    char cans  [MAX_EXPECTED_WORD_LENGTH] = "cans";
    char cant  [MAX_EXPECTED_WORD_LENGTH] = "cant";
    char cart  [MAX_EXPECTED_WORD_LENGTH] = "cart";
    char carts [MAX_EXPECTED_WORD_LENGTH] = "carts";
    char cap   [MAX_EXPECTED_WORD_LENGTH] = "cap";
    char caps  [MAX_EXPECTED_WORD_LENGTH] = "caps";
    char carp  [MAX_EXPECTED_WORD_LENGTH] = "carp";
    char carps [MAX_EXPECTED_WORD_LENGTH] = "carps";
    char cot   [MAX_EXPECTED_WORD_LENGTH] = "cot";
    char cots  [MAX_EXPECTED_WORD_LENGTH] = "cots";
    char corp  [MAX_EXPECTED_WORD_LENGTH] = "corp";
    char corps [MAX_EXPECTED_WORD_LENGTH] = "corps";
    char cuts  [MAX_EXPECTED_WORD_LENGTH] = "cuts";
    char cut   [MAX_EXPECTED_WORD_LENGTH] = "cut";

    VocabTree t;
    t.add_word(can);
    t.add_word(cans);
    t.add_word(cant);
    t.add_word(cart);
    t.add_word(carts);
    t.add_word(cap);
    t.add_word(caps);
    t.add_word(carp);
    t.add_word(carps);
    t.add_word(cot);
    t.add_word(cots);
    t.add_word(corp);
    t.add_word(corps);
    t.add_word(cut);
    t.add_word(cuts);

    BoggleSolver bs(board0, &t);
}

void test_make_step()
{
    BoggleSolver bs(board0);
    assert(bs.ws.empty());
    assert(bs.q.empty());
    SolutionStep first_step = bs.make_first_step(0, 0);
    coord_set expected_squares_used;
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

    SolutionStep step_0_2 = bs.make_step(0, 2, step_0_1);
    coord_set expected_squares_0_2 = expected_squares_used;
    expected_squares_0_2.insert({0, 2});

    assert(bs.could_lead_to_new_words(0, 2, step_0_1));

    assert(step_0_2.x == 0);
    assert(step_0_2.y == 2);
    assert(step_0_2.depth == 2);
    assert(step_0_2.v);
    assert(step_0_2.word_so_far == "arg");
    assert(step_0_2.squares_used == expected_squares_0_2);
    assert(bs.ws.size() == 1);
    assert(bs.ws.count("arg") == 1);

    SolutionStep step_1_1 = bs.make_step(1, 1, step_0_1);
    coord_set expected_squares_1_1 = expected_squares_used;
    expected_squares_1_1.insert({1, 1});

    assert(bs.could_lead_to_new_words(1, 1, step_0_1));

    assert(step_1_1.x == 1);
    assert(step_1_1.y == 1);
    assert(step_1_1.depth == 2);
    assert(step_1_1.v);
    assert(step_1_1.word_so_far == "are");
    assert(step_1_1.squares_used == expected_squares_1_1);
    assert(bs.ws.size() == 2);
    assert(bs.ws.count("are") == 1);
}

void test_do_step()
{
    BoggleSolver bs(board0);
    assert(bs.ws.empty());
    assert(bs.q.empty());
    SolutionStep first_step = bs.make_first_step(0, 0);
    coord_set expected_squares_used;
    assert(expected_squares_used.empty());
    expected_squares_used.insert({0, 0});

    assert(first_step.x == 0);
    assert(first_step.y == 0);
    assert(first_step.depth == 0);
    assert(first_step.v);
    assert(first_step.word_so_far == "a");
    assert(first_step.squares_used == expected_squares_used);
    assert(bs.ws.empty());

    bs.do_step(first_step);
    assert(bs.q.size() == 3);
    assert(bs.ws.empty());

    SolutionStep step = bs.q.front();
    coord_set expected_squares_0_1 = expected_squares_used;
    expected_squares_0_1.insert({0, 1});

    assert(step.x == 0);
    assert(step.y == 1);
    assert(step.depth == 1);
    assert(step.v);
    assert(step.word_so_far == "ar");
    assert(step.squares_used == expected_squares_0_1);

    bs.q.pop();

    step = bs.q.front();
    coord_set expected_squares_1_0 = expected_squares_used;
    expected_squares_1_0.insert({1, 0});

    assert(step.x == 1);
    assert(step.y == 0);
    assert(step.depth == 1);
    assert(step.v);
    assert(step.word_so_far == "an");
    assert(step.squares_used == expected_squares_1_0);

    bs.q.pop();

    step = bs.q.front();
    coord_set expected_squares_1_1 = expected_squares_used;
    expected_squares_1_1.insert({1, 1});

    assert(step.x == 1);
    assert(step.y == 1);
    assert(step.depth == 1);
    assert(step.v);
    assert(step.word_so_far == "ae");
    assert(step.squares_used == expected_squares_1_1);
}

void test_gather_words_from_square()
{
    BoggleSolver bs(board0);
    assert(bs.ws.empty());
    assert(bs.q.empty());

    bs.gather_words_from_square(0, 0);
    assert(bs.ws.size() == 3);
    assert(bs.ws.count("and") == 1);
    assert(bs.ws.count("are") == 1);
    assert(bs.ws.count("arg") == 1);
    assert(bs.q.empty());
}

void test_quart()
{
    BoggleSolver bs(board4);
    SolutionStep first_step = bs.make_first_step(0, 0);
    coord_set expected_squares_used;
    assert(expected_squares_used.empty());
    expected_squares_used.insert({0, 0});

    assert(first_step.x == 0);
    assert(first_step.y == 0);
    assert(first_step.depth == 1);
    assert(first_step.v);
    assert(first_step.word_so_far == "qu");
    assert(first_step.squares_used == expected_squares_used);
    assert(bs.ws.empty());
}

int main() {
    test_is_not_on_board();
    test_initialize_simple_words();
    test_make_step();
    test_do_step();
    test_gather_words_from_square();
    test_quart();
}