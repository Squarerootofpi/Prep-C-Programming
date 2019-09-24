#ifndef HASHMAP_H
#define HASHMAP_H
#include "HashMapInterface.h"
#include "BST.h"
#include <utility>
using std::pair;

template <typename K, typename V>

class HashMap :
	public HashMapInterface<K, V>
{
private:
	size_t capacity;
	pair<K, V>* myPairs;
	size_t numPairs = 0;
	string stringNumPairs;
	
public:
	HashMap<K, V>() : myPairs(new pair<K, V>[DEFAULT_MAP_HASH_TABLE_SIZE]), capacity(DEFAULT_MAP_HASH_TABLE_SIZE) 
	{
		//stringstream ss;
		//ss << numPairs;
		//stringNumPairs = ss.str();
	}

	virtual ~HashMap()
	{
		clear();
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key)
	{
		long long hash = key[0];
		for (size_t i = 1; i < key.length(); ++i)
		{
			hash = hash * HASH_CONSTANT + key[i];
		}
		hash %= capacity;
		//cout << endl << "Key=" << key << ", hash=" << hash;
		int k = 1;
		while (1)
		{
			if (myPairs[hash].first.length())
			{
				if (myPairs[hash].first == key) break;
				hash = (hash + k) % capacity;
				k += 2;
				continue;
			}
			myPairs[hash].first = key;
			++numPairs;
			stringNumPairs = convertInt(numPairs);
			break;
		}
		return myPairs[hash].second;
	}

	/** @return: the number of elements that match the key in the Map. */
	virtual size_t count(const K& key)
	{
		long long hash = key[0];
		for (size_t i = 1; i < key.length(); ++i)
		{
			hash = hash * HASH_CONSTANT + key[i];
		}
		hash %= capacity;
		//cout << endl << "Key=" << key << ", hash=" << hash;
		int k = 1;
		//iterate through hashes. If you don't find it, know it's not in there, so return count = 0
		while (myPairs[hash].first.length())
		{
			if (myPairs[hash].first == key) return 1;
			hash = (hash + k) % capacity;
			k += 2;
		}
		return 0;
	}

	/** Removes all items from the Map. */
	virtual void clear()
	{
		delete [] myPairs;
		return;
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size() const
	{
		return numPairs;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size() const
	{
		return DEFAULT_MAP_HASH_TABLE_SIZE;
	}

	/*	string numPairsToString*/
	string convertInt(int number)
	{
		if (number == 0)
		{
			return "0";
		}
		string temp = "";
		string returnvalue = "";
		while (number > 0)
		{
			temp += number % 10 + 48;
			number /= 10;
		}
		for (int i = 0; i < temp.length(); i++)
			returnvalue += temp[temp.length() - i - 1];
		return returnvalue;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString() const
	{
		string str = stringNumPairs;
		
		stringstream os(str);
		//string str = "";
		//str = size();
		//nothing
		//testline
		//testline
		os << str;
		os << "/" << capacity;
		for (size_t i = 0; i < capacity; ++i)
		{
			if (myPairs[i].first.length())
			{
				os << endl << "  [" << i << ":";
				os << myPairs[i].first << "->";

				os << myPairs[i].second << "]";
			}
		}
		os << endl;
		return os.str();
	}
};

#endif