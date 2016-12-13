#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
	double key;
	int height;
	Node* left;
	Node* right;
	
	Node(double k) {
		key = k;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

class BST {
	Node* root;

	int height(Node*) const;
	int balanceCoef(Node*) const;
	void fixHeight(Node*);
	
	Node* rotateRight(Node*);
	Node* rotateLeft(Node*);
	Node* balance(Node*);
	
	Node* findMin(Node*);
	Node* removeMin(Node*);

	Node* insertHelper(Node*, double);
	Node* removeHelper(Node*, double);
	bool findHelper(Node*, double) const;
	
	void printHelper(Node*) const;
public:
	BST();

	void insert(double);
	void remove(double);
	bool find(double) const;
	
	void print() const;
};

BST::BST() {
	root = NULL;
}

// Целта на тази функция е да си сместим постоянни if-ове за валидността на node,
// тъй като ако node е NULL и викнем height, програмата ще гръмне.
int BST::height(Node* node) const {
    return node ? node->height : 0;
}

// Връщаме разликата от височината на дясното поддърво и лявото
// Така ако функцията върне 2, то дясното е по-тежко и има нужда от пребалансиране,
// ако върне -2, същото се отнася за лявото поддърво.
int BST::balanceCoef(Node* node) const {
    return height(node->right) - height(node->left);
}

// Приемаме, че стойностите на height в преките ни деца са правилно сметнати,
// затова не е нужно да смятаме рекурсивно цялата височина на поддървото.
void BST::fixHeight(Node* node) {
	node->height = max(height(node->left), height(node->right)) + 1;
}

// За завъртанията пробвайте да си нарисувате картинка, аз мисля да добавя такава скоро.
Node* BST::rotateRight(Node* node) {
    Node* leftChild = node->left;

    node->left = leftChild->right;
    leftChild->right = node;

    fixHeight(node);
    fixHeight(leftChild);

    return leftChild;
}

Node* BST::rotateLeft(Node* node) {
    Node* rightChild = node->right;

    node->right = rightChild->left;
    rightChild->left = node;

    fixHeight(node);
    fixHeight(rightChild);

    return rightChild;
}

Node* BST::balance(Node* node) {
    fixHeight(node);
	int coef = balanceCoef(node);

	// Дясното е по-тежко
    if (coef == 2) {
		// Ако лявото поддърво на дясното дете е по-тежко от дясното поддърво, имаме нужда
		// от пребалансиране първо там.
        if (balanceCoef(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
	// Аналогично ако лявото е по-тежко
    if (coef == -2) {
        if (balanceCoef(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    return node;
}

void BST::insert(double x) {
	root = insertHelper(root, x);
}

Node* BST::insertHelper(Node* node, double x) {
    if (!node)
		return new Node(x);
    if (x < node->key)
        node->left = insertHelper(node->left, x);
    else
        node->right = insertHelper(node->right, x);

    return balance(node);
}

// Минималният възел в едно поддърво представлява възможно най-лявото дете.
Node* BST::findMin(Node* node) {
    return node->left ? findMin(node->left) : node;
}

Node* BST::removeMin(Node* node) {
	// Ако няма ляво дете, то най-малкият възел е текущият и връщаме дясното поддърво.
    if (!node->left)
        return node->right;

    node->left = removeMin(node->left);

    return balance(node);
}

void BST::remove(double x) {
	root = removeHelper(root, x);
}

Node* BST::removeHelper(Node* node, double x) {
    if (!node)
		return 0;
    if (x < node->key)
        node->left = removeHelper(node->left, x);
    else if (x > node->key)
        node->right = removeHelper(node->right, x);
	// Ако сме попаднали на точния възел
    else {
        Node* leftChild = node->left;
        Node* rightChild = node->right;
        delete node;

        if (!rightChild)
			return leftChild;
		
		// Намираме минималния елемент в дясното поддърво
        Node* min = findMin(rightChild);
		// Пренасочваме му лявото и дясното дете. Отново се опитайте да си нарисувате картинка
        min->right = removeMin(rightChild);
        min->left = leftChild;

        return balance(min);
    }
    return balance(node);
}

bool BST::find(double x) const {
	return findHelper(root, x);
}

bool BST::findHelper(Node* node, double x) const {
	if (!node)
		return false;
	if (node->key == x)
		return true;
	
	return findHelper(node->left, x) || findHelper(node->right, x);
}

void BST::print() const {
	printHelper(root);
}

void BST::printHelper(Node* node) const {
	if (node) {
		cout << node->key << " ";
		
		printHelper(node->left);
		printHelper(node->right);
	}
}


int main() {
	BST b;
	
	for (int i = 0; i < 10; i++)
		b.insert(i);
		
	for (int i = 0; i < 10; i++)
		cout << b.find(i) << " ";
	
	cout << endl;
	b.print();
}