#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <algorithm>

#include "word.hpp"

using namespace std;

class FileReader {

  public:
    wchar_t* getFileBuffer(locale loc, string name);
    vector<wstring> getStopWords(locale loc);
    void fillHash(unordered_map <wstring, int> &hash, wchar_t * character, vector<wstring> &stopWords);
    int getFileNumber();
};

streampos getSize(wifstream &stream);

string getFileName(int x);
  
void printHeap(vector<Word> heap);

void updateHeap(pair<wstring,int> w, vector<Word> &heap);