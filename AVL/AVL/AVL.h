#ifndef AVL_H
#define AVL_H


#include "AVLInterface.h"

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
class AVL : AVLInterface<T>
{
private:

	//THE NODE FOR AVL
	class Node
	{
	public:
		enum balance_type { LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = +1 };

		T data;
		Node* left;
		Node* right;
		// Additional data field not from BST, for AVL
		balance_type balance; 
		// Constructor 
		Node(const T& the_data, Node* left_val = NULL, Node* right_val = NULL) 
			: left(left_val), right(right_val), data(the_data), balance(BALANCED) {}


		//Destructor
		~Node() {}
		// returns data in Node
		virtual std::string toString() const
		{
			ostringstream os;
			os << balance << ": " << data; //Balance is AVL
			return os.str();
		}
	};

	unsigned int size;
	Node* root;
	bool increase; //AVL increase, initialized upon first insert
	bool decrease; //AVL remove, it is initialized upon first removal.

public:
	//Constructor with no arguments
	AVL() : root(NULL), size(0) {}
	//Constructor with root given 
	AVL(Node* newRoot) : root(newRoot), size(0) {}
	//Destructor
	~AVL()
	{
		clearTree();
	}

	//NON-AVL ADD AND INSERT!! ONLY FOR GENERIC BST
	/** Return true if node added to AVL, else false */
	virtual bool addNode(const T& item)
	{
		return addNode(this->root, item); //start at root
	}
	//recursive addNode, in .cpp
	bool addNode(Node*& localRoot, const T& item);

	/** Return true if node removed from AVL, else false */
	virtual bool removeNode(const T& item)
	{
		return removeNode(this->root, item);
	}
	//Recursive removal, in .cpp
	virtual bool removeNode(Node*& localRoot, const T& item);

	//Replaces the parent Node for a root, in .cpp
	void replaceParent(Node*& oldRoot, Node*& localRoot);

	/** Returns Left subtree */ //Not used, but useful for certain trees
	AVL leftSubTree(Node& toCheck) const
	{
		if (root == NULL)
		{
			throw std::invalid_argument("get_left_subtree on empty tree");
		}
		return AVL(toCheck->left);
	}

