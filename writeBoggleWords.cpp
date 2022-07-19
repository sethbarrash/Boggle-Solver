#include <fstream>
#include <iostream>

using namespace std;

char inFile  [100] = "englishWords.txt";
char outFile [100] = "boggleWords.txt";

int MAX_WORD_LENGTH = 100;

int main() {
    ifstream in_stream;
    ofstream out_stream;
    in_stream.open(inFile);
    out_stream.open(outFile);

    char word [MAX_WORD_LENGTH];
    int i = 0;
    char x;

    while (!in_stream.eof()) {
        do {
            in_stream.get(x);
            word[i++] = x;
        } while (x != '\n');
        if (i >= 4) {
            word[i] = 0;
            out_stream << word;
        }
        i = 0;
    }
    
    in_stream.close();
    out_stream.close();
}