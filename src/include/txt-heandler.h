#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "structure/doubly_linked_list.h"

using namespace std;

// Função que verifica se um caractere é um sinal de pontuação
bool isPunctuation(char c) {
    return ispunct(static_cast<unsigned char>(c));
}

// Função que lê e processa um arquivo de texto
template <typename T>
void openTxt(void (*printFunction)(T)) {
    string directoryPath = filesystem::current_path().string() + "/data";

    if (!filesystem::exists(directoryPath)) {
        cout << "O diretório não foi encontrado." << endl;  // Exibe uma mensagem de erro se o diretório não existir
        return;
    }

    DoublyLinkedList<string> files;
    int fileCount = 0;

    // Itera sobre os arquivos no diretório
    for (const auto &entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            files.pushBack(entry.path().filename().stem().string());  // Adiciona o nome do arquivo à lista
            fileCount++;
        }
    }

    if (fileCount == 0) {
        cout << "Não há arquivos para realizar a leitura!" << endl;
        return;
    }

    cout << "\nESCOLHA O ARQUIVO A SER INSERIDO NA ÁRVORE:" << endl;

    // Apresenta os nomes dos arquivos disponíveis para leitura
    for (int i = 0; i < files.size(); i++) {
        cout << "[" << i + 1 << "]" << files.getValue(i) << " ";
    }

    cout << "\n> ";

    int selection;
    cin >> selection;
    string fileName = directoryPath + '/' + files.getValue(selection - 1) + ".txt";  // Obtém o nome do arquivo selecionado

    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    string word;

    while (file >> word) {
        string cleanedWord = "";

        for (size_t i = 0; i < word.length(); ++i) {
            char c = word[i];

            if (i == 0 || i == word.length() - 1) {
                if (!isPunctuation(c)) {
                    cleanedWord += c;
                }
            } else {
                cleanedWord += c;
            }
        }

        if (cleanedWord.size() > 3) {
            cout << cleanedWord << endl << endl;
        }
    }

    file.close();
}
