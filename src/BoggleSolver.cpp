#include "BoggleSolver.h"
#include "VocabTree.h"

BoggleSolver::BoggleSolver(char input_board [][4]) {
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            board[i][j] = input_board[i][j];
    t = VocabTree(DEFAULT_VOCAB_FILE);
}

BoggleSolver::BoggleSolver(char input_board [][4], VocabTree wt) {
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            board[i][j] = input_board[i][j];
    t = wt;
}

void BoggleSolver::add_board(char (*input_board)[4]) {
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            board[i][j] = input_board[i][j];
}

void BoggleSolver::add_VocabTree(VocabTree wt) {
    t = wt;
}

SolutionStep BoggleSolver::make_step(uint8_t xnew, uint8_t ynew, SolutionStep step) {
    char letter = board[xnew][ynew];
    uint8_t new_depth = step.depth + 1;
    VocabNodePtr new_vocab_node_ptr = step.v->children[letter-ascii_a];
    set<pair<uint8_t, uint8_t>> new_squares_used = step.squares_used;
    new_squares_used.insert({xnew, ynew});

    SolutionStep new_step = {
        xnew,
        ynew,
        new_depth,
        new_vocab_node_ptr,
        step.word_so_far,
        new_squares_used,
    };
    new_step.word_so_far.push_back(letter);

    if (new_vocab_node_ptr->is_end_of_word)
        ws.insert(new_step.word_so_far);
    
    return new_step;
}

bool is_not_on_board(uint8_t x, uint8_t y) {
    if (x < 0) return true;
    if (y < 0) return true;
    if (x > 3) return true;
    if (y > 3) return true;
    return false;
}

bool square_already_used(uint8_t xnew, uint8_t ynew, SolutionStep step) {
    bool already_used = step.squares_used.count({xnew, ynew}) > 0;
    return already_used;
}

bool BoggleSolver::could_lead_to_new_words(uint8_t xnew, uint8_t ynew, SolutionStep step) {
    if (is_not_on_board(xnew, ynew)) return false;
    if (square_already_used(xnew, ynew, step)) return false;

    char letter = board[xnew][ynew];
    if (step.v->children[letter-ascii_a]) return true;
    else return false;
}

void BoggleSolver::do_step(SolutionStep step) {
    uint8_t i, j, xnew, ynew;
    for (uint8_t k=0; k<8; k++) {
        i = XADJ[k];
        j = YADJ[k];
        xnew = step.x + i;
        ynew = step.y + j;

        if (could_lead_to_new_words(xnew, ynew, step))
        {
            SolutionStep next_step = make_step(xnew, ynew, step);
            q.push(next_step);
        }
    }
}

SolutionStep BoggleSolver::make_first_step(uint8_t x, uint8_t y) {
    char letter = board[x][y];
    VocabNodePtr vocab_node_ptr = t.root->children[letter - ascii_a];
    set<pair<uint8_t, uint8_t>> squares_used;
    squares_used.insert({x, y});
    SolutionStep first_step = {x, y, 0, vocab_node_ptr, string(t.max_word_length, 0), squares_used};
    first_step.word_so_far[0] = letter;
    first_step.word_so_far.resize(1);
    return first_step;
}

void BoggleSolver::gather_words_from_square(uint8_t x, uint8_t y) {
    SolutionStep first_step = make_first_step(x, y);
    SolutionStep next_step;

    q.push(first_step);
    while (!q.empty())
    {
        next_step = q.front();
        q.pop();
        do_step(next_step);
    }
}

word_set BoggleSolver::solve_board() {
    for (int x=0; x<4; x++)
        for (int y=0; y<4; y++)
            gather_words_from_square(x, y);
    return ws;
}

word_set BoggleSolver::solve_board(char (*board)[4]) {
    add_board(board);
    word_set ws = solve_board();
    return ws;
}