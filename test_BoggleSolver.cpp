#include "BoggleSolver.h"

int main() {
    char board0[4][4] = {{'a', 'r', 'g', 't'}, {'n', 'e', 'v', 'r'}, {'d', 'f', 'b', 'a'}, {'t', 'w', 'e', 'n'}};
    char inputFile [20] = "boggleWords.txt";
    WordTree t = WordTree(inputFile);
    BoggleSolver bt = BoggleSolver(board0,t);
}