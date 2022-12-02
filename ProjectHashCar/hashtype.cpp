// Implementation file for hashtype.h

#include "hashtype.h"
#include <iostream>

HashType::HashType()
{
	numCollisions = 0;
	numItems = 0;
	size = MAX_ITEMS;
	info = new int[size];
	for (int i = 0; i < size; i++)
		info[i] = -1;
}

bool HashType::IsFull() const
{
	return (numItems == size);
}

int HashType::GetNumItems() const
{
	return numItems;
}

void HashType::MakeEmpty()
// Post: list is empty.
{
	numItems = 0;
	for (int i = 0; i < size; i++)
		info[i] = emptyItem;
}

//Updated IT via Dale 1/31/2019
void HashType::DeleteItem(int item)
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

int HashType::Hash(int item) const
// Post: Returns an integer between 0 and hash table size.
{
	return abs((item % size));
}

unsigned long int HashType::GetCollisions() const {
	return numCollisions;
}

// Actual implementation will depend on whether ID is a string, or int.
void HashType::InsertItem(int item)
// Post: item is stored in the array at position item.Hash()
//       or the next free spot.
{
	int location = Hash(item);

	while (info[location] != emptyItem) {
		location = (location + 1) % size;	// linear probing (Change method)
		numCollisions++;
	}

	info[location] = item;
	numItems++;
}

void HashType::RetrieveItem(int item, bool& found)
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

ostream& operator<<(ostream& out, const HashType& items) {
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
