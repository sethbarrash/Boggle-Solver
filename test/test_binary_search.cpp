#include <cassert>
#include "binary_search.h"

int main() {
  char genesis     [MAX_WORD_LENGTH] = "genesis";
  char exodus      [MAX_WORD_LENGTH] = "exodus";
  char leviticus   [MAX_WORD_LENGTH] = "leviticus";
  char numbers     [MAX_WORD_LENGTH] = "numbers";
  char deuteronomy [MAX_WORD_LENGTH] = "deuteronomy";
  char joshua      [MAX_WORD_LENGTH] = "joshua";

  char a [5][MAX_WORD_LENGTH] = {
    "deuteronomy",
    "exodus",
    "genesis",
    "leviticus",
    "numbers"
  };

  assert(binary_search(a,joshua,5)      == -1);
  assert(binary_search(a,deuteronomy,5) == 0);
  assert(binary_search(a,exodus,5)      == 1);
  assert(binary_search(a,genesis,5)     == 2);
  assert(binary_search(a,leviticus,5)   == 3);
  assert(binary_search(a,numbers,5)     == 4);
}