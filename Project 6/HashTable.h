#pragma once
#include "Slot.h"
#include "Record.h"
#include "hashfunction.h"
#define MAXHASH 20

class HashTable
{
private:
   int offsets[MAXHASH - 1];
   Slot slots[MAXHASH];
   int slotsOccupied;

public:
   HashTable();
   ~HashTable();
   int getSlotsOccupied() const;
   bool insert(int key, int index, int &collisions);
   bool remove(int key);
   bool find(int key, int &index, int &collisions);
   bool findInHashTable(int key, int &index) const;
   bool adjustSlotIndex(int slotIndex, int newStoredValue);
   float alpha();
   friend ostream &operator<<(ostream &, const HashTable &);
};