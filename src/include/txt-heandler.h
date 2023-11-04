#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cctype>
#include "structure/doubly_linked_list.h"
#include "structure/avl_tree.h"

using namespace std;

// Função para remover pontuações do início e do final de uma palavra
string removePunctuation(string word)
{
    while (!word.empty() && ispunct(word.front()))
    {
        word = word.substr(1);
    }

    while (!word.empty() && ispunct(word.back()))
    {
        word.pop_back();
    }

    return word;
}

void openTxt()
{
    string directoryPath = filesystem::current_path().string() + "/data"; // Obter o caminho atual e adicionar "/data"

    if (!filesystem::exists(directoryPath))
    {
        cout << "O diretório não foi encontrado" << endl;
        return;
    }

    DoublyLinkedList<string> files;

    for (const auto &entry : filesystem::directory_iterator(directoryPath))
        if (entry.is_regular_file())
            files.pushBack(entry.path().filename().stem().string());

    if (files.size() == 0)
    {
        cout << "Não há arquivos para realizar a leitura!" << endl;
        return;
    }

    int selection; // Variável para armazenar a seleção do usuário
    do
    {
        cout << "\nEscolha um arquivo:" << endl;

        for (int i = 0; i < files.size(); i++)
            cout << "[" << i + 1 << "] " << files.getValue(i) << "  ";

        cout << "\n> ";
        cin >> selection;
    } while (selection < 1 || selection > files.size());

    string fileName = directoryPath + "/" + files.getValue(selection - 1) + ".txt"; // Construir o nome do arquivo a ser aberto

    ifstream file(fileName); // Abrir o arquivo

    if (!file.is_open())
    {
        cerr << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    AVLTree<string> tree;

    string line;        // Variável para armazenar cada linha do arquivo
    int lineNumber = 1; // Contador para o número da linha

    // Ler o arquivo linha por linha
    while (getline(file, line))
    {
        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            word = removePunctuation(word);
            if (word.size() > 3)
                tree.insert(word);
        }
        lineNumber++;
    }

    file.close();

    tree.printTree();
}
