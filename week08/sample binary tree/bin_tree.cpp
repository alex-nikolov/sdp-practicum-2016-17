#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* back;

    Node(T const&, Node<T>*, Node<T>*, Node<T>*);
    Node() {};
};

template <typename T>
Node<T>::Node(T const& _data, Node<T>* _left, Node<T>* _right, Node<T>* _back) {
    data = _data;
    left = _left;
    right = _right;
    back = _back;
}

template <typename T>
class BinTree {
    Node<T>* root;

    Node<T>* copy(Node<T>*);
public:
    BinTree();
    BinTree(BinTree<T> const&);
    ~BinTree();
    BinTree<T>& operator=(BinTree<T> const&);

    Node<T>* add(Node<T>*, int, T const&);
    void erase(Node<T>*);

    Node<T>* getRoot();
};

template <typename T>
Node<T>* BinTree<T>::copy(Node<T>* node) {
    if (!node)
        return NULL;

    return new Node<T>(node->data, copy(node->left), copy(node->right), node->back);
}

template <typename T>
BinTree<T>::BinTree() {
    root = NULL;
}

template <typename T>
BinTree<T>::~BinTree() {
    erase(root);
}

template <typename T>
BinTree<T>::BinTree(BinTree<T> const& tree) {
    root = copy(tree.root);
}


template <typename T>
Node<T>* BinTree<T>::getRoot() {
    return root;
}

template <typename T>
BinTree<T>& BinTree<T>::operator=(BinTree<T> const& rs) {
    if (this != &rs) {
        erase(root);
        root = copy(rs.root);
    }

    return *this;
}

template <typename T>
Node<T>* BinTree<T>::add(Node<T>* current, int leftOrRight, T const& data) {
    if (current == NULL && root == NULL) {
        root = new Node<T>(data, NULL, NULL, current);
        return root;
    }

    Node<T>* child = (leftOrRight == 0) ? current->left : current->right;

    if (child == NULL) {
        Node<T>* newChild = new Node<T>(data, NULL, NULL, current);

        if (leftOrRight == 0)
            current->left = newChild;
        if (leftOrRight == 1)
            current->right = newChild;

        return newChild;
    }

    return NULL;
}

template <typename T>
void BinTree<T>::erase(Node<T>* toErase) {
    if (toErase != NULL) {
        erase(toErase->left);
        erase(toErase->right);

        Node<T>* back = toErase->back;
        if (back && back->left == toErase)
            back->left = NULL;
        else if (back && back->right == toErase)
            back->right = NULL;

        delete toErase;
    }
}

int main() {
    BinTree<double> tree;
    Node<double>* root = tree.add(NULL, 0, 25);
    Node<double>* one = tree.add(root, 0, 1);
    Node<double>* two = tree.add(root, 1, 2);
    Node<double>* three = tree.add(one, 0, 3);
}
