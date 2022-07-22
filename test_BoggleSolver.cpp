#include "BoggleSolver.h"

int main() {
    char board0[4][4] = {{'a', 'r', 'g', 't'}, {'n', 'e', 'v', 'r'}, {'d', 'f', 'b', 'a'}, {'t', 'w', 'e', 'n'}};
    char input_file [100] = "boggleWords.txt";
    WordTree t = WordTree(input_file);
    BoggleSolver bs = BoggleSolver(board0,t);
    BoggleTree bt = bs.buildBoggleTree(0,0);
}