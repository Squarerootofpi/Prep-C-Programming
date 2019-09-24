#ifndef DEQUE_H
#define DEQUE_H

#define DEFAULT_CAPACITY 4

#include "DequeInterface.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <istream>

using std::endl;
using std::cout;
using std::string;
using std::stringstream;

template<typename T>
class Deque : public DequeInterface<T>
{
private:
	size_t capacity;
	size_t numItems;
	size_t frontIndex;
	size_t rearIndex;
	T* theData;

public: //Remember to delete the commented portions of DequeInterface as well!
	Deque() : capacity(DEFAULT_CAPACITY), rearIndex(DEFAULT_CAPACITY - 1), 
		frontIndex(0), numItems(0), theData(new T[DEFAULT_CAPACITY]) {}

	~Deque() 
	{
		delete[] theData;
	}

	/** Insert item at front of deque */
	virtual void push_front(const T& value)
	{
		if (numItems == capacity)
		{
			reallocate();
		}
		numItems++;
		frontIndex = (frontIndex - 1) % capacity; //yes, this works with size_t
		theData[frontIndex] = value;
	}

	/** Insert item at rear of deque */
	virtual void push_back(const T& value) //pretty good
	{
		if (numItems == capacity)
		{
			reallocate();
		}
		numItems++;
		rearIndex = (rearIndex + 1) % capacity;
		theData[rearIndex] = value;
	}


	/** Remove the front item of the deque */
	virtual void pop_front(void) //Pretty good
	{
		frontIndex = (frontIndex + 1) % capacity;
		numItems--;
	}


	/** Remove the rear item of the deque */
	virtual void pop_back(void)
	{
		
		rearIndex = (rearIndex -1) % capacity; //yes, this works with size_t
		numItems--;
	}

	/** Return the front item of the deque (Do not remove) */
	virtual T& front(void)
	{
		return theData[frontIndex];
	}

	/** Return the rear item of the deque (Do not remove) */
	virtual T& back(void)
	{
		return theData[rearIndex];
	}

	/** Return the number of items in the deque */
	virtual size_t size(void) const
	{
		return numItems;
	}

	/** Return the current capacity of the array */
	size_t maxCapacity()
	{
		return capacity;
	}

	/** Return true if deque is empty */
	virtual bool empty(void) const
	{
		if (numItems == 0) return true;
		return false;
	}

	/** Return item in deque at index (0 based) */
	virtual T& at(size_t index) 
	{
		return theData[(index + frontIndex) % capacity];
	}
	/** Returns a reference to an item in the deque. */
	//T& operator[](size_t i) not be necessary!
	


	/** Return the deque items */
	virtual std::string toString(void) const
	{
		std::string returnString;
		std::ostringstream oss;
		for (int i = 0; i < numItems; ++i)
		{
			oss << " " << theData[(i + frontIndex) % capacity];
		}
		returnString = oss.str();
		return returnString;
	}

	/** Reallocate memory so size can grow, etc. */
	void reallocate()
	{
		size_t new_capacity = 2 * capacity;
		T* new_data = new T[new_capacity];
		size_t j = frontIndex;
		for (size_t i = 0; i < numItems; i++)
		{
			new_data[i] = theData[j];
			j = (j + 1) % capacity;
		}
		frontIndex = 0;
		//rearIndex = rearIndex; //
		rearIndex = (numItems - 1);
		capacity = new_capacity;
		std::swap(theData, new_data);

		delete[] new_data; //Deletes the old data, since they have been swapped and reallocated
	}
	void errorTopPop() //Not used, but useful for later if want to make deque by itself
	{
		if (empty())
		{
			throw std::string("No way to see that! None deleted or seen");
		}
	}

};

#endif // !DEQUE_H
