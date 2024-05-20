#include <cassert>
#include <iostream>
#include <cstring>
#include "binary_search.h"
#include "BoggleTree.h"

using std::cout;

int main() {
  char new_york   [MAX_WORD_LENGTH] = "New York";
  char baltimore  [MAX_WORD_LENGTH] = "Baltimore";
  char chicago    [MAX_WORD_LENGTH] = "Chicago";
  char cleveland  [MAX_WORD_LENGTH] = "Cleveland";
  char washington [MAX_WORD_LENGTH] = "Washington";
  char detroit    [MAX_WORD_LENGTH] = "Detroit";

  char a [5][MAX_WORD_LENGTH] = {
    "New York",
    "Baltimore",
    "Chicago",
    "Cleveland",
    "Washington"
  };

  assert(binary_search(a, detroit, 5)    == -1);
  assert(binary_search(a, new_york, 5)   == -1);
  assert(binary_search(a, chicago, 5)    == 2);
  assert(binary_search(a, cleveland, 5)  == 3);
  assert(binary_search(a, washington, 5) == 4);
  assert(binary_search(a, baltimore, 5)  == -1);
}