	/** Returns Right subtree */ //Not used, but useful for certain trees
	AVL rightSubTree(Node* toCheck) const
	{
		if (root == NULL)
		{
			throw std::invalid_argument("get_right_subtree on empty tree");
		}
		return AVL(toCheck->right); //returns a tree made from the right side
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

	/** Return true if AVL cleared of all nodes, else false */
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

	/** Return a level order traversal of a AVL as a string */
	virtual string toString() const;

	/** Returns size of AVL */
	int getSize() const
	{
		return size;
	}

	/** Returns if data is inside AVL, NOT using iterator, recursively */
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




	/**  AVL FUNCTIONS  */
	void rotate_right(Node*& local_root)
	{
		Node* temp = local_root->left;
		local_root->left = temp->right;
		temp->right = local_root;
		local_root = temp;
	}
	void rotate_left(Node*& local_root)
	{
		Node* temp = local_root->right;
		local_root->right = temp->left;
		temp->left = local_root;
		local_root = temp;
	}

	/** AVL INSERT: UTILIZES BALANCING **/
	/** Insert an item into the tree. 
	post: The item is in the tree. 
	@param item The item to be inserted 
	@return true only if the item was not already in the tree */ 
	virtual bool insert(const T& item) 
	{
		return insert(this->root, item); 
	} 
	/** Remove an item from the tree. 
	post: The item is no longer in the tree. 
	@param item The item to be removed 
	@return true only if the item was in the tree */ 
	/*virtual bool erase(const T& item) 
	{ 
		return erase(this->root, item); 
	}*/

	/** Recursive AVL insert 
	post: The item is in the tree. 
	@param local_root A reference to the current root 
	@param item The item to be inserted 
	@return true only if the item was not already in the tree */
	virtual bool insert(Node*& local_root, const T& item)
	{
		if (local_root == NULL)
		{
			local_root = new Node(item);
			increase = true;
			return true;
		}
		if (item < local_root->data) 
		{
			bool return_value = insert(local_root->left, item);
			if (increase) //The left subtree was increased!
			{ 
				Node* AVL_local_root = dynamic_cast<Node*>(local_root);
				switch (AVL_local_root->balance) {
				case Node::BALANCED: 
					// local root is now left heavy 
					AVL_local_root->balance = Node::LEFT_HEAVY; 
					break;
				case Node::RIGHT_HEAVY: 
					// local root is now right heavy 
					AVL_local_root->balance = Node::BALANCED; 
					// Overall height of local root remains the same 
					increase = false; 
					break;
				case Node::LEFT_HEAVY: 
					// local root is now critically unbalanced 
					rebalance_left(local_root); 
					increase = false; 
					break;
				} // End switch 
			} // End (if increase) 
			return return_value; 
		} // End (if item < local_root->data)
		if (item > local_root->data) 
		{
			bool return_value = insert(local_root->right, item);
			if (increase) //The right subtree was increased!
			{ //if the height is increased
				Node* AVL_local_root = dynamic_cast<Node*>(local_root);
				switch (AVL_local_root->balance) 
				{
				case Node::BALANCED: 
					// local root is now RIGHT heavy 
					AVL_local_root->balance = Node::RIGHT_HEAVY; 
					break;
				case Node::LEFT_HEAVY: 
					// local root is now LEFT heavy 
					AVL_local_root->balance = Node::BALANCED; 
					// Overall height of local root remains the same 
					increase = false; 
					break;
				case Node::RIGHT_HEAVY: 
					// local root is now critically unbalanced 
					//cout << "Do Rebalance Right, not impemented?" << endl;
					rebalance_right(local_root); 
					increase = false; 
					break;
				} // End switch 
			} // End (if increase) 
			return return_value; 
		} // End (if item > local_root->data)
		else 
		{ 
			increase = false; 
			return false; 
		}

	}

	void rebalance_left(Node*& local_root) 
	{
		// Cast local_root to an AVLNode pointer 
		Node* AVL_local_root = dynamic_cast<Node*>(local_root); 
		// Obtain reference to the left child
		Node* left_child = dynamic_cast<Node*>(local_root->left); 
		// See whether left-right-heavy 
		if (left_child->balance == Node::RIGHT_HEAVY) 
		{
			// Obtain a reference to the left-right child 
			Node* left_right_child = dynamic_cast<Node*>(left_child->right); 
			// Adjust the balances to be the new values after rotations are 
			// performed 
			if (left_right_child->balance == Node::LEFT_HEAVY) 
			{ 
				left_child->balance = Node::BALANCED; 
				left_right_child->balance = Node::BALANCED; 
				AVL_local_root->balance = Node::RIGHT_HEAVY; 
			} 
			else if (left_right_child->balance == Node::BALANCED)
			{
				left_child->balance = Node::BALANCED; 
				left_right_child->balance = Node::BALANCED; 
				AVL_local_root->balance = Node::BALANCED; 
			} 
			else 
			{ 
				left_child->balance = Node::LEFT_HEAVY; 
				left_right_child->balance = Node::BALANCED; 
				AVL_local_root->balance = Node::BALANCED; 
			} 
			// Perform left rotation 
			rotate_left(local_root->left); 
		}
		else 
		{ 
			// Left-Left case 
			/* In this case the left child (the new root) and the local root (new right child) will both be balanced after the rotation.*/ 
			left_child->balance = Node::BALANCED; 
			AVL_local_root->balance = Node::BALANCED;
		} // Finally rotate right 
		rotate_right(local_root); 
	}

	void rebalance_right(Node*& local_root) 
	{
		// Cast local_root to an AVLNode pointer 
		Node* AVL_local_root = dynamic_cast<Node*>(local_root); 
		// Obtain reference to the right child
		Node* right_child = dynamic_cast<Node*>(local_root->right); 
		// See whether right-left-heavy 
		if (right_child->balance == Node::LEFT_HEAVY) 
		{ 
			// Obtain a reference to the right-left child 
			Node* right_left_child = dynamic_cast<Node*>(right_child->left); 
			// Adjust the balances to be the new values after rotations are 
			// performed 
			if (right_left_child->balance == Node::RIGHT_HEAVY) 
			{ 
				right_child->balance = Node::BALANCED; 
				right_left_child->balance = Node::BALANCED; 
				AVL_local_root->balance = Node::LEFT_HEAVY; 
			} 
			else if (right_left_child->balance == Node::BALANCED)
			{
				right_child->balance = Node::BALANCED; 
				right_left_child->balance = Node::BALANCED; 
				AVL_local_root->balance = Node::BALANCED; 
			} 
			else 
			{ 
				right_child->balance = Node::RIGHT_HEAVY; 
				right_left_child->balance = Node::BALANCED; 
				AVL_local_root->balance = Node::BALANCED; 
			} 
			// Perform right rotation 
			rotate_right(local_root->right); 
		} 
		else 
		{ 
			// right-right case 
			/* In this case the right child (the new root) and the local root (new left child) will both be balanced after the rotation.*/ 
			right_child->balance = Node::BALANCED; 
			AVL_local_root->balance = Node::BALANCED;
		} // Finally rotate left 
		rotate_left(local_root); 
	}




};

template<typename T>
/** Output nodes at a given level */
bool AVL<T>::outLevel(Node* root, int level, stringstream& out) const
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
/** Return a level order traversal of a AVL as a string */
string AVL<T>::toString() const
{
	stringstream out;
	if (root == NULL) out << "empty";
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
bool AVL<T>::addNode(Node*& localRoot, const T& item)
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
bool AVL<T>::removeNode(Node*& localRoot, const T& item)
{
	if (localRoot == NULL)
	{ 
		return false; //It was not found, nothing is removed
		decrease = false;
	}

	if (item < localRoot->data)
	{
		bool returnValue = removeNode(localRoot->left, item);
		if (decrease) //if not removed, don't go through the craziness of trying to rebalance
		{

		}










		return returnValue;
	}
	else if (item > localRoot->data)
	{
		return removeNode(localRoot->right, item);
	}
	else if (item == localRoot->data)
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
		decrease = true;
		--size;
		return true;
	}
}

template<typename T>
//Replaces the parent Node for a root
void AVL<T>::replaceParent(Node*& oldRoot, Node*& localRoot) {
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
bool AVL<T>::inOrder(Node* root, stringstream& out) const
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


#endif // !AVL_H


//IF YOU EVER WANT TO IMPLIMENT, THESE ARE FAIRLY READY

/** These two functions to return DATA inside AVL, NOT using iterator */
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