#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
/*
 * Ali Aljaffer - CS3100
 * Database implementation using jsHash as a hash function
 * and psuedo-random probing.
 */
// There are three types of slots in a closed hash:
// Normal slots, empty (since start) slots, and emptyAfterRemovals (i.e. tombstones)
enum SlotType
{
	normalSlot,
	emptySinceStart,
	emptyAfterRemoval
};

// Each slot holds an integer key and an integer vector index.
// The integer index will be used as to find the record in the
// record store.

class Slot
{
private:
	int key;
	int index;
	SlotType type;

public:
	// The default constructor produces an empty slot.
	Slot()
	{
		key = -1;
		index = -1;
		type = emptySinceStart;
	}

	// This constructor uses an initialization list
	// See "member initialization" at: http://www.cplusplus.com/doc/tutorial/classes/
	Slot(int newKey, int newIndex)
		 : key(newKey), index(newIndex)
	{
		type = normalSlot;
	}

	// Place a key and an index into a slot, convert the type to normalSlot
	void load(int newKey, int newIndex)
	{
		key = newKey;
		index = newIndex;
		type = normalSlot;
	}

	// Convert a slot to a emptyAfterRemoval
	void kill()
	{
		type = emptyAfterRemoval;
	}

	// Get the integer key of a slot
	int getKey() const
	{
		return key;
	}

	// Get the index of a slot
	int getIndex() const
	{
		return index;
	}

	// Set the index of a slot to a new value
	void setIndex(int newIndex)
	{
		index = newIndex;
	}

	// Check if a slot is emptySinceStart
	bool isEmptySinceStart() const
	{
		return (type == emptySinceStart);
	}

	// Check if a slot is a normal slot
	bool isNormal() const
	{
		return (type == normalSlot);
	}

	// Check if a slot is a emptyAfterRemoval
	bool isEmptyAfterRemoval() const
	{
		return (type == emptyAfterRemoval);
	}

	// Check if a slot is empty
	bool isEmpty() const
	{
		return ((type == emptySinceStart) || (type == emptyAfterRemoval));
	}

	// Overload the << operator for printing slots
	friend ostream &operator<<(ostream &os, const Slot &me)
	{
		if (me.isEmptyAfterRemoval())
			os << "<<emptyAfterRemoval>>";
		else if (me.isEmptySinceStart())
			os << "<<Empty>>";
		else
			os << "Key: " << me.key << ", Index: " << me.index;
		return os;
	}

	// No destructor is needed as Slots don't use any dynamically
	// allocated memory
	~Slot()
	{
	}
};
