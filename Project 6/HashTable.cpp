#include "HashTable.h"
#include <algorithm>
HashTable::HashTable()
{
   for (int i = 0; i < MAXHASH; i++)
   {
      slots[i] = new Slot();
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
   int homePosition = jsHash(key) % MAXHASH;
   int probe = homePosition;
   while (!slots[probe]->isEmpty() && collisions < MAXHASH - 1)
   {
      if (slots[probe]->getKey() == key)
         return false;
      probe = (homePosition + offsets[collisions]) % MAXHASH;
      cout << to_string(probe) << endl;
      collisions++;
   }
   slots[probe] = new Slot(key, index);
   return false;
}

bool HashTable::probe(int key, int &collisions)
{
}