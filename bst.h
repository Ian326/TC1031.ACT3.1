// =================================================================
//
// File: bst.h
// Author: Ian Joab Padrón Corona - A01708940
// Date: 17-Oct
//
// =================================================================
#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <string>
#include "exception.h"
#include "header.h"
#include <bits/stdc++.h>

template <class T> class BST;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	T value;


	Node(T);
	Node(T, Node<T>*, Node<T>*);

	bool find(T) const;

	void add(T);

	Node<T>* succesor();
	void remove(T);
	void removeChilds();

	void inOrder(std::stringstream&) const;
	void postOrder(std::stringstream&) const;
	void preOrder(std::stringstream&) const;

	uint leaves() const;
	bool isFull2() const;
	bool isFull() const;
	T ancestor(T) const;

	friend class BST<T>;
 public:
	 Node *left, *right;
};

// =================================================================
// Constructor. Initializes the value of the node. The variables
// left and right a initialized to null.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), left(NULL), right(NULL) {}

// =================================================================
// Constructor. Initializes all instances variables.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri)
	: value(val), left(le), right(ri) {}

// =================================================================
// Search for an element within the bst.
//
// @param val, the searched element.
// returns True, if the element is in the bst. False, otherwise.
// =================================================================
template <class T>
bool Node<T>::find(T val) const {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != NULL && left->find(val));
	} else {
		return (right != NULL && right->find(val));
	}
}

// =================================================================
// Add an element within the bst.
//
// @param val, the element to be inserted.
// =================================================================
template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != NULL) {
			left->add(val);
		} else {
			left = new Node<T>(val);
		}
	} else {
		if (right != NULL) {
			right->add(val);
		} else {
			right = new Node<T>(val);
		}
	}
}

// =================================================================
// Finds the correct successor for a parent node.
//
// returns the successor node of a node or NULL, if it a leaf node.
// =================================================================
template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (left == NULL && right == NULL) {
		return NULL;
	}

	if (left == NULL && right != NULL) {
		right = NULL;
		return ri;
	}

	if (left != NULL && left->right == NULL) {
		left = le->left;
		le->left = NULL;
		return le;
	}

	if (left != NULL && left->right != NULL) {
		Node<T> *parent, *child;
		parent = left;
		child = left->right;

		while (child->right != NULL) {
			parent = child;
			child = child->right;
		}
		parent->right = child->left;
		child->left = NULL;
		return child;
	}

	return NULL;
}

// =================================================================
// Remove an elemento, putting a suc node in its place.
//
// param @val, the element to be removed.
// =================================================================

