#include "utils.hpp"

using namespace std;

streampos getSize(wifstream &stream){
  // Obtém o tamanho do arquivo
  stream.seekg(0, ios::end);

  streampos size = stream.tellg();
      
  stream.seekg(0, ios::beg);

  return size;
}

void printHeap(vector<Word> heap){
  // Cria um convertor de wstring baseado na codificação utf-8
  wstring_convert<std::codecvt_utf8<wchar_t>> converter;

  cout << "\n-------- Heap final: --------" << endl;
  
  // Percorre o heap e printa os valores
  for (long unsigned int i = 0; i < heap.size(); i++){
    cout << to_string(i) +": " <<
    converter.to_bytes(heap[i].getContent()) <<" -> " << 
    heap[i].getFrequence() << endl;
  }
}

void updateHeap(pair<wstring,int> w, vector<Word> &heap){
  pop_heap(heap.begin(), heap.end());

  // Remove ultimo membro do vetor
  heap.pop_back();
  // Adiciona a palavra com a maior frequência
  heap.push_back(Word(w.first, w.second));

  // Faz o heap novamente
  push_heap(heap.begin(), heap.end());
}

string getFileName(int x){
  return "./dataset/input" + to_string(x) + ".data";
}

int FileReader::getFileNumber(){

  int i = 0;
  while(1){
    
    wifstream stream(getFileName(i+1), ios::binary);

    if(stream.is_open()){
      i++;
    }
    else{
      return i;
    }
  }
}

void FileReader::fillHash(unordered_map <wstring, int> &hash, wchar_t * character, vector<wstring> &stopWords){
  
  wstring word;
  while(*character){
    
    switch(*character){
      // Caso se encontre um caracter de terminação
      case L' ': case L'!': case L'?': case L'.': case L'\n': 
      case L',': case L'(': case L')': case L';': case L'/': 
      case L':': case L'—': case L'"': case L'\'':

        if(!word.empty()){
          // Aplica a função tolower em cada caracter da palavra usando uma lambda function
          transform(word.begin(), word.end(), word.begin(),
            [](wchar_t c){ return std::tolower(c); });

          // Se a palavra não é stopword, soma na frequência
          if(find(stopWords.begin(),stopWords.end(),word) == stopWords.end()){
            hash[word]++;
          }

          word.clear();
        }
        break;

      default:
        // Não adiciona somente o '-' como palavra, mas deixa palavras compostas como abaixo-assinado
        if(*character == '-' && word.size() == 0){
          break;
        }
        // Adiciona caracteres na palavra
        word += *character;
        break;
    }

    // Progride no buffer
    character++;
  }
}

wchar_t* FileReader::getFileBuffer(locale loc, string name){
  
  wifstream stream(name, ios::binary);

  if(!stream.is_open()){
    cerr << "Não foi possível ler o arquivo" << endl;
    exit(1);
  }

  // Seta o locale português UTF-8 para o arquivo
  stream.imbue(loc);

  streampos size = getSize(stream);

  // Cria um buffer do tamanho do arquivo
  wchar_t* buffer = new wchar_t[size];
  
  // Joga todo o arquivo para o buffer
  stream.read(buffer,size);

  stream.close();

  return buffer;
}

vector<wstring> FileReader::getStopWords(locale loc){
  vector<wstring> stopwords;
  
  wifstream stream("dataset/stopwords.txt");

  if(!stream.is_open()){
    cerr << "Não foi possível abrir o arquivo!" << endl;
    exit(1);
  }

  stream.imbue(loc);

  // Consome todas as palavras e as colocas no vetor
  wstring word;
  while (stream >> word){
    stopwords.push_back(word);
  }
  stream.close();

  return stopwords;
}
