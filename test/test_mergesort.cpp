#include <cassert>
#include <cstring>
#include <iostream>
#include "mergesort.h"

void print_words(char (*a)[MAX_WORD_LENGTH], int length) {
  for (int i=0; i<length; i++) {
    cout << a[i] << '\n';
  }
}

int main() {
  char genesis     [MAX_WORD_LENGTH] = "genesis";
  char exodus      [MAX_WORD_LENGTH] = "exodus";
  char leviticus   [MAX_WORD_LENGTH] = "leviticus";
  char numbers     [MAX_WORD_LENGTH] = "numbers";
  char deuteronomy [MAX_WORD_LENGTH] = "deuteronomy";

  char a [5][MAX_WORD_LENGTH] = {
    "genesis",
    "exodus",
    "leviticus",
    "numbers",
    "deuteronomy"
  };

  mergesort(a,5);
  print_words(a,5);

  assert(!strcmp(a[0],deuteronomy));
  assert(!strcmp(a[1],exodus));
  assert(!strcmp(a[2],genesis));
  assert(!strcmp(a[3],leviticus));
  assert(!strcmp(a[4],numbers));
}