#ifndef BOGGLESOLVER_H
#define BOGGLESOLVER_H

#include <cstring>
#include <queue>
#include <set>
#include <string>

using std::set;
using std::queue;

typedef set<string> word_set;

static char DEFAULT_VOCAB_FILE [100] = "boggleWords.txt";
static int XADJ [8] = {-1, -1, -1,  0,  0,  1,  1,  1};
static int YADJ [8] = {-1,  0,  1, -1,  1, -1,  0,  1};

struct SolutionStep {
    uint8_t x;
    uint8_t y;
    VocabNodePtr v;
    char word_so_far [MAX_ENGLISH_WORD_LENGTH];
    uint8_t depth;
    set<pair<uint8_t, uint8_t>> squares_used;
};

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

        SolutionStep make_first_step(uint8_t x, uint8_t y);
        SolutionStep make_step(uint8_t xnew, uint8_t ynew, SolutionStep step);
        void do_step(SolutionStep step);
        void gather_words_from_square(uint8_t x, uint8_t y);
};

#endif