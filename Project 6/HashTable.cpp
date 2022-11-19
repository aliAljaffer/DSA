#include "HashTable.h"
#include <algorithm>
// HashTable ->
HashTable::HashTable()
{
   for (int i = 0; i < MAXHASH; i++)
   {
      slots[i] = Slot();
      if (i < MAXHASH - 1)
         offsets[i] = i + 1;
   }
   random_shuffle(std::begin(offsets), std::end(offsets));
}

HashTable::~HashTable()
{
}

bool HashTable::insert(int key, int index, int &collisions)
{
   collisions = 0;
   int homePosition = jsHash(key) % MAXHASH;
   int probe = homePosition;
   while (!slots[probe].isEmpty() && collisions < MAXHASH - 1)
   {
      if (slots[probe].getKey() == key)
         return false;
      probe = (homePosition + offsets[collisions]) % MAXHASH;
      collisions++;
   }
   slots[probe].load(key, index); // use setters
   return false;
}

bool HashTable::probe(int key, int &collisions)
{
}