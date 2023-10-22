#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "structure/doubly_linked_list.h"

using namespace std;

struct wordsStruct {
    string palavra;
    int count = 0;
};


DoublyLinkedList<string> files;
DoublyLinkedList<wordsStruct> words;


wordsStruct createWordsStruct(string palavra) {
    wordsStruct w;
    w.palavra = palavra;

    return w;
}

// Função para remover pontuações do início e do final de uma palavra
string removePunctuation(string word) {
    while (!word.empty() && ispunct(word.front())) {
        word = word.substr(1);
    }
    
    while (!word.empty() && ispunct(word.back())) {
        word.pop_back();
    }
    
    return word;
}

string toLower(string str) {
  
    transform(str.begin(), str.end(), str.begin(), ::toupper); 
    return str;
}

void addFilesName(string directoryPath) {
    
    if (!filesystem::exists(directoryPath)) {
        cout << "O diretório não foi encontrado :(" << endl;
        return;
    }

    for (auto entry : filesystem::directory_iterator(directoryPath))
        if (entry.is_regular_file())
            files.pushBack(entry.path().filename().stem().string());

    if (files.getSize() == 0) {
        cout << "Não há arquivos para realizar a leitura!" << endl;
        return;
    }
}

int chooseBook() {
    int selection;  // Variável para armazenar a seleção do usuário
    do {
        cout << "\nEscolha um arquivo:" << endl;

        for (int i = 0; i < files.getSize(); i++)
            cout << "[" << i + 1 << "] " << files.getValue(i) << "  ";

        cout << "\n> ";
        cin >> selection;
    } while (selection < 1 || selection > files.getSize());
    return selection;
}


void printString(wordsStruct str) {
    cout << str.palavra << "\n";
}

int compareWords(wordsStruct p1, wordsStruct p2) { 
    string p1String = p1.palavra;
    string p2String = p2.palavra;


    transform(p1String.begin(), p1String.end(), p1String.begin(), ::toupper); 
    transform(p2String.begin(), p2String.end(), p2String.begin(), ::toupper); 
  
     return p1String.compare(p2String); 
 }

void openTxt() {
    string directoryPath = filesystem::current_path().string() + "/data";  // Obter o caminho atual e adicionar "/data"
    addFilesName(directoryPath);
    
    int selection = chooseBook();

    string fileName = directoryPath + "/" + files.getValue(selection - 1) + ".txt";  // Construir o nome do arquivo a ser aberto

    ifstream file(fileName);  // Abrir o arquivo

    if (!file.is_open()) {
        cerr << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    string line;  // Variável para armazenar cada linha do arquivo
    int lineNumber = 1;  // Contador para o número da linha
    
    // Ler o arquivo linha por linha
    while (getline(file, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            word = toLower(removePunctuation(word));
            if (words.getSize() == 0) {
                wordsStruct wordStr = createWordsStruct(word);
                if (wordStr.palavra.size() > 3)
                    words.pushBack(wordStr);
            } else {
                bool search = false;
                wordsStruct wordStr = createWordsStruct(word);
                wordsStruct temp = words.binarySearch(wordStr, 0, words.getSize() - 1, compareWords, search);
                if (!search && wordStr.palavra.size() > 3) {
                    words.pushBack(wordStr);
                } 
            }
        }
        lineNumber++;
    }

    words.display(printString);
    file.close();
}
