#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/***********
*  UTILS  *
***********/
int digitsCount(int number)
{
    if (number > -10 && number < 10)
        return 1;

    return digitsCount(number / 10) + 1;
}

int max(int arg1, int arg2)
{
    return arg1 < arg2 ? arg2 : arg1;
}

/***************
*  END UTILS  *
***************/

template <class T>
struct Node {
    T data;
    Node *left,
        *right;

    Node(T _data = T(), Node* _left = NULL, Node* _right = NULL)
        : data(_data)
        , left(_left)
        , right(_right)
    {
    }
};

template <typename T>
class Tree {
public:
    Tree(Node<T>* root = NULL)
        : m_root(root)
    {
    }
    virtual ~Tree();

    void initTestTree();

    Node<T>* getRoot()
    {
        return m_root;
    }

private:
    Node<T>* m_root;
    
    void del(Node<T> *root);
};

template <typename T>
void Tree<T>::del(Node<T> *root)
{
    if (!root)
        return;
    del(root->left);
    del(root->right);

    delete root;
}

template <typename T>
Tree<T>::~Tree()
{
    del(m_root);
}


template <typename T>
void Tree<T>::initTestTree()
{
/*
         9
      4     3
   5    5     7
  1 2  2 1   5 6
 3        3 8
*/
    Node<T>
       *n_5_0 = new Node<int>(3),
       *n_5_1 = new Node<int>(3),
       *n_5_2 = new Node<int>(8),

       *n_4_0 = new Node<int>(1, n_5_0, NULL),
       *n_4_1 = new Node<int>(2),
       *n_4_2 = new Node<int>(2),
       *n_4_3 = new Node<int>(1, NULL, n_5_1),
       *n_4_4 = new Node<int>(5, n_5_2, NULL),

       *n_3_0 = new Node<int>(5, n_4_0, n_4_1),
       *n_3_1 = new Node<int>(5, n_4_2, n_4_3),
       *n_3_2 = new Node<int>(7, n_4_4, NULL),

       *n_2_0 = new Node<int>(4, n_3_0, n_3_1),
       *n_2_1 = new Node<int>(3, NULL, n_3_2),

       *root = new Node<int>(9, n_2_0, n_2_1);

    m_root = root;
}


template <class T>
int height(Node<T>* root)
{
    if (!root)
        return 1;

    return max(height(root->left), height(root->right)) + 1;
}

template <typename T>
bool getPath(Node<T> *root, T elem, string& path)
{
    if (!root)
        return false;

    if (root->data == elem)
        return true;

    if (getPath(root->left, elem, path))
    {
        path.push_back('l');
        return true;
    }

    if (getPath(root->right, elem, path))
    {
        path.push_back('r');
        return true;
    }
}

template <class T>
void printTree(Node<T>* root)
{
    Node<T>* level_sep = NULL;
    Node<T> missing_elem = Node<int>();

    queue<Node<T>*> leveled_tree_elems;
    leveled_tree_elems.push(root);
    leveled_tree_elems.push(level_sep);

    int level = 1;
    int tree_height = height(root);
    int padding;
    Node<T>* current;
    while (level < tree_height) {
        current = leveled_tree_elems.front();
        leveled_tree_elems.pop();

        if (!current) { // sentinel reached
            level++;
            // all items for the next level have been added
            leveled_tree_elems.push(level_sep);

            // print relations
            cout << endl;
        } else {
            // add children
            leveled_tree_elems.push(current->left ? current->left : &missing_elem);
            leveled_tree_elems.push(current->right ? current->right : &missing_elem);

            // next element padding
            padding = (1 << (tree_height - level)); // 2 ^ height
            cout << string(padding, ' ');

            // finally, print level element
            cout << current->data;

            // also on the right
            cout << string(padding, ' ');
        }
    }
}

template <typename T>
void printTreeLevel(Node<T>* root, int level)
{
    if (!root)
        return;
    if (level == 1)
        cout << root->data << ' ';

    printTreeLevel(root->left, level-1);
    printTreeLevel(root->right, level-1);
}

template <class T>
void reverseTree(Node<T>* root)
{
    if (!root)
        return;

    reverseTree(root->left);
    reverseTree(root->right);

    Node<T>* temp = root->left;
    root->left = root->right;
    root->right = temp;
}


template <typename T>
int size(Node<T>* root)
{
    if (!root)
        return 0;

    return size(root->right) + size(root->left) + 1;
}

template <typename T>
int leafsSum(Node<T>* root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return root->data;

    return leafsSum(root->left) + leafsSum(root->right);
}

template <typename T>
void getLeafs(Node<T>* root, vector<Node<T>*>& leafsArr)
{
    if (!root)
        return;
    if (!root->left && !root->right)
        return leafsArr.push_back(root);

    getLeafs(root->right, leafsArr);
    getLeafs(root->left, leafsArr);
}

template <typename T>
bool sameTree(Node<T>* root1, Node<T>* root2)
{
    // Are both NULL?
    if (!root1 || !root2)
        return root1 == root2;

    if (root1->data != root2->data)
        return false;

    // it will terminate with false as soon as a mismatch is found
    return sameTree(root1->left, root1->left) && sameTree(root1->right, root1->right);
}

// TODO fix
template <typename T>
bool simetricTreeDest(Node<T>* root)
{
    reverseTree(root->right);
    return sameTree(root->left, root->right);
}

// Like same tree
template <typename T>
bool simetricTree(Node<T>* root)
{
    if (!root)
        return true;

    bool flag = true;
    stack<Node<T>*> treesElems;
    Node<T> *rootLeft = root->left,
            *rootRight = root->right;

    treesElems.push(rootLeft);
    treesElems.push(rootRight);
    while (!treesElems.empty() && flag) {
        rootLeft = treesElems.top();
        treesElems.pop();
        rootRight = treesElems.top();
        treesElems.pop();

        if (!rootLeft || !rootRight) {
            flag = rootLeft == rootRight;
        } else {

            flag = rootLeft->data == rootRight->data;

            // simulate the recursion
            treesElems.push(rootLeft->left);
            treesElems.push(rootRight->right);
            treesElems.push(rootLeft->right);
            treesElems.push(rootRight->left);
        }
    }

    return flag;
}

/*
 *   x
 *  / \
 * y   z
 */
template <typename T>
void simpleTreeToList(Node<T>* root)
{
    if (!root)
        return;

    if (!root->left && !root->right) {
        root->left = root->right = root;
    }

    // next element
    if (root->left) {
        root->left->right = root;

        // make it cyclic
        root->left->left = root->right ? root->right : root;
    }

    if (root->right) {
        // prev element
        root->right->left = root;

        // make it cyclic
        root->right->right = root->left ? root->left : root;
    }
}

int main()
{

 /*
         9
      4     3
   5    5     7
  1 2  2 1   5 6
 3        3 8
 */
    Tree<int> t;
    t.initTestTree();

    printTree(t.getRoot());

//    reverseTree(t.getRoot());
//    printTree(t.getRoot());

    vector<Node<int>*> leafs;
    getLeafs(t.getRoot(), leafs);

    // range-based loop
    for (auto i : leafs) {
        cout << i->data << ' ';
    }
    cout << endl;

    cout << "Same: " << sameTree(t.getRoot(), t.getRoot()) << endl;
    cout << "Same: " << sameTree(t.getRoot(), t.getRoot()->left) << endl;

    cout << "Simetric: " << simetricTree(t.getRoot()) << endl;
    cout << "Simetric: " << simetricTree(t.getRoot()->left) << endl;

    printTreeLevel(t.getRoot(), 3);
    cout << endl;

    string path;
    getPath(t.getRoot(), 8, path);
    cout << "Path - 8 : " << path << endl;

    cout << "Simetric Dest: " << simetricTreeDest(t.getRoot()) << endl;
    cout << "Simetric Dest: " << simetricTreeDest(t.getRoot()->left) << endl;


    return 0;
}

/*
InitTree
good print

 
 */
