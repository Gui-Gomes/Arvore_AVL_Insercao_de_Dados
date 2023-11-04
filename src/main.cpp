#include <iostream>
#include <string>
#include "include/structure/avl_tree.h"
#include "include/ordenation/quick_sort.h"
#include "include/txt-heandler.h"
#include <cstdlib>

#ifdef _WIN32
void clearScreen()
{
    std::system("cls");
}
#else
void clearScreen()
{
    std::system("clear");
}
#endif

using namespace std;

class StringQuickSort : public QuickSort<filesInfo>
{
public:
    int compare(filesInfo word1, filesInfo word2) override
    {
        return word1.fileName.compare(word2.fileName);
    }
};

void printLine(int line)
{
    cout << line << " ";
}

void printFilesNames(filesInfo file)
{
    cout << file.fileName << endl;
    cout << endl;
}

void printLineList(filesInfo file)
{
    file.lines->printList(printLine);
}

int main()
{
    AVLTree<string> words;
    int choice;

    while (true)
    {
        clearScreen(); // Limpa a tela no início de cada iteração

        cout << "MENU:\n";
        cout << "1. LEITURA DE ARQUIVOS:\n";
        cout << "2. IMPRIMIR ÁRVORE: \n";
        cout << "3. VERIFICAR SE DETERMINADA PALAVRA EXISTE NA ÁRVORE:\n";
        cout << "4. VERIFICAR EM QUAIS LINHAS DETERMINADA PALAVRA SE ENCONTRA:\n";
        cout << "5. DELETAR DETERMINADA PALAVRA DA ÁRVORE:\n";
        cout << "6. VERIFICAR A QUANTIDADE DE PALAVRAS DISTINTAS PRESENTE NA ÁRVORE:\n";
        cout << "7. VERIFICAR ALTURA DA ÁRVORE:\n";
        cout << "8. SAIR\n\n";
        cout << "ESCOLHA UMA OPÇÃO: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            openTxt(words);
            cout << "DOCUMENTO CARREGADO COM SUCESSO!" << endl;
            break;
        case 2:
            cout << "ÁRVORE DE PALAVRAS:" << endl;
            words.printTree();
            break;
        case 3:
        {
            string word;
            cout << "DIGITE UMA PALAVRA:\n> ";
            cin >> word;

            for (char &c : word)
            {
                c = toupper(c);
            }

            if (words.contains(word))
            {
                cout << word << " EXISTE NA ÁRVORE" << endl;
            }
            else
            {
                cout << word << " NÃO EXISTE NA ÁRVORE" << endl;
            }
            break;
        }
        case 4:
        {
            string word;
            cout << "DIGITE UMA PALAVRA:\n> ";
            cin >> word;

            for (char &c : word)
            {
                c = toupper(c);
            }

            StringQuickSort quicksort = StringQuickSort();
            quicksort.sort(*(words.find(word)->files));

            int selection;
            do
            {
                cout << "\nEscolha um arquivo:" << endl;

                for (int i = 0; i < words.find(word)->files->size(); i++)
                {
                    cout << "[" << i + 1 << "] " << words.find(word)->files->getValue(i).fileName << "  ";
                }
                cout << "\n> ";
                cin >> selection;
            } while (selection < 1 || selection > words.find(word)->files->size());

            words.find(word)->files->printOneNode(printLineList, selection - 1);
            break;
        }
        case 5:
        {
            string word;
            cout << "DIGITE UMA PALAVRA:\n> ";
            cin >> word;

            for (char &c : word)
            {
                c = toupper(c);
            }

            if (words.contains(word))
            {
                words.remove(word);
                cout << "PALAVRA DELETADA COM SUCESSO." << endl;
            }
            else
            {
                cout << "PALAVRA NÃO ENCONTRADA..." << endl;
            }
            break;
        }
        case 6:
            cout << "QUANTIDADE DE PALAVRAS DISTINTAS: " << words.countDistinct() << endl;
            break;
        case 7:
            cout << "ALTURA DA ÁRVORE: " << words.getHeight() << endl;
            break;
        case 8:
            return 0;
        default:
            cout << "Opção inválida. Tente novamente." << endl;
            break;
        }

        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get(); // Pausa até que o usuário pressione Enter
    }

    return 0;
}
