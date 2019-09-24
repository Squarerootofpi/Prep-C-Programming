#ifndef BST_H
#define BST_H


#include "BSTInterface.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <istream>


using std::endl;
using std::cout;
using std::string;
using std::ostringstream;
using std::stringstream;


template<typename T>
class BST : BSTInterface<T>
{
private:

	//THE NODE FOR BST
	class Node
	{
	public:
		T data;
		Node* left;
		Node* right;
		//Constructor
		Node(const T& dataItem, Node* leftVal = NULL, Node* rightVal = NULL)
			: left(leftVal), right(rightVal), data(dataItem) {}
		//Destructor
		~Node() {}
		// returns data in Node
		virtual std::string toString() const
		{
			ostringstream os;
			os << data;
			return os.str();
		}
	};

	unsigned int size;
	Node* root;

public:
	//Constructor with no arguments
	BST() : root(NULL), size(0) {}
	//Constructor with root given 
	BST(Node* newRoot) : root(newRoot), size(0) {}
	//Destructor
	~BST()
	{
		clearTree();
	}


	/** Return true if node added to BST, else false */
	virtual bool addNode(const T& item)
	{
		return addNode(this->root, item); //start at root
	}
	//recursive addNode, in .cpp
	bool addNode(Node*& localRoot, const T& item);

	/** Return true if node removed from BST, else false */
	virtual bool removeNode(const T& item)
	{
		return removeNode(this->root, item);
	}
	//Recursive removal, in .cpp
	virtual bool removeNode(Node*& localRoot, const T& item);

	//Replaces the parent Node for a root, in .cpp
	void replaceParent(Node*& oldRoot, Node*& localRoot);

	/** Returns Left subtree */ //Not used, but useful for certain trees
	BST leftSubTree(Node& toCheck) const
	{
		if (root == NULL)
		{
			throw std::invalid_argument("get_left_subtree on empty tree");
		}
		return BST(toCheck->left);
	}

	/** Returns Right subtree */ //Not used, but useful for certain trees
	BST rightSubTree(Node* toCheck) const
	{
		if (root == NULL)
		{
			throw std::invalid_argument("get_right_subtree on empty tree");
		}
		return BST(toCheck->right); //returns a tree made from the right side
	}

	/** Indicate that this tree is a leaf */ //Not used, but useful for certain trees
	bool isLeaf() const
	{
		if (root != NULL)
		{
			return root->left == NULL && root->right == NULL; //returns false if there are any subtrees
		}
		else return true; //there are no subtrees, tree is leaf
	}

	/** Return true if BST cleared of all nodes, else false */
	virtual bool clearTree()
	{
		if (root == NULL) return true;
		else
		{
			clearTreeRecursive(root);
		}
		root = NULL; //last, finish root assignment to null.
		size = 0;
		return true;
	}
	//Recursive call of clearTree
	bool clearTreeRecursive(Node* root) const
	{
		if (root == NULL) return true;

		if ((root->left != NULL) || (root->right != NULL))
		{
			clearTreeRecursive(root->left);
			clearTreeRecursive(root->right);
		}
		delete root;
		root = NULL;
		return true;
	} // end outLevel()

	/** Output nodes at a given level */
	bool outLevel(Node* root, int level, stringstream& out) const;

	/** Outputs inorder traversal of tree */
	bool inOrder(Node* root, stringstream& out) const;

	/** inorder toString traversal */
	string inOrderToString() const
	{
		stringstream ss;
		if (inOrder(root, ss))
		{
			return ss.str();
		}
		return " empty";
	}

	/** Return a level order traversal of a BST as a string */
	virtual string toString() const;

	/** Returns size of BST */
	int getSize() const
	{
		return size;
	}

	/** Returns if data is inside BST, NOT using iterator, recursively */
	const bool findRecursive(Node* localRoot, const T& toFind) const
	{
		if (localRoot == NULL) return false; //not found in leaf
		if (toFind == localRoot->data) return true; //data is the same!
		if (toFind < localRoot->data) return findRecursive(localRoot->left, toFind); //check the left
		else if (localRoot->data < toFind) return findRecursive(localRoot->right, toFind); //check the right
	}
	//Wrapper of find
	bool find(T& toFind) const
	{
		return findRecursive(root, toFind); //sees if it is inside the function...
	}

};

