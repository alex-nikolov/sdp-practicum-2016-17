#include <iostream>
#include <algorithm>

#include "bin_tree.cpp"

using namespace std;

template <typename T>
void printLTR(BinTree<T> const& bt) {
    helperPrint(bt.getRoot());
}

template <typename T>
void helperPrint(Node<T>* root) {
    if (root) {
        helperPrint(root->left);
        cout << root->data << endl;
        helperPrint(root->right);
    }
}



template <typename T>
int height(BinTree<T> const& bt) {
    return helperHeight(bt.getRoot());
}

template <typename T>
int helperHeight(Node<T>* root) {
    if (!root || root->isLeaf())
        return 0;
    
    return 1 + max(helperHeight(root->left), helperHeight(root->right));
}



template <typename T>
int longestPath(BinTree<T> const& bt) {
    return longestPathHelper(bt.getRoot());
}

template <typename T>
int longestPathHelper(Node<T>* root) {
    if (!root)
        return 0;
    
    int leftHeight = helperHeight(root->left);
    int rightHeight = helperHeight(root->right);
    
    int leftLongestPath = longestPathHelper(root->left);
    int rightLongestPath = longestPathHelper(root->right);
    
    // Имаме два възможни случая: Или пътят минава през текущия връх, или не.
    // Ако не минава, то най-дългият път се намира в лявото или дясното поддърво.
    // Ако минава, т.е. пътят съдържа лявото и дясното дете на текущия връх,
    // то най-дългият път е точно височината на лявото, събрана с тази на дясното поддърво + 2.
    return max(leftHeight + rightHeight + 2, max(leftLongestPath, rightLongestPath));
}



template <typename T>
bool equal(BinTree<T> const& first, BinTree<T> const& second) {
    return helperEqual(first.getRoot(), second.getRoot());
}

template <typename T>
bool helperEqual(Node<T>* first, Node<T>* second) {
    // Ако и двата корена не са дефинирани, то дърветата са еднакви.
    if (!first && !second)
        return true;
    
    // Ако единият е дефиниран, а другият не, не са еднакви.
    if ((first && !second) || (!first && second))
        return false;
    
    // В противен случай за да са еднакви е необходимо данните в корените да съвпадат, както и левите и десните
    // поддървета да съвпадат.
    return (first->data == second->data &&
            helperEqual(first->left, second->left) &&
            helperEqual(first->right, second->right));
}



template <typename T>
double evalExpression(BinTree<T> const& bt) {
    return helperEval(bt.getRoot());
}

template <typename T>
double helperEval(Node<T>* root) {
    if (!root)
        return 0;
    
    if (root->isLeaf())
        return root->data - '0';
    
    switch (root->data) {
        case '+':
            return helperEval(root->left) + helperEval(root->right);
        case '-':
            return helperEval(root->left) - helperEval(root->right);
        case '*':
            return helperEval(root->left) * helperEval(root->right);
        case '/':
            return helperEval(root->left) / helperEval(root->right);
    }
}



template <typename T>
void longestConsecutiveUtil(Node<T>* root, int curLength,
                              int expected, int& res)
{
    if (root == NULL)
        return;

    // Ако в текущия възел стойността е поне толкова, колкото е нужна, за да се получи път с растящи възли,
    // текущата дължина се увеличава.
    if (root->data >= expected)
        curLength++;
    else
        curLength = 1;

    res = max(res, curLength);

    // Рекурсивно викаме за лявото и дясното поддърво.
    longestConsecutiveUtil(root->left, curLength,
                           root->data + 1, res);
    longestConsecutiveUtil(root->right, curLength,
                           root->data + 1, res);
}

template <typename T>
int longestIncreasingPath(BinTree<T> const& bt)
{
    Node<T>* root = bt.getRoot();

    if (root == NULL)
        return 0;
 
    int res = 0;

    longestConsecutiveUtil(root, 0, root->data, res);
 
    return res;
}



int main() {
    BinTree<double> tree;
    Node<double>* root = tree.add(NULL, 0, 25);
    Node<double>* one = tree.add(root, 0, 1);
    Node<double>* two = tree.add(root, 1, 2);
    Node<double>* three = tree.add(one, 0, 3);
    
    Node<double>* ten = tree.add(three, 1, 10);
    Node<double>* fifteen = tree.add(ten, 0, 15);
    Node<double>* thirty = tree.add(one, 1, 30);
    Node<double>* forty = tree.add(thirty, 1, 40);
    Node<double>* fifty = tree.add(forty, 1, 50);
    
    
    BinTree<double> cpy = tree;
    Node<double>* r = tree.getRoot();
    Node<double>* a = r->right;
    tree.add(a, 1, 11);
    
    printLTR(tree);
    cout << endl;
    printLTR(cpy);
    cout << endl;
    cout << endl << height(tree) << endl;
    cout << longestPath(tree) << endl;
    cout << equal(tree, cpy) << endl << endl;
    
    
    BinTree<char> exp;
    Node<char>* _root = exp.add(NULL, 0, '*');
    Node<char>* _plus = exp.add(_root, 0, '+');
    Node<char>* _five = exp.add(_plus, 0, '5');
    Node<char>* _ten = exp.add(_plus, 1, '9');
    Node<char>* _two = exp.add(_root, 1, '2');
    
    cout << evalExpression(exp) << endl;
    
    cout << longestIncreasingPath(tree);
}
