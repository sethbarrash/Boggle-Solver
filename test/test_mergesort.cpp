#include <cassert>
#include <cstring>
#include "mergesort.h"

int main() {
  char new_york   [MAX_WORD_LENGTH] = "New York";
  char baltimore  [MAX_WORD_LENGTH] = "Baltimore";
  char chicago    [MAX_WORD_LENGTH] = "Chicago";
  char cleveland  [MAX_WORD_LENGTH] = "Cleveland";
  char washington [MAX_WORD_LENGTH] = "Washington";
  char detroit    [MAX_WORD_LENGTH] = "Detroit";

  char a [5][MAX_WORD_LENGTH] = {
    "Baltimore",
    "Chicago",
    "Cleveland",
    "New York",
    "Washington"
  };

  mergesort(a,5);

  assert(!strcmp(a[0], baltimore));
  assert(!strcmp(a[1], chicago));
  assert(!strcmp(a[2], cleveland));
  assert(!strcmp(a[3], new_york));
  assert(!strcmp(a[4], washington));
}