template<typename T>
/** Output nodes at a given level */
bool BST<T>::outLevel(Node* root, int level, stringstream& out) const
{
	if (root == NULL) return false;
	if (level == 0)
	{
		out << " " << root->data;
		if ((root->left != NULL) || (root->right != NULL)) { return true; }
		return false;
	}
	if ((level == 1) && !root->left && root->right) out << " _";
	bool left = outLevel(root->left, level - 1, out);
	bool right = outLevel(root->right, level - 1, out);
	if ((level == 1) && root->left && !root->right) out << " _";
	return left || right;
} // end outLevel()

template<typename T>
/** Return a level order traversal of a BST as a string */
string BST<T>::toString() const
{
	stringstream out;
	if (root == NULL) out << " empty";
	else
	{
		int level = 0;
		do
		{
			out << endl << "  " << ++level << ":";
		} while (outLevel(root, level - 1, out));
	}
	out << endl;
	return out.str();
}

template<typename T>
//recursive addNode 
bool BST<T>::addNode(Node*& localRoot, const T& item)
{
	if (localRoot == NULL)
	{
		localRoot = new Node(item);
		++size;
		return true;
	}
	else
	{
		if (item < localRoot->data) return addNode(localRoot->left, item);
		else if (localRoot->data < item) return addNode(localRoot->right, item);
		else return false; //it was found inside the tree already
	}
}

template<typename T>
//Recursive removal
bool BST<T>::removeNode(Node*& localRoot, const T& item)
{
	if (localRoot == NULL) { return false; }
	else
	{
		if (item < localRoot->data)
		{
			return removeNode(localRoot->left, item);
		}
		else if (localRoot->data < item)
		{
			return removeNode(localRoot->right, item);
		}
		else
		{ // Found item
			Node* oldRoot = localRoot;
			if (localRoot->left == NULL)
			{
				localRoot = localRoot->right;
			}
			else if (localRoot->right == NULL)
			{
				localRoot = localRoot->left;
			}
			else
			{
				replaceParent(oldRoot, oldRoot->left); //Need to do complex replacement
			}
			delete oldRoot;
			--size;
			return true;
		}
	}
}

template<typename T>
//Replaces the parent Node for a root
void BST<T>::replaceParent(Node*& oldRoot, Node*& localRoot) {
	if (localRoot->right != NULL)
	{
		replaceParent(oldRoot, localRoot->right);
	}
	else
	{
		oldRoot->data = localRoot->data; //reassign data!
		oldRoot = localRoot;
		localRoot = localRoot->left;
	}
}

template<typename T>
/** Outputs inorder traversal of tree */
bool BST<T>::inOrder(Node* root, stringstream& out) const
{
	if (root == NULL)
	{
		return false; //there is nothing there....
	}
	if (root->left == NULL && root->right == NULL) //it is a leaf
	{
		if (out.str().size() != 0) //if there is nothing in the string yet, don't put a commma
		{
			out << ",";
		}
		out << root->data;
		return true;
	}
	if (root->left != NULL && root->right == NULL) //There is something on the left
	{
		inOrder(root->left, out);
		out << ",";
		out << root->data;
		return true;
	}
	if (root->left == NULL && root->right != NULL) //There is something on the right
	{
		if (out.str().size() != 0) //if there is nothing in the string yet, don't put a commma
		{
			out << ",";
		}
		out << root->data;
		inOrder(root->right, out);
		return true;
	}
	//last case: both children are not null
	inOrder(root->left, out);
	out << ",";
	out << root->data;
	inOrder(root->right, out);
	return true;
}

#endif // !BST_H


//IF YOU EVER WANT TO IMPLIMENT, THESE ARE FAIRLY READY

/** These two functions to return DATA inside BST, NOT using iterator */
	/*const T* findReturnWrap(const T& target) const
	{
		return findReturn(this->root, target);
	}*/
	//Recursive findReturn
	/*const T* findReturn(Node* localRoot, const T& target) const
	{
		if (localRoot == NULL) return NULL;
		if (target < localRoot->data) return find(localRoot->left, target);
		else if (localRoot->data < target) return find(localRoot->right, target);
		else return &(localRoot->data);
	}


	/*
	bool find(T& toFind) const
	{
		if (toFind == findReturnWrap(toFind)) return true; //sees if it is inside the function...
		return false;
	}
	*/