
#ifndef QS_H
#define QS_H

#define TEST_MY_PIVOT right -

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <istream>

#include "QSInterface.h"

using std::string;
using std::stringstream;
using std::getline;
using std::cin;
using std::endl;
using std::cout;

template <typename T>
class QS :
	public QSInterface<T>
{
private:
	size_t currentCapacity;
	size_t numElements;
	T* anArray;
	size_t comparisons;
	size_t exchanges;
public:
	QS(const size_t capacity = 0) : numElements(0), currentCapacity(capacity)
	{}
	virtual ~QS()
	{
		deleteArray();
	}

	/** Dynamically allocate an initial array to the QuickSort class. */
	virtual bool createArray(size_t capacity)
	{
		if (currentCapacity != 0)
		{
			deleteArray();
		}
		//anArray = (T*)malloc(capacity * sizeof(T));
		anArray = new T[capacity];
		cout << "NewArray" << endl;
		currentCapacity = capacity;
		numElements = 0;
		return true;
	}

	/** Deletes the Array */
	bool deleteArray()
	{
		delete[] anArray;
		cout << "DeletingArray" << endl;
		currentCapacity = 0;
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element)
	{
		if (numElements == currentCapacity)
		{
			doubleCapacity();
		}
		anArray[numElements] = element;
		++numElements;
		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right)
	{
		/*if (right - left <= 0) //Base Cases: if the indexes are the same.
		{
			return true; 
		}*/
		if (right - left < 2) //There are only 3 values it sorted, and the median already sorted them
		{
			return true;
		}
		size_t middle = medianOfThree(left, right);
		size_t pivot = partition(left, right, middle); //Calling partition, while sorting and selecting pivot
		sort(left, pivot);
		sort(pivot + 1, right);
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll()
	{
		size_t middle = medianOfThree(0, size());
		size_t pivot = partition(0, size(), middle); //Calling partition, while sorting and selecting pivot
		sort(0, pivot);
		sort(pivot + 1, size());
		return true;
	}

	/** Removes all items from the QuickSort array. */
	virtual bool clear()
	{
		numElements = 0;
		return true;
	}

	bool doubleCapacity()
	{
		size_t new_capacity = 2 * currentCapacity;
		T* new_data = new T[new_capacity];
		size_t j = 0;
		for (size_t i = 0; i < numElements; i++)
		{
			new_data[i] = anArray[j];
			++j;
		}
		//rearIndex = rearIndex; //
		currentCapacity = new_capacity;
		std::swap(anArray, new_data);

		delete[] new_data;
		return true;
	}

	/** Return size of the QuickSort array. */
	virtual size_t capacity() const
	{
		return currentCapacity;
	}

	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const
	{
		return numElements;
	}

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	virtual int medianOfThree(size_t left, size_t right)
	{
		if (left >= right || right > numElements)
		{
			return -1;
		}
		size_t midIndex = (left + right) / 2;
		bubbleSort3(left, midIndex, right);
		return midIndex;
	}

	//BUBBLE SORT WITH 2 VALUES: NOT USED IN THIS LAB
	void bubbleSort2(size_t first, size_t last)
	{
		if (anArray[first] > anArray[last])
		{
			std::swap(anArray[first], anArray[last]);
		}
	}

	/** Returns the statistics of comparisons for lab thus far etc */
	string stats()
	{
		stringstream ss;
		ss << comparisons << "," << exchanges;
		return ss.str();
	}

	/** medianofThree Bubble Sort */ //NOT USED IN THIS LAB
	void bubbleSort3(size_t first, size_t middle, size_t last)
	{
		/* Perform bubble sort on table[first], table[middle], table[last - 1]. */
		if (anArray[middle] < anArray[first])
		{
			std::swap(anArray[first], anArray[middle]);
			++exchanges;
		}
		// Assert: table[first] <= table[middle]. 
		if (anArray[last - 1] < anArray[middle])
		{
			std::swap(anArray[middle], anArray[last - 1]);
			++exchanges;
		}
		// Assert: table[last] is the largest value of the three. 
		if (anArray[middle] < anArray[first])
		{
			std::swap(anArray[first], anArray[middle]);
			++exchanges;
		}
		comparisons += 3;
		// Assert: table[first] <= table[middle] <= table[last - 1]. 
	}

	/** medianofThree Bubble Sort */ //NOT USED IN THIS LAB
	void bubbleSort3WithTwo(size_t first, size_t last)
	{
		size_t middle = first + (last - first) / 2;
		/* Perform bubble sort on table[first], table[middle], table[last - 1]. */
		if (anArray[middle] < anArray[first])
		{
			std::swap(anArray[first], anArray[middle]);
		}
		// Assert: table[first] <= table[middle]. 
		if (anArray[last - 1] < anArray[middle])
		{
			std::swap(anArray[middle], anArray[last - 1]);
		}
		// Assert: table[last] is the largest value of the three. 
		if (anArray[middle] < anArray[first])
		{
			std::swap(anArray[first], anArray[middle]);
		}
		// Assert: table[first] <= table[middle] <= table[last - 1]. 
	}
	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
					2) if any of the given indexes are out of bounds,
					3) if the left index is not less than the right index.
	*/
	virtual int partition(size_t left, size_t right, size_t pivotIndex)
	{
		if (size() == 0 || left >= right || left < 0
			|| right > numElements || pivotIndex <= left
			|| pivotIndex >= right)
		{
			return -1;
		}
		/* Put the median of table[first], table[middle], table[last - 1] into
		//table[first], and use this value as the pivot. */
		// Swap first element with middle element. 
		std::swap(anArray[left], anArray[pivotIndex]);
		// Continue with rest of partition function in Listing 10.10. 
		// Start up and down at either end of the sequence. 
		// The first table element is the pivot value. 
		size_t up = left + 1;
		size_t down = right - 1;
		do {
			/* Invariant: All items in table[first] through table[up - 1] <= table[first]
			All items in table[down + 1] through table[last - 1] > table[first] */
			while ((up != right - 1) && (anArray[left] >= anArray[up])) //up shouldn't pass end, and move up when pivot should be bigger than up's value
			{
				++up;
			}
			// Assert: up equals last - 1 or table[up] > table[first]. 
			while (anArray[left] < anArray[down]) //move down while the down value is less than the pivot
			{
				--down;
			}
			// Assert: down equals first or table[down] <= table[first]. 
			if (up < down)
			{
				// if up is to the left of down, 
				// Exchange table[up] and table[down]. 
				std::swap(anArray[up], anArray[down]);
				++exchanges;
			}
		} while (up < down); // Repeat while up is left of down. 
		// Exchange table[first] and table[down] thus putting the 

		std::swap(anArray[left], anArray[down]);
		++exchanges;
		return down;
	}


	/** ostream Operater Definition */
	friend std::ostream& operator<< (std::ostream& os, const QS<T>& anArray)
	{
		os << anArray.toString();
		return os;
	}

	/** @return: comma delimited string representation of the array. */
	virtual std::string toString() const
	{
		if (numElements == 0)
		{
			return string("Empty");
		}
		stringstream ss;
		ss << anArray[0];
		for (int i = 1; i < numElements; ++i)
		{
			ss << "," << anArray[i];
		}

		return ss.str();
	}



};

#endif // !QS_H