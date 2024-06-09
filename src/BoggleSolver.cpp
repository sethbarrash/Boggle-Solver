#include "BoggleSolver.h"
#include "VocabTree.h"

void harvest_node(BoggleNodePtr bn, word_set& ws, int depth) {
    // Gather words from subtree pointed to by bn and put them into the list ws
    bn->word_so_far[depth] = bn->letter;
    if (bn->is_end_of_word) {
        string word_copy = bn->word_so_far;
        ws.insert(word_copy);
    }
    for (int k=0; k<8; k++) {
        BoggleNodePtr bk = bn->children[k];
        if (bk) {
            strcpy(bk->word_so_far,bn->word_so_far);
            harvest_node(bk, ws, depth+1);
        }
    }
}

void harvest(BoggleTree& bt, word_set& ws) {
    harvest_node(bt.root,ws,0);
}

word_set harvest(BoggleTree& bt) {
    word_set ws;
    BoggleNodePtr bn = bt.root;
    harvest_node(bn, ws, 0);

    return ws;
}

void add_children_to_queue(BoggleNodePtr bn, queue<BoggleNodePtr>& q) {
    for (int k=0; k<8; k++) if (bn->children[k]) q.push(bn->children[k]);
}

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

BoggleNodePtr BoggleSolver::create_child(BoggleNodePtr b, int x, int y, char l) {
    BoggleNodePtr child = new_BoggleNode();
    child->letter = l;
    child->x = x;
    child->y = y;
    child->parent = b;
    child->vnode = b->vnode->children[l-ascii_a];
    child->is_end_of_word = child->vnode->is_end_of_word;
    return child;
}

void BoggleSolver::populateChildren(BoggleNodePtr b) {
    int i, j, xnew, ynew;
    char lnew;

    for (int k=0; k<8; k++) {
        i = XADJ[k];
        j = YADJ[k];
        xnew = b->x+i;
        ynew = b->y+j;
        if (xnew >= 0 && ynew >= 0 && xnew < 4 && ynew < 4 && !is_ancestor(b,xnew,ynew)) {
            lnew = board[xnew][ynew];
            if (b->vnode->children[lnew-ascii_a])
                b->children[k] = create_child(b,xnew,ynew,lnew);
        }
    }
}

void BoggleSolver::initialize_BoggleTree(BoggleTree& bt, int x, int y) {
    bt.root = new_BoggleNode();
    bt.root->letter = board[x][y];
    bt.root->x = x;
    bt.root->y = y;
    int letter_idx = bt.root->letter-ascii_a;
    bt.root->vnode = t.root->children[letter_idx];
}

void BoggleSolver::build_BoggleTree(BoggleTree& bt) {
    BoggleNodePtr b = bt.root;

    queue<BoggleNodePtr> q;
    populateChildren(b);
    add_children_to_queue(b,q);
    while (!q.empty()) {
        b = q.front();
        q.pop();
        populateChildren(b);
        add_children_to_queue(b,q);
    }
}

void BoggleSolver::do_step(SolutionStep step) {
    uint8_t i, j, xnew, ynew;
    char lnew;

    for (int k=0; k<8; k++) {
        i = XADJ[k];
        j = YADJ[k];
        xnew = step.x + i;
        ynew = step.y + j;
        bool used_before = step.squares_used.count({xnew, ynew}) == 0;
        if (xnew >= 0 && ynew >= 0 && xnew < 4 && ynew < 4 && !used_before)
        {
            lnew = board[xnew][ynew];
            VocabNodePtr new_vocab_node_ptr = step.v->children[lnew-ascii_a];
            if (new_vocab_node_ptr)
            {
                uint8_t new_depth = step.depth + 1;
                set<pair<uint8_t, uint8_t>> new_squares_used = step.squares_used;
                new_squares_used.insert({step.x, step.y});

                SolutionStep new_step = {
                    xnew,
                    ynew,
                    new_vocab_node_ptr,
                    {0},
                    new_depth,
                    new_squares_used,
                };
                strcpy(new_step.word_so_far, step.word_so_far);
                step.word_so_far[new_depth] = lnew;

                if (new_vocab_node_ptr->is_end_of_word)
                    // TODO: Convert word_so_far to a string
                    ws.insert(new_step.word_so_far);
                
                q.push(new_step);
            }
        }
    }
}

void BoggleSolver::gather_words_from_square(uint8_t x, uint8_t y) {
    char letter = board[x][y];
    VocabNodePtr vocab_node_ptr = t.root->children[letter - ascii_a];
    set<pair<uint8_t, uint8_t>> squares_used;
    squares_used.insert({x, y});
    SolutionStep first_step = {x, y, vocab_node_ptr, {0}, 0, squares_used};
    first_step.word_so_far[0] = letter;

    q.push(first_step);
    SolutionStep next_step;
    while (!q.empty())
    {
        next_step = q.front();
        q.pop();
        do_step(next_step);
    }
}

void BoggleSolver::build_BoggleTree(BoggleTree& bt, int x, int y) {
    initialize_BoggleTree(bt, x, y);
    build_BoggleTree(bt);
}

word_set BoggleSolver::solve_board() {
    BoggleTree* bt;
    add_board(board);

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