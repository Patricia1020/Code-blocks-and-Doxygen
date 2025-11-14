#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;
template <class T>
struct Node
{
    T data;// data variable
    Node<T> *left;// node left variable
    Node<T> *right;// node right variab
};

template <class T>
class Bst
{
public:
      /**
        * @brief this is default constructor. so the aim of this method is to set the root into null
        * @return void
        */
    Bst();
      /**
        * @brief this is specific constructor. so the aim of this method is to set the root, left, and right node to inputted value
        * @return void
        */
    Bst(T data);
    /**
        * @brief destructor method
        * @return void
        */
    ~Bst();
      /** @brief to insert the node into binary search tree
        * @param data
        * @return true
        */
    bool insertNode(T data);
      /** @brief to delete the node from binary search tree
        * @param data
        * @return void
        */
    void deleteTree();
      /** @brief to define maximum value in bst
        * @return true
        */
    int maxValue();
      /** @brief to define minimum value in bst
        * @return true
        */
    int minValue();
      /** @brief to insert the node from binary search tree with preorder format
        * @param data
        * @return void
        */
    void preOrderTraversal();
      /** @brief to insert the node from binary search tree with inorder format
        * @param data
        * @return void
        */
    void inOrderTraversal();
      /** @brief to insert the node from binary search tree with postorder format
        * @param data
        * @return void
        */
    void postOrderTraversal();
private:
    Node<T> *root;

      /** @brief to insert the node from binary search tree by implement the code
        * @param data, node
        * @return true or false
        */
    bool insertNode(T data, Node<T> *node);

    int maxValue(Node<T> *node);

    int minValue(Node<T> *node);
      /** @brief to delete the node from binary search tree by implement the code
        * @param node
        * @return void
        */
    void deleteTree(Node<T> *node);
      /** @brief to insert the node from binary search tree by implement the code using preorder format
        * @param node
        * @return void
        */
    void preOrderTraversal(Node<T> *node);
      /** @brief to insert the node from binary search tree by implement the code using inorder format
        * @param node
        * @return void
        */
    void inOrderTraversal(Node<T> *node);
      /** @brief to insert the node from binary search tree by implement the code using postorder format
        * @param node
        * @return void
        */
    void postOrderTraversal(Node<T> *node);
};

template <class T>
Bst<T>::Bst()
{root = NULL;}

template <class T>
Bst<T>::Bst(T data)
{
    root = new Node<T>;
    root->data = data;
    root->left = NULL;
    root->right = NULL;
}
template <class T>
Bst<T>::~Bst()
{deleteTree(root);}

template <class T>
bool Bst<T>::insertNode(T data)
{
    if (root != NULL)
    {return insertNode(data, root);}
    else
    {
        root = new Node<T>;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        return true;
    }
}

template <class T>
void Bst<T>::deleteTree()
{deleteTree(root);}

template <class T>
int Bst<T>::maxValue()
{maxValue(root);}

template <class T>
int Bst<T>::minValue()
{minValue(root);}

template <class T>
void Bst<T>:: preOrderTraversal()
{preOrderTraversal(root);}

template <class T>
void Bst<T>::inOrderTraversal()
{inOrderTraversal(root);}

template <class T>
void Bst<T>::postOrderTraversal()
{postOrderTraversal(root);}

template <class T>
bool Bst<T>::insertNode(T data, Node<T> *node)
{
    if (data < node->data)
    {// Create new node for left
        if (node->left != NULL)
        {insertNode(data, node->left);}
        else
        {
            node->left = new Node<T>;
            node->left->data = data;
            node->left->left = NULL;
            node->left->right = NULL;
            return true;
        }
    }
    if (data > node->data) // Create new node for right
    {
        if (node->right != NULL)
        {insertNode(data, node->right);}
        else
        {
            node->right = new Node<T>;
            node->right->data = data;
            node->right->left = NULL;
            node->right->right = NULL;
            return true;
        }
    }
    return false;
}

template <class T>
void Bst<T>::deleteTree(Node<T> *node)
{
    if(node != NULL)
    {root = NULL;}
    else
    {cout << "";}
}

template <class T>
int Bst<T>::maxValue(Node<T> *node)
{
    struct Node<T> *curr  = node;
    while (curr->right != NULL)
    {curr = curr->right;}
    return curr->data;
}

template <class T>
int Bst<T>::minValue(Node<T> *node)
{
    struct Node<T> *curr  = node;
    while (curr->left != NULL)
    {curr = curr->left;}
    return curr->data;
}

template <class T>
void Bst<T>:: preOrderTraversal(Node<T> *node)
{
    cout << node->data << " ";
    if (node->left != NULL)
    {preOrderTraversal(node->left);}
    if (node->right != NULL)
    {preOrderTraversal(node->right);}
}

template <class T>
void Bst<T>::inOrderTraversal(Node<T> *node)
{
    if (node->left != NULL)
    {inOrderTraversal(node->left);}
    cout << node->data << " ";
    if (node->right != NULL)
    {inOrderTraversal(node->right);}
}

template <class T>
void Bst<T>::postOrderTraversal(Node<T> *node)
{
    if (node->left != NULL)
    {postOrderTraversal(node->left);}
    if (node->right != NULL)
    {postOrderTraversal(node->right);}
    cout << node->data << " ";
}
#endif