template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != NULL) {
			if (left->value == val) {
				old = left;
				succ = left->succesor();
				if (succ != NULL) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != NULL) {
			if (right->value == val) {
				old = right;
				succ = right->succesor();
				if (succ != NULL) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

// =================================================================
// Removes, recursively, the childs of a parent node.
//
// =================================================================
template <class T>
void Node<T>::removeChilds() {
	if (left != NULL) {
		left->removeChilds();
		delete left;
		left = NULL;
	}

	if (right != NULL) {
		right->removeChilds();
		delete right;
		right = NULL;
	}
}

// =================================================================
// Go through the tree in inorder.
//
// @param aux, a stringstream used to create the string to display.
// =================================================================
template <class T>
void Node<T>::inOrder(std::stringstream &aux) const {
	if (left != NULL) {
		left->inOrder(aux);
	}
	aux << value << " ";
	if (right != NULL) {
		right->inOrder(aux);
	}
}

// =================================================================
// Go through the tree in postorder.
//
// @param aux, a stringstream used to create the string to display.
// =================================================================
template <class T>
void Node<T>::postOrder(std::stringstream &aux) const {
	if (left != 0) {
		left->postOrder(aux);
	}
	if (right != 0) {
		right->postOrder(aux);
	}
	aux << value << " ";
}

// =================================================================
// Go through the tree in preorder.
//
// @param aux, a stringstream used to create the string to display.
// =================================================================
template <class T>
void Node<T>::preOrder(std::stringstream &aux) const {
	aux << value << " ";
	if (left != NULL) {
		left->preOrder(aux);
	}
	if (right != NULL) {
		right->preOrder(aux);
	}
}

// =================================================================
// Definition of the Binary Search Tree class
// =================================================================
template <class T>
class BST {
private:
	Node<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	bool find(T) const;

	void add(T);

	void remove(T);
	void removeAll();


	std::string inOrder() const;
	std::string postOrder() const;
	std::string preOrder() const;

	std::string byLevel();
	bool printLevel(Node<T>* root, int level, std::stringstream &aux);
	std::string printAllLevels(Node<T>* root);

	uint leaves() const;
	uint leaves2(Node<T>*) const;

	bool isFull2(Node<T>*) const;
	bool isFull() const;

	T ancestor(T) const;
	T ancestor1(Node<T>*, T, std::vector<T>&) const;
};

template <class T>
BST<T>::BST() : root(NULL) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

// =================================================================
// Returns if the bst is empty or not.
//
// returns True is the root node is NULL. False, if the bst is
//				 empty.
// =================================================================
template <class T>
bool BST<T>::empty() const {
	return (root == NULL);
}

// =================================================================
// Search for an element within the bst.
//
// @param val, the searched element.
// returns the result of searching for an element within the tree.
//				 False, if the bst is empty.
// =================================================================
template <class T>
bool BST<T>::find(T val) const {
	if (!empty()) {
		return root->find(val);
	} else {
		return false;
	}
}

// =================================================================
// Add an element within the bst.
//
// @param val, the element to be inserted.
// =================================================================
template<class T>
void BST<T>::add(T val) {
	if (!empty()) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}

// =================================================================
// Removes an element from the bst.
//
// @param val, the element to be removed.
// =================================================================
template <class T>
void BST<T>::remove(T val) {
	if (!empty()) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != NULL) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

// =================================================================
// Removes all the elements from the bst.
//
// =================================================================
template <class T>
void BST<T>::removeAll() {
	if (!empty()) {
		root->removeChilds();
		delete root;
		root = NULL;
	}
}

// =================================================================
// Go through the tree in inorder.
//
// returns a string with the result of the inorder traverse of the
//				 bst.
// =================================================================
template <class T>
std::string BST<T>::inOrder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inOrder(aux);
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Go through the tree in preorder.
//
// returns a string with the result of the preorder traverse of the
//				 bst.
// =================================================================
template <class T>
std::string BST<T>::preOrder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preOrder(aux);
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Go through the tree in posrorder.
//
// returns a string with the result of the posrorder traverse of the
//				 bst.
// =================================================================
template <class T>
std::string BST<T>::postOrder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postOrder(aux);
	}
	aux << "]";
	return aux.str();
}


// =================================================================
// Returns the level traversal of the tree.
//
// @return a string with the level traversal of the tree.
// =================================================================
template <class T>
std::string BST<T>::byLevel() {
	 	std::string levels = printAllLevels(root);
		return levels;
}

template <class T>
bool BST<T>::printLevel(Node<T>* root, int level, std::stringstream &aux)
{
    if (root == NULL) {
        return false;
    }

    if (level == 1)
    {
        aux << root->value << " ";
        return true;
    }

    bool left = printLevel(root->left, level - 1, aux);
    bool right = printLevel(root->right, level - 1, aux);

    return left || right;
}

// Real function to print level order traversal of a given binary tree
template <class T>
std::string BST<T>::printAllLevels(Node<T>* root)
{
	std::stringstream aux;

	aux << "[";
  int level = 1;
  while (printLevel(root, level, aux)) {
      level++;
    }
		aux << "]";
		return aux.str();
}

// =================================================================
// Returns how many leaves are below the current node. Remember that
// a node without children is a leaf.
//
// @return the number of leaves below the current node.
// =================================================================
template <class T>
uint BST<T>::leaves() const {
	int leafcount = 0;
	leafcount = leaves2(root);

	return leafcount;
}

template <class T>
uint BST<T>::leaves2(Node<T>* root) const {
	if(root == NULL)
		return 0;
	if(root->left == NULL && root->right == NULL)
		return 1;
	else
		return leaves2(root->left)+
			leaves2(root->right);
}

// =================================================================
// Returns if a node is full. A node is said to be complete if:
// a) it is a leaf, b) they have both children, both children are
// full and both children have the same depth.
//
// @return true if the node is complete, false otherwise.
// =================================================================
template <class T>
bool BST<T>::isFull() const {
	bool full = isFull2(root);
	return full;
}

template <class T>
bool BST<T>::isFull2(Node<T>* root) const {
	if (root == NULL) {
		return false;
	}
	if (root -> left == NULL and root -> right == NULL) {
		return true;
	}
	else if (root -> left and root -> right) {
	 	return (isFull2(root -> left) and isFull2(root -> right));
	}
	return false;
}

// =================================================================
// Returns the ancestors (parent) of the value * val *.
//
// @return the ancestor (father) of * val *.
// @throw NoSuchElement if the * val * element is not inside the
//				tree.
// =================================================================
template <class T>
T BST<T>::ancestor1(Node<T>* root, T val, std::vector<T> &ancestors) const{
  if (root == NULL)
     return false;

  if (root->value == val)
     return true;

  if ( ancestor1(root->left, val, ancestors) ||
       ancestor1(root->right, val, ancestors) )
  {
    ancestors.push_back(root->value);
    return true;
  }

  return false;
}

// =================================================================
// Returns the ancestor of a value.
//
// @return the ancestor of val.
// @throws an exception if the element does not exist or if it is
//				 the ancestor of the root.
// =================================================================
template <class T>
T BST<T>::ancestor(T val) const {
	if (empty()) {
		throw NoSuchElement();
	}

	if (root->value == val) {
		throw NoSuchElement();
	}
	std::vector<T> ancestors;
	ancestor1(root, val, ancestors);
	return ancestors.back();
}

#endif /* BST_H */
