#include<iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T>* right;
    Node<T>* left;
    int heigth;
};

template<typename T>
int max(T a, T b) {
    if(a > b)
        return a;
    return b;
}

template<typename T>
class Tree {
private:
    Node<T>* root;
public:
    Tree() {
        root = NULL;
        root->heigth = -1;
    }

    int height(Node<T>* root) { /*retorna a altura do nó*/
        if(root == NULL) {
            return -1;
        }
        return (root->heigth);
    }

    Node<T>* rotationRight(Node<T>* root) { /*rotação simples para direita*/
        Node<T>* aux;
        aux = root->left;
        root->left = aux->left;
        aux->right = root;

        root->heigth = max(height(root->right), height(root->left)) + 1;
        return aux;
    }

    Node<T>* rotationLeft(Node<T>* root) { /*rotação simples para esquerda*/
        Node<T>* aux;
        aux = root->right;
        root->right = aux->right;
        aux->left = root;

        root->heigth = max(height(root->right), height(root->left)) + 1;
        return aux;
    }

    Node<T>* rotationLeftRight(Node<T>* root) { /*rotação dupla para esquerda/direita*/
        root->left = rotationLeft(root->left);
        return rotationRight(root);
    }

    Node<T>* rotationRigthLeft(Node<T>* root) { /*rotação dupla apara direita/esquerda*/
        root->right = rotationRight(root->right);
        return rotationLeft(root);
    }

    Node<T>* insert(Node<T> root, T data) { /*inserção*/
        if(root == NULL) {
            Node<T>* newNode = new(Node<T>);
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->heigth = max(height(newNode->left), height(newNode->right)) + 1;
            return newNode;
        }
        if(data < root->data) { /*se a chave for menor que da raiz (tenta iserir a esquerda conforme uma ávore binária)*/
            root->left = insert(root->left, data);
            if( (height(root->left)) - height(root->right == 2) ) {
                if(data < root->left->data) {
                    root = rotationRight(root);
                } else {
                    root = rotationLeftRight(root);
                }
            }
        } else {
            if(data > root->data) {
                root->right = insert(root->right, data);
                if( (height(root->right) - height(root->left) == 2) ) {
                    if(data > root->right->data) {
                        root = rotationLeft(root);
                    } else {
                        root = rotationRigthLeft(root);
                    }
                }
            }
        } 
    }

};