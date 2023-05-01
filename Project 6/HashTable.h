#pragma once
#include "Slot.h"
#include "Record.h"
#include "hashfunction.h"
#define MAXHASH 20
/*
 * Ali Aljaffer - CS3100
 * Database implementation using jsHash as a hash function
 * and psuedo-random probing.
 */
class HashTable
{
private:
   int offsets[MAXHASH - 1];
   Slot slots[MAXHASH];
   // Using slotsOccupied to keep the number of slots being occupied. I think this would be more beneficial by being O(1) access if we had a much larger hash table, because searching through the slots everytime alpha is called will be expensive. So for our MAXHASH = 20 case, this doesn't reallly do much but it's nice to have
   int slotsOccupied;

public:
   HashTable();
   ~HashTable();
   int getSlotsOccupied() const;
   void setSlotsOccupied(int newSlotsNumber);
   bool insert(int key, int index, int &collisions);
   bool remove(int key);
   bool find(int key, int &index, int &collisions);
   bool findInHashTable(int key, int &index) const;
   bool adjustSlotIndex(int slotIndex, int newStoredValue);
   float alpha();
   friend ostream &operator<<(ostream &, const HashTable &);
};