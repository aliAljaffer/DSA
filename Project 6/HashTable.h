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

public:
   HashTable();
   ~HashTable();
   bool insert(int key, int index, int &collisions);
   bool remove(int key);
   bool find(int key, int &index, int &collisions);
   float alpha();
   friend ostream &operator<<(ostream &, const HashTable &);
   bool probe(int key, int &collisions);
};