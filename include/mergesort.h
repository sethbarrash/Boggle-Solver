#include <cstring>

const int MAX_WORD_LENGTH = 100;

void merge(char a[][MAX_WORD_LENGTH], int left, int center, int right) {
  if (center <= left || right <= center) return;

  int length = right-left;
  char temp [length][MAX_WORD_LENGTH];
  int leftPos = left;
  int rightPos = center;
  int tempPos = 0;

  
  while (leftPos < center && rightPos < right) {
    char* aleft = a[leftPos];
    char* aright = a[rightPos];
    if (strcmp(a[leftPos],a[rightPos])<=0) strcpy(temp[tempPos++],a[leftPos++]);
    else strcpy(temp[tempPos++],a[rightPos++]);
  }
  while (leftPos < center) strcpy(temp[tempPos++],a[leftPos++]);
  while (rightPos < right) strcpy(temp[tempPos++],a[rightPos++]);

  for (int i=0; i<length; i++) strcpy(a[left+i],temp[i]);
}

void mergesort(char a[][MAX_WORD_LENGTH], int left, int right) {
  if (right <= left+1) return;

  int center = (left+right)/2;

  char* a1 = a[1];
  char* a2 = a[2];
  char* a3 = a[3];
  char* a4 = a[4];

  mergesort(a,left,center);
  mergesort(a,center,right);
  merge(a,left,center,right);
}

void mergesort(char a[][MAX_WORD_LENGTH], int length) {
  mergesort(a,0,length);
}
