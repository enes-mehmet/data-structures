#pragma once
#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;



bool isPrime(int n)
{
	// Corner cases
	if (n <= 1)  return false;
	if (n <= 3)  return true;

	// This is checked so that we can skip 
	// middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0) return false;

	for (int i = 5; i * i <= n; i = i + 6)
		if (n % i == 0 || n % (i + 2) == 0)
			return false;

	return true;
}

int nextPrime(int N)
{

	// Base case
	if (N <= 1)
		return 2;

	int prime = N;
	bool found = false;

	// Loop continuously until isPrime returns
	// true for a number greater than n
	while (!found) {
		prime++;

		if (isPrime(prime))
			found = true;
	}

	return prime;
}

template <class HashedObj>
class HashTable
{
public:
	template <class HashedObj>
	HashTable(const HashedObj& notFound, int size) : ITEM_NOT_FOUND(notFound), array(nextPrime(size))
	{
		makeEmpty();
	}
	HashTable(const HashTable& rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
		array(rhs.array), currentSize(rhs.currentSize) { }

	template <class HashedObj>
	void remove(const HashedObj& x)
	{
		int currentPos = findPos(x);
		if (isActive(currentPos))
			array[currentPos].info = DELETED;
	}

	template <class HashedObj>
	const HashedObj& find(const HashedObj& x)const
	{
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return array[currentPos].element;

		return ITEM_NOT_FOUND;
	}

	void makeEmpty()
	{
		currentSize = 0;
		for (unsigned int i = 0; i < array.size(); i++)
			array[i].info = EMPTY;
	}

	template <class HashedObj>
	bool insert(const HashedObj& x)
	{
		// Insert x as active
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return false;
		array[currentPos] = HashEntry(x, ACTIVE);

		// enlarge the hash table if necessary 
		if (++currentSize >= (array.size()*2) / 3) {
			rehash();
			return true;
		}
		return false;
	}

	const double loadFactor() const
	{
		return currentSize/double(array.capacity());
	}

	int size() const
	{
		return currentSize;
	}

	int capacity() const
	{
		return array.capacity();
	}

	template <class HashedObj>
	HashedObj* findPosition( HashedObj& x)
	{
		int currentPos = findPos(x);
		if(array[currentPos].info != ACTIVE)
			return NULL;
		return &(array[currentPos].element);
	}



	//const HashTable& operator=(const HashTable& rhs);

	enum EntryType { ACTIVE, EMPTY, DELETED };



private:

	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj(),
			EntryType i = EMPTY)
			: element(e), info(i) { }
	};



	vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

	void rehash()
	{
		vector<HashEntry> oldArray = array;
		// Create new double-sized, empty table
		array.resize(nextPrime(2 * oldArray.size()));
		for (int j = 0; j < array.size(); j++)
			array[j].info = EMPTY;

		// Copy table over
		currentSize = 0;
		for (int i = 0; i < oldArray.size(); i++)
			if (oldArray[i].info == ACTIVE)
				insert(oldArray[i].element);
	}

	template <class HashedObj>
	int hash(const HashedObj& key, int tableSize)const
	{
		string keyStr = key.key();
		int hashVal = 0;

		for (int i = 0; i < keyStr.length(); i++)
			hashVal = 37 * hashVal + keyStr[i];

		hashVal = hashVal % tableSize;

		if (hashVal < 0)
			hashVal = hashVal + tableSize;

		return(hashVal);
	}


	template <class HashedObj>
	int findPos(const HashedObj& x)const
	{
		int collisionNum = 0;
		int currentPos = hash(x, array.size());

		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x)
		{
			currentPos += pow(++collisionNum, 2);  //add the difference
			if (currentPos >= array.size())              // perform the mod
				currentPos -= array.size();
		}
		return currentPos;
	}

	bool isActive(int currentPos) const
	{
		return array[currentPos].info == ACTIVE;
	}
};

#endif
