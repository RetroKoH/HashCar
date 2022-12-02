#ifndef HASHTYPE_H
#define HASHTYPE_H

// Author: Ivan Temesvari
// Date 4/10/2019

#include <string>
using namespace std;
const int MAX_ITEMS = 11;

template <class ItemType>
class HashType
{
public:
	// Constructors
	HashType();
	HashType(int, int);

	// Member Functions
	void MakeEmpty();
	bool IsFull() const;
	int GetNumItems() const;
	void RetrieveItem(ItemType&, bool&);
	void InsertItemLinear(ItemType);
	void InsertItemQuadratic(ItemType);
	void DeleteItem(ItemType);
	int Hash(string) const;
	unsigned long int GetCollisions() const;
	// Overloaded Operator
	friend ostream& operator<<(ostream&, const HashType<ItemType>&);

private:
	int a; // the value used for a polynomial hash function
	int numItems;
	int size;
	ItemType* info;
	ItemType emptyItem = ""; // The empty string
	unsigned long int numCollisions;
};
#endif
