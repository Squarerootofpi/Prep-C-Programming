#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListInterface.h"
#include <sstream>
//#include "Node.h"

template<typename T>
class LinkedList : public LinkedListInterface<T>
{
private:
	int numItems;

	struct Node
	{
	public:
		T thisData;
		Node* next;

		Node(const T& dataItem, Node* nextPtr = NULL)
		{
			thisData = dataItem;
			next = nextPtr;
			
		};
		~Node() {};
	};

	Node* head;
public:
	LinkedList() 
	{
		numItems = 0;
		head = nullptr;
		return;
	};
	~LinkedList() 
	{
		Node* destroyerPointer;

		while (head != nullptr)
		{
			destroyerPointer = head;
			head = head->next;
			delete destroyerPointer;

		}
	};
	virtual bool insertHead(T value) //insert at beginning of list
	{
		bool insertSuccess = false;
		if (numItems == 0)
		{
			Node* newNode = new Node(value);
			head = newNode;
			++numItems;
			return true;
		}
		
		Node* iterPointer = head;

		while (iterPointer != nullptr) //Loop checks iff data is same anywhere
		{
			if (iterPointer->thisData == value)
			{
				return false;
			} 
			if (iterPointer->next == nullptr) { break; }
			iterPointer = iterPointer->next;
		}
		
		 
		
		if (value == head->thisData)
		{
			return false;
		}
		else
		{
			Node* newNode = new Node(value);
			newNode->next = head;
			head = newNode; // Step 2
			++numItems;
			return true;
		}
		
		return insertSuccess;
	};

	virtual bool insertAfter(T matchNode, T node)
	{
		//find if duplicate or erroneous data
		if (numItems == 0)
		{
			return false;
		}

		Node* iterPointer = head;
		Node* matchPointer = nullptr;

		while (iterPointer != nullptr) //loop to find if data matches
		{
			if (iterPointer->thisData == matchNode) //Check if match
			{
				matchPointer = iterPointer;
			}
			if (iterPointer->thisData == node) //check if copy.
			{
				return false;
			}
			if (iterPointer->next == nullptr) { break; }
			iterPointer = iterPointer->next;
		}
		if (matchPointer != nullptr)
		{
			Node* newNode = new Node(node, matchPointer->next);
			matchPointer->next = newNode;
			++numItems;
			return true;
		}
		return false;
	};

	virtual std::string toString() const //toStrings all items with spaces in between.
	{
		
		std::ostringstream returnString; 
		returnString << " ";
		Node* iterPtrAtHead = head;
		if (numItems == 0)
		{
			returnString << "Empty";
		}

		while (iterPtrAtHead != nullptr)
		{
			returnString << (iterPtrAtHead->thisData);
			iterPtrAtHead = iterPtrAtHead->next;
			
			if (iterPtrAtHead != nullptr) 
			{
				returnString << " "; 
			}
		}
		returnString << std::endl;
		std::string finalString = returnString.str();
		return finalString;
	}; //Do I need these semicolons???
	virtual size_t size() const
	{
		return numItems;
	};
	virtual bool clear() //basically same as destructor, but doesn't delete list container
	{
		Node* destroyerPointer;

		while (head != nullptr) //head will end on nullptr, just as was constructed.
		{
			destroyerPointer = head;
			head = head->next;
			delete destroyerPointer;
		}
		numItems = 0; //number of items is 0 now.
		return true;
	};
	virtual bool remove(T value)
	{
		Node* iterNodePtr = head;
		Node* behindPtr = head;

		if (numItems == 0) { return false; }

		if (value == iterNodePtr->thisData) //it is head
		{
			head = head->next;
			delete iterNodePtr;
			--numItems;
			return true;
		}

		while (iterNodePtr != nullptr)
		{
			if (iterNodePtr->thisData == value)
			{
				behindPtr->next = iterNodePtr->next;
				delete iterNodePtr;
				--numItems;
				return true;
			}
			else
			{
				behindPtr = iterNodePtr;
				iterNodePtr = iterNodePtr->next;
			}
		}
		return false; //It didn't find it.
	};
	virtual bool insertTail(T value)
	{
		if (numItems == 0)
		{
			Node* newNode = new Node(value);
			head = newNode;
			++numItems;
			return true;
		}

		Node* iterPointer = head;

		while (iterPointer != nullptr)
		{
			if (iterPointer->thisData == value) { return false; } //If data is same
			if (iterPointer->next == nullptr) { break; }
			iterPointer = iterPointer->next;
		}

		Node* newNode = new Node(value);
		iterPointer->next = newNode;
		++numItems;
		return true;
	};
	virtual T& at(size_t index)
	{
		Node* iterNodePtr = nullptr;
		int counter = 0;
		if (counter > index || numItems <= index) 
		{
			return iterNodePtr->thisData; //throws exception in main;
		}
		iterNodePtr = head;
		while (counter <= index)
		{
			iterNodePtr = iterNodePtr->next;
			++counter;
		}
		return iterNodePtr->thisData;
	};
}; 
#endif // !LINKEDLIST_H
