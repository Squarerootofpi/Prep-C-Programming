#ifndef MYARRAY_H
#define MYARRAY_H
#define MAX_ARRAY_SIZE	1000

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

template<typename T>
class MyArray
{
private:
	size_t sizeOfArray;
	T* anArray;
public:
	MyArray(const size_t maxSize) : sizeOfArray(0) //Constuctor (no default)
	{
		anArray = (T*)malloc(maxSize * sizeof(T));
	}
	~MyArray() //Destructor, deallocate malloc
	{
		free(anArray); 
	}
	void push_back(T item) //Adds item to array
	{
		anArray[sizeOfArray++] = item;
	}
	//This should print whole array, output toString with <<
	friend ostream& operator<< (ostream& os, const MyArray<T>& myArray)
	{
		os << myArray.toString();
		return os;
	}

	class Iterator
	{
	private:
		size_t size;
		size_t indexAt;
		T* arrayPtr;
	public:
		Iterator(T* array, size_t indexAt, size_t size) //Constructor
		{
			this->indexAt = indexAt;
			arrayPtr = array;
			this->size = size;
		}
		~Iterator() {} //Destructor
		Iterator& operator++() //PreIncrement Operator
		{
			++indexAt;
			return *this;
		}
		Iterator operator++(int) //Postdecrement Operator
		{
			Iterator temp(*this);
			++indexAt;
			return temp;
		}
		/*Iterator& operator--() //PreDecrement Operator
		{
			--indexAt;
			return *this;
		}*/
		T operator[](size_t i) const //"Bracket" Operator
		{
			arrayPtr[i];
		}
		T& operator*() const //Dereferencing Operator
		{
			return arrayPtr[indexAt];
		}
		/*!= is lefthandside, operates on the thing on the right*/ /*other is Righthandside, is operated on*/
		bool operator!=(const Iterator& other) const //NotEquals Operator
		{
			return (this->indexAt != other.indexAt);
		}
		string toString() const //ToString. 
		{
			ostringstream oString;
			oString << "size=" << this->size << " index=" << this->indexAt << endl;
			string returnString = oString.str();
			return returnString;
		} //Return beginning and end of array...
		friend ostream& operator<< (ostream& os, const Iterator& iter)
		{
			os << iter.toString();
			return os;
		}
	};

	Iterator begin()
	{
		return MyArray::Iterator(anArray, 0, sizeOfArray); //Returns an iterator pointing at the beginning.
	}
	Iterator end()
	{
		return MyArray::Iterator(anArray, sizeOfArray, sizeOfArray);  //Returns an iterator pointing at the end.
	}
	string toString() const  //Tostring for MyArray
	{
		ostringstream oString;
		for (int i = 0; i < sizeOfArray; ++i)
		{
			if ((i % 10) == 0) { oString << endl; }
			oString << anArray[i] << " ";
		}
		string returnString = oString.str();
		return returnString;
	}
};
#endif // MYARRAY_H

