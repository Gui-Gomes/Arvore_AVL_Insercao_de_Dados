#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;
    int count; // Contador de duplicatas

    AVLNode(const T& value) : data(value), left(nullptr), right(nullptr), height(1), count(1) {}
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int getHeight(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode<T>* node) {
        if (node == nullptr)
            return;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;
        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;
        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode<T>* insert(AVLNode<T>* node, const T& value) {
        if (node == nullptr)
            return new AVLNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            node->count++;
            return node;
        }

        updateHeight(node);

        int balance = getBalanceFactor(node);

        if (balance > 1) {
            if (value < node->left->data) {
                return rotateRight(node);
            } else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (balance < -1) {
            if (value > node->right->data) {
                return rotateLeft(node);
            } else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    AVLNode<T>* findMinValueNode(AVLNode<T>* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    AVLNode<T>* remove(AVLNode<T>* node, const T& value) {
        if (node == nullptr)
            return node;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                AVLNode<T>* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLNode<T>* temp = findMinValueNode(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }

            if (node == nullptr)
                return node;

            updateHeight(node);
            int balance = getBalanceFactor(node);

            if (balance > 1) {
                if (getBalanceFactor(node->left) >= 0)
                    return rotateRight(node);
                else {
                    node->left = rotateLeft(node->left);
                    return rotateRight(node);
                }
            }

            if (balance < -1) {
                if (getBalanceFactor(node->right) <= 0)
                    return rotateLeft(node);
                else {
                    node->right = rotateRight(node->right);
                    return rotateLeft(node);
                }
            }
        }

        return node;
    }

    void destroyTree(AVLNode<T>* node) {
        if (node == nullptr)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void printAVLTree(AVLNode<T>* node, const string& prefix = "", bool isLeft = true) {
        if (node != nullptr) {
            cout << prefix;
            cout << (isLeft ? "├── " : "└── ");
            cout << node->data << " (Count: " << node->count << ")" << endl;

            string childPrefix = prefix + (isLeft ? "│   " : "    ");

            bool hasLeft = node->left != nullptr;
            bool hasRight = node->right != nullptr;

            if (hasLeft || hasRight) {
                if (hasLeft) {
                    printAVLTree(node->left, childPrefix, true);
                }
                if (hasRight) {
                    printAVLTree(node->right, childPrefix, false);
                }
            }
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroyTree(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    void remove(const T& value) {
        root = remove(root, value);
    }

    void printTree() {
        if (root == nullptr) {
            cout << "A árvore está vazia." << endl;
        } else {
            cout << "Árvore AVL:" << endl;
            printAVLTree(root);
        }
    }

    // Método para buscar um valor na árvore
    AVLNode<T>* find(const T& value) {
        return find(root, value);
    }

    // Método para verificar se um valor está na árvore
    bool contains(const T& value) {
        return contains(root, value);
    }

    // Método para contar elementos distintos na árvore
    int countDistinct() {
        return countDistinct(root);
    }

    // Método para obter a altura da árvore
    int getHeight() {
        return getHeight(root);
    }

    // Método para esvaziar completamente a árvore
    void clear() {
        destroyTree(root);
        root = nullptr;
    }

    // Método para verificar se a árvore está vazia
    bool isEmpty() {
        return root == nullptr;
    }

    // Imprime a árvore AVL em ordem (inorder)
    void printInOrder() {
        cout << "Árvore AVL em ordem (inorder):" << endl;
        printInOrder(root);
    }

    // Imprime a árvore AVL em pré-ordem (preorder)
    void printPreOrder() {
        cout << "Árvore AVL em pré-ordem (preorder):" << endl;
        printPreOrder(root);
    }

    // Imprime a árvore AVL em pós-ordem (postorder)
    void printPostOrder() {
        cout << "Árvore AVL em pós-ordem (postorder):" << endl;
        printPostOrder(root);
    }

private:
    AVLNode<T>* find(AVLNode<T>* node, const T& value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return find(node->left, value);
        } else {
            return find(node->right, value);
        }
    }

    bool contains(AVLNode<T>* node, const T& value) {
        return find(node, value) != nullptr;
    }

    int countDistinct(AVLNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countDistinct(node->left) + countDistinct(node->right);
    }

    void printInOrder(AVLNode<T>* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->data << " (Count: " << node->count << "), ";
            printInOrder(node->right);
        }
    }

    void printPreOrder(AVLNode<T>* node) {
        if (node != nullptr) {
            cout << node->data << " (Count: " << node->count << "), ";
            printPreOrder(node->left);
            printPreOrder(node->right);
        }
    }

    void printPostOrder(AVLNode<T>* node) {
        if (node != nullptr) {
            printPostOrder(node->left);
            printPostOrder(node->right);
            cout << node->data << " (Count: " << node->count << "), ";
        }
    }
};
