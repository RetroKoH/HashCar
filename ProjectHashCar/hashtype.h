#ifndef HASHTYPE_H
#define HASHTYPE_H

// Author: Ivan Temesvari
// Date 4/10/2019

#include <string>
using namespace std;
const int MAX_ITEMS = 20;

class HashType
{
public:
	// Constructor
	HashType();
	
	// Member Functions
	void MakeEmpty();
	bool IsFull() const;
	int GetNumItems() const;
	void RetrieveItem(int, bool&);
	void InsertItem(int);
	void DeleteItem(int);
	int Hash(int) const;
	unsigned long int GetCollisions() const;
	// Overloaded Operator
	friend ostream& operator<<(ostream&, const HashType&);

private:
//	int a; // the value used for a polynomial hash function (Only used if we utilize strings for ID
	int numItems;
	int size;
	int* info;
	int emptyItem = -1; // The empty value
	unsigned long int numCollisions;
};
#endif
