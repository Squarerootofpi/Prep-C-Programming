#ifndef SET_H
#define SET_H
#include "SetInterface.h"
#include "BST.h"

template<typename T>
class Set :
	public SetInterface<T>
{
private:

	BST<T> setBST;
public:
	Set()
	{

	}
	virtual ~Set()
	{
		cout << "~set" << endl;
		clear();
	}
	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value.
		@return: pair.first = pointer to item
				 pair.second = true if successfully inserted, else false. */
				 //virtual Pair<T*, bool> insert(const T& item) = 0;
	virtual bool insert(const T& item)
	{
		return(setBST.addNode(item));
	}

	/** Removes all items from the set. */
	virtual void clear()
	{
		setBST.clearTree();
		return;
	}

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const
	{
		return setBST.getSize();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item)
	{
		T tempItem = item; 
		if (setBST.find(tempItem))
		{
			return 1;
		}
		return 0;
	}

	/** @return: string representation of items in Set. */
	virtual std::string toString() const
	{
		return setBST.inOrderToString();
	}
	friend std::ostream& operator<<(std::ostream& os, const Set<T>& set)
	{
		os << set.toString();
		return os;
	}
	/*friend ostream& operator<< (ostream& os, const Iterator& iter)
	{
		os << iter.toString();
		return os;
	}*/
};

#endif 