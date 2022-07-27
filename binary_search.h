#include <cstring>
#include "BoggleTree.h"

int binary_search(char a[][MAX_WORD_LENGTH], char target[MAX_WORD_LENGTH], int left, int right) {
  if (right < left) return -1;

  int center = (right+left)/2;
  int comp = strcmp(a[center],target);
  if (comp > 0) return binary_search(a,target,left,center-1);
  if (comp < 0) return binary_search(a,target,center+1,right);
  return center;
}

int binary_search(char a[][MAX_WORD_LENGTH], char target[MAX_WORD_LENGTH], int length) {
  return binary_search(a,target,0,length-1);
}