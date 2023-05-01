#include "HashTable.h"
#include <algorithm>
#include <chrono>
#include <random>
/*
 * Ali Aljaffer - CS3100
 * Database implementation using jsHash as a hash function
 * and psuedo-random probing.
 */

/// @brief No args constructor that initializes the slots and offsets arrays and then randomizes the offsets
HashTable::HashTable()
{
   slotsOccupied = 0;
   for (int i = 0; i < MAXHASH; i++)
   {
      slots[i] = Slot();
      if (i < MAXHASH - 1)
         offsets[i] = i + 1;
   }
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   shuffle(begin(offsets), end(offsets), default_random_engine(seed));
}

HashTable::~HashTable()
{
}

/// @brief Occupancy of the hashtable
/// @return 0 <= float <= 1
float HashTable::alpha()
{
   return (float)slotsOccupied / MAXHASH;
}

/// @brief Adjusts the value stored in a slot
/// @param slotIndex the index of the slot to adjust
/// @param newStoredValue the new value to change the index to
/// @return true when successful(always)
bool HashTable::adjustSlotIndex(int slotIndex, int newStoredValue)
{
   slots[slotIndex].setIndex(newStoredValue);
   return true;
}

/// @brief getter for slotsOccupied
/// @return the number of the normal slots in the hash table
int HashTable::getSlotsOccupied() const
{
   return slotsOccupied;
}

/// @brief Inserts a key into the hashtable
/// @param key the key to insert
/// @param index the index of the key in the database recordStore
/// @param collisions the number of collisions encountered
/// @return true on successful insert, false if either duplicate or if hash table is full.
bool HashTable::insert(int key, int index, int &collisions)
{
   collisions = 0;
   int homePosition = jsHash(key) % MAXHASH;
   int probe = homePosition;
   // While loop finds an empty slot using the probe sequence
   while (!slots[probe].isEmpty() && collisions < MAXHASH - 1)
   {
      if (slots[probe].getKey() == key)
         return false;
      probe = (homePosition + offsets[collisions]) % MAXHASH;
      collisions++;
   }
   // This check is to make sure we exited the loop because the found slot was empty, and not because we collided over the limit!
   if (collisions == MAXHASH - 1)
   {
      return false;
   }
   slots[probe].load(key, index); // use setters
   slotsOccupied++;
   return true;
}

/// @brief Removes a key from the hashtable
/// @param key the key to remove
/// @return true on successful removal, false if key doesn't exist in the table
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

/// @brief Similar to regular find, except that it gets the index of a key in the hashtable rather than the database vector
/// @param key the key to find
/// @param index we'll store the index found in this variable
/// @return true on success, false if key doesn't exist in the hash table.
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

/// @brief Regular find that gives us the index of the key in the vector of the database
/// @param key the key to find
/// @param index we'll store the index found in this variable
/// @param collisions the number of collisions we encountered
/// @return true on success, false if key doesn't exist in the hash table.
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

/// @brief Overloaded << operator to allow for chaining hashtables to an output stream
/// @param os the output stream
/// @param printMe the hashtable to print
/// @return the output stream
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