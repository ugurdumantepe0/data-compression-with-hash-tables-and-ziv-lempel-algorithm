#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>





using namespace std;

template <typename Key, typename Value>
class HashTable
{


public:

	enum EntryType { ACTIVE, EMPTY, DELETED };

	~HashTable() {
	}

private:
	struct HashEntry
	{
		Key key;
		Value value;
		EntryType info;
		HashEntry(const Key & e = Key{}, const Value & v = Value{}, EntryType i = EMPTY)
			: key{ e }, value(v), info{ i } { }
		HashEntry(Key && e, Value && v, EntryType i = EMPTY)
			: key{ move(e) }, value(v), info{ i } { }
	};
	const size_t arraySize;
	vector<HashEntry> array;

	// check if this element is active, or deleted/empty.
	bool isActive(size_t currentPos) const
	{
		return array[currentPos].info == ACTIVE;
	}


	// find position of an element
	size_t findPos(const Key & x) {

		probs = 0;
		size_t currentPos = myhash(x);
		while ((array[currentPos].info == ACTIVE && array[currentPos].key != x))
		{

			probs++;
			currentPos += 1;
			if (currentPos >= arraySize)
				currentPos = 0;

			if (probs >= arraySize) {
				break;
			}
		}

		return currentPos;

	}

	// find position of an element for removal
	bool findPosForRemove(const Key & x, size_t & currentPos) {

		probs = 0;
		currentPos = myhash(x);
		bool succeed = true;
		while ((array[currentPos].info != EMPTY && array[currentPos].key != x))
		{
			probs++;
			currentPos += 1;
			if (currentPos >= arraySize)
				currentPos = 0;
			if (probs >= arraySize) {
				succeed = false;
				break;
			}
		}
		if (array[currentPos].key == x&&array[currentPos].info == ACTIVE) //this line is changed{
			succeed = true;
		else
			succeed = false;

		return succeed;

	}

	// hash function
	// to use this in a custom class, template specialization is needed.
	// i.e. hash<CustomClass>
	// it supports all the built-in types in c++ by default
	size_t myhash(const Key & x) const {
		return hash<Key>{}(x) % arraySize;
	}

public:

	size_t totalkeys;
	size_t probs;


	explicit HashTable(int size) :array(size), arraySize(size)
	{
		makeEmpty();
	}

	// check if key exists
	bool keyExists(const Key & x)
	{

		size_t currentPos = findPos(x);
		if (probs<arraySize&&isActive(currentPos)) {
			return true;
		}
		else {
			return false;
		}

	}

	// clear the hash by setting their info = Empty
	void makeEmpty() {
		totalkeys = 0;
		for (auto & entry : array)
			entry.info = EMPTY;

	}


	// insert key,value pair
	bool insert(const Key & k, const Value &v) {

		size_t currentPos = findPos(k);
		if (probs<arraySize && !isActive(currentPos)) {
			array[currentPos].key = k;
			array[currentPos].value = v;
			array[currentPos].info = ACTIVE;
			++totalkeys;
			return true;
		}
		else {
			return false;

		}

	}

	// remove the given element with key 
	bool remove(const Key & x)
	{

		size_t currentPos;
		bool succeed = findPosForRemove(x, currentPos);
		if (succeed) {
			totalkeys--;
			array[currentPos].info = DELETED;
			return true;
		}
		else {
			return false;
		}


	}


	// print results for debugging
	void printResults() {

		for (auto &elem : array) {
			if (elem.info == ACTIVE)
				cout << elem.key << " " << elem.value << endl;
		}
		cout << endl;
	}

	// find the element inserted, this is for debugging
	int getCount() {

		int count = 0;
		for (auto &elem : array) {
			if (elem.info == ACTIVE)
				count++;
		}

		return count;
	}

	// get the value of a given key
	Value getValueForKey(Key k) {
		size_t currentPos = findPos(k); //this line is changed
		if (probs < arraySize&&isActive(currentPos))
			return array[currentPos].value;
		else {
			string arg = "key doesn't exist ";
			arg.append(to_string(stoi("" + k)));
			throw invalid_argument(arg);
		}
	}
};


#endif /* HashTable_hpp */
