#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include<vector>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
    T value;
    Node* left;
    Node* right;

    Node(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node()
    {
        this->value = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
    Node<T>* _root;         // Root of the tree nodes

    /* Add new T val to the tree */
    void addHelper(Node<T>* root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            }
            else {
                addHelper(root->left, val);
            }
        }
        else {
            if (!root->right) {
                root->right = new Node<T>(val);
            }
            else {
                addHelper(root->right, val);
            }
        }
    }

    /* Print tree out in inorder (A + B) */
    void printInOrderHelper(Node<T>* root) {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

    /* Return number of nodes in tree */
    int nodesCountHelper(Node<T>* root) {
        if (!root) {
            return 0;
        }
        else {
            return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
        }
    }

    /* Return height of tree (root == nullptr -> 0) */
    int heightHelper(Node<T>* root) {
        if (!root) {
            return 0;
        }
        else {
            return 1 + max(heightHelper(root->left), heightHelper(root->right));
        }
    }

    /* Delete a given <T> value from tree */
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == nullptr || current->right == nullptr) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    }
                    else {
                        parent->right = temp;
                    }
                }
                else {
                    this->_root = temp;
                }
            }
            else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
            deleteValueHelper(current, current->right, value);
    }

    /********************************* PUBLIC API *****************************/
public:

    BST() : _root(nullptr) {
        _root = NULL;
    }               // Basic initialization constructor

    /**
     * Destructor - Needs to free *all* nodes in the tree
     * TODO: Implement Destructor
     */
    ~BST() {
        //deletes the BST tree.

        deep_delete(_root);
        

    }
    void deep_delete(Node<T>* node) {
        if (node == NULL)
            return;
        delete(node->left);
        delete(node->right);

        if (node->left == NULL && node->right == NULL) {
            delete node;
        }
    }

    /* Public API */
    void add(T val) {
        if (this->_root) {
            this->addHelper(this->_root, val);
        }
        else {
            this->_root = new Node<T>(val);
        }
    }

    void print() {
        printInOrderHelper(this->_root);
    }
    void print_level(Node<T>* root, int level) {
        if (root == NULL)
            return;
        if (level == 1)
            cout << " " << root->value;
        else if (level > 1) {
            print_level(root->left, level - 1);
            print_level(root->right, level - 1);
        }
    }
    /**
     * Print the nodes level by level, starting from the root
     * TODO: Implement printLevelOrder
     */
    void printLevelOrder() {
        Node<T>* node = _root;
        int h = height();

        for (int i = 1; i <= h; i++) {
            print_level(node, i);
            cout << " \n" << endl;
        }
    }

    int nodesCount() {
        return nodesCountHelper(this->_root);
    }

    int height() {
        return heightHelper(this->_root);
    }

    /**
     * Print the maximum path in this tree
     * TODO: Implement printMaxPath
     */
    void printMaxPath() {
       
        Node<T>* node = _root;
        while (node) {
            cout << node->value << " ";
            
            if (node->left && node->right) {

                if (heightHelper(node->left) >= heightHelper(node->right))
                    node = node->left;
                else
                    node = node->right;
            }

            else if (node->left)
                node = node->left;
            else if (node->right)
                node = node->right;
            else {
                node = NULL;
            }
        }
    }
    bool deleteValue(T value) {
        return this->deleteValueHelper(nullptr, this->_root, value);
    }

    /**
     * Find if the BST contains the value
     * TODO: Implement contains
     */
    bool contains(T value) {
        return contains_helper(this->_root, value);

    }
    
    bool contains_helper(Node<T>* root, T value) {
        if (root == NULL)    
            return false;
        if (root->value == value) 
            return true;
        if (root->value > value)  
            return contains_helper(root->left, value);
        return contains_helper(root->right, value);
    }
};

#endif