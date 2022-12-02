// Implementation file for hashtype.h

#include "hashtype.h"
#include <iostream>

template <class ItemType>
HashType<ItemType>::HashType()
{
	numCollisions = 0;
	numItems = 0;
	size = MAX_ITEMS;
	a = 33;				// The former constant file will be the default
	info = new ItemType[size];
	for (int i = 0; i < size; i++)
		info[i] = emptyItem;
}

template <class ItemType>
HashType<ItemType>::HashType(int s, int factor) {
	numItems = 0;
	numCollisions = 0;
	size = s;
	a = factor;
	info = new ItemType[size];
	for (int i = 0; i < size; i++) {
		info[i] = emptyItem;
	}
}

template <class ItemType>
bool HashType<ItemType>::IsFull() const
{
	return (numItems == size);
}

template <class ItemType>
int HashType<ItemType>::GetNumItems() const
{
	return numItems;
}

template <class ItemType>
void HashType<ItemType>::MakeEmpty()
// Post: list is empty.
{
	numItems = 0;
	for (int i = 0; i < size; i++)
		info[i] = emptyItem;
}

//Updated IT via Dale 1/31/2019
template <class ItemType>
void HashType<ItemType>::DeleteItem(ItemType item)
{
	int location = 0;
	int startLoc;

	startLoc = Hash(item);
	location = startLoc;
	do
	{
		if (info[location] == item || info[location] == emptyItem) {
			info[location] = -1;
			numItems--;
			return;
		}
		else
			location = (location + 1) % size;
	} while (location != startLoc);

	if (location == startLoc) {
		cout << "Item to delete not found." << endl;
	}
}

template <class ItemType>
int HashType<ItemType>::Hash(string item) const
// Post: Returns an integer between 0 and hash table size.
{
	int hash = 0;
	int n = item.length();
	for (int i = 0; i < n; i++)
		hash = a * hash + item[i];

	// prevent overflow negative values as an index.
	return abs(hash % size);
}

template <class ItemType>
unsigned long int HashType<ItemType>::GetCollisions() const {
	return numCollisions;
}

template <class ItemType>
void HashType<ItemType>::InsertItemLinear(ItemType item)
// Post: item is stored in the array at position item.Hash()
//       or the next free spot.
{
	int location = Hash(item);

	while (info[location] != emptyItem) {
		location = (location + 1) % size;	// linear probing
		numCollisions++;
	}

	info[location] = item;
	numItems++;
}

template <class ItemType>
void HashType<ItemType>::InsertItemQuadratic(ItemType item)
// Post: item is stored in the array at position item.Hash()
//       or the next free spot.
{
	int hashVal = Hash(item);
	int location = hashVal;
	int i = 1;

	while (info[location] != emptyItem) {
		location = (hashVal + i * i) % size;   // quadratic probing
		numCollisions++;
		i++;
	}

	info[location] = item;
	numItems++;
}

template <class ItemType>
void HashType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
	int location;
	int startLoc;
	bool moreToSearch = true;

	startLoc = Hash(item);
	location = startLoc;
	do
	{
		if (info[location] == item || info[location] == emptyItem)
			moreToSearch = false;
		else
			location = (location + 1) % size;
	} while (location != startLoc && moreToSearch);
	found = (info[location] == item);
	if (found)
		item = info[location];
}

template <class ItemType>
ostream& operator<<(ostream& out, const HashType<ItemType>& items) {
	out << "[ ";
	for (int i = 0; i < items.size; i++) {
		if (i == 0)
			out << items.info[i];
		else
			out << ", " << items.info[i];
	}
	out << " ]" << endl;
	return out;
}
