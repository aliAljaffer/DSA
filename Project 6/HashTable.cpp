#include "HashTable.h"
#include <algorithm>
// HashTable ->
HashTable::HashTable()
{
   slotsOccupied = 0;
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

float HashTable::alpha()
{
   return (float)slotsOccupied / MAXHASH;
}

bool HashTable::adjustSlotIndex(int slotIndex, int newStoredValue)
{
   slots[slotIndex].setIndex(newStoredValue);
   return true;
}
int HashTable::getSlotsOccupied() const
{
   return slotsOccupied;
}
void HashTable::setSlotsOccupied(int newSlotsNumber)
{
   slotsOccupied = newSlotsNumber;
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
   slotsOccupied++;
   return true;
}

// bool HashTable::remove(int key)
// {
//    int homePosition = jsHash(key) % MAXHASH;
//    int i = 0;
//    Slot currentSlot = slots[(homePosition + offsets[i]) % MAXHASH];
//    while (currentSlot.getKey() != key && !currentSlot.isEmptySinceStart() && i < MAXHASH - 1)
//    {
//       i++;
//       currentSlot = slots[(homePosition + offsets[i]) % MAXHASH];
//    }
//    if (i == MAXHASH || currentSlot.isEmptySinceStart())
//    {
//       // Key not in hashtable
//       return false;
//    }
//    currentSlot.kill();
//    return true;
// }
bool HashTable::remove(int key)
{
   int index = -1;
   findInHashTable(key, index);
   if (index == -1)
      return false;
   slots[index].kill();
   slotsOccupied--;
   return true;
}
bool HashTable::findInHashTable(int key, int &index) const
{
   int homePosition = jsHash(key) % MAXHASH;
   int probe = homePosition;
   int i = 0;
   while (!slots[probe].isEmptySinceStart() && i < MAXHASH - 1)
   {
      if (slots[probe].getKey() == key && !slots[probe].isEmptyAfterRemoval())
      {
         index = probe;
         return true;
      }
      probe = (homePosition + offsets[i]) % MAXHASH;
      i++;
   }
   return false;
}
bool HashTable::find(int key, int &index, int &collisions)
{
   collisions = 0;
   int homePosition = jsHash(key) % MAXHASH;
   int probe = homePosition;
   while (!slots[probe].isEmptySinceStart() && collisions < MAXHASH - 1)
   {
      if (slots[probe].getKey() == key && !slots[probe].isEmptyAfterRemoval())
      {
         index = slots[probe].getIndex();
         return true;
      }
      probe = (homePosition + offsets[collisions]) % MAXHASH;
      collisions++;
   }
   return false;
}

ostream &operator<<(ostream &os, const HashTable &printMe)
{
   for (int i = 0; i < MAXHASH; i++)
   {
      if (i == 0)
      {
         os << "HashTable contents:" << endl;
      }
      Slot currentSlot = printMe.slots[i];
      if (!currentSlot.isEmpty())
      {
         os << "HashTable Slot " << to_string(i) << ": Key = " << to_string(currentSlot.getKey()) << ", Index: " << to_string(currentSlot.getIndex()) << endl;
      }
   }
   return os;
}