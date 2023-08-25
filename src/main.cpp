#include <iostream>
#include <codecvt>
#include <locale>
#include <algorithm>
#include <vector>
#include <chrono>
#include <unordered_map>

#include "word.hpp"
#include "utils.hpp"

using namespace std;

int main() {
  // expecifica o locale a ser utilizado assim como a codificação do unicode
  setlocale(LC_ALL, "pt_BR.UTF-8");
  // inicializa o locale com o método de conversão utf-8
  locale loc(locale(), new codecvt_utf8<wchar_t>);
  // Número de elementos no heap
  const int k = 20;

  FileReader fr;
  vector<Word> heap;
  unordered_map <wstring, int> wordsHash; 

  auto startTime = chrono::high_resolution_clock::now();
  vector<wstring> stopWords = fr.getStopWords(loc);
  
  cout << "Os arquivos de input são nomeados na forma \"input{n}.data\", onde n é seu número a partir de 1" << endl;
  
  for(int i=1; i <= fr.getFileNumber();i++){
    // Lê o arquivo para a memória
    wchar_t* buffer = fr.getFileBuffer(loc, getFileName(i));

    fr.fillHash(wordsHash,buffer,stopWords);

    // Libera o arquivo da memória
    delete[] buffer;
  }

  for(std::pair< const wstring,int> &aux : wordsHash){
    // Adiciona palavras no heap até atingir o valor de k
    if(heap.size() < k){
      heap.push_back(Word(aux.first,aux.second));

      // Chama o heapfy somente quando atingir k
      if(heap.size() == k)
        make_heap(heap.begin(), heap.end());
    }
    else if(heap.size() == k){
      // Se a palavra na hash tem a frequencia maior que o ultimo do heap, realiza a troca
      if(aux.second > heap[0].getFrequence()){
        updateHeap(aux, heap);
      }
    }
  }

  printHeap(heap);
  
  auto finalTime = chrono::high_resolution_clock::now();
  // Calcula e printa o tempo gasto
  auto duration = chrono::duration_cast<chrono::milliseconds>(finalTime - startTime);
  wcout << duration.count() << " ms" << endl;
  
  return 0;
}