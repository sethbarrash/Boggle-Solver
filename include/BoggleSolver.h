#ifndef BOGGLESOLVER_H
#define BOGGLESOLVER_H

#include <cstring>
#include <queue>
#include <set>
#include <string>
#include "VocabTree.h"

using std::set;
using std::queue;
using std::string;

typedef set<string> word_set;

static char DEFAULT_VOCAB_FILE [100] = "boggleWords.txt";
static int XADJ [8] = {-1, -1, -1,  0,  0,  1,  1,  1};
static int YADJ [8] = {-1,  0,  1, -1,  1, -1,  0,  1};

struct SolutionStep {
    uint8_t x;
    uint8_t y;
    uint8_t depth;
    VocabNodePtr v;
    char word_so_far [MAX_ENGLISH_WORD_LENGTH];
    set<pair<uint8_t, uint8_t>> squares_used;
};

bool is_not_on_board(uint8_t x, uint8_t y);
bool square_already_used(uint8_t xnew, uint8_t ynew, SolutionStep step);

class BoggleSolver {
    public:
        BoggleSolver(char board [][4]);
        BoggleSolver(char board [][4], VocabTree t);
        void add_board(char (*board)[4]);
        void add_VocabTree(VocabTree t);
        word_set solve_board();
        word_set solve_board(char (*board)[4]);

    private:
        char board [4][4];
        VocabTree t;
        queue<SolutionStep> q;
        word_set ws;

        bool could_lead_to_new_words(uint8_t xnew, uint8_t ynew, SolutionStep step);
        SolutionStep make_first_step(uint8_t x, uint8_t y);
        SolutionStep make_step(uint8_t xnew, uint8_t ynew, SolutionStep step);
        void do_step(SolutionStep step);
        void gather_words_from_square(uint8_t x, uint8_t y);
};

#endif