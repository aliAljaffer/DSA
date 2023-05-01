#include "Database.h"
#include "Record.h"
#include "HashTable.h"
/*
 * Ali Aljaffer - CS3100
 * Database implementation using jsHash as a hash function
 * and psuedo-random probing.
 */

/// @brief No args constructor to initialize the DB fields
Database::Database()
{
   indexTable = HashTable();
   for (int i = 0; i < recordStore.size(); i++)
   {
      recordStore[i] = Record();
   }
}

/// @brief DB Destructor
Database::~Database()
{
}

/// @brief Inserts a record into the database and indexTable
/// @param newRecord the record to insert
/// @param collisions the number of collisions encountered
/// @return true on success, false if record already exists or the indexTable is full
bool Database::insert(const Record &newRecord, int &collisions)
{
   collisions = 0;
   int index = -1;
   indexTable.findInHashTable(newRecord.getUID(), index);
   if (index != -1)
      return false;

   if (indexTable.insert(newRecord.getUID(), recordStore.size(), collisions))
   {
      recordStore.push_back(newRecord);
      return true;
   }
   return false;
}

/// @brief Removes a key from the database
/// @param key the key to remove
/// @return true on successful removal, false if key isn't in the database.
bool Database::remove(int key)
{
   Record toDelete;
   int collisions = 0;
   if (!find(key, toDelete, collisions))
   {
      return false;
   }
   // Finds the index of the record in the recordStore
   int indexInRecordStore = 0;
   indexTable.find(toDelete.getUID(), indexInRecordStore, collisions);

   // Removes the record's UID from the indexTable
   indexTable.remove(toDelete.getUID());

   // Copies the last record in the recordStore into toDelete
   toDelete.recordCopy(recordStore[recordStore.size() - 1]);

   // Finds the index of the record in the indexTable
   int indexInHashTable = 0;
   indexTable.findInHashTable(toDelete.getUID(), indexInHashTable);

   // Now that we have both indices, we need to adjust the index of the swapped record(that was in the last index of the recordStore)
   indexTable.adjustSlotIndex(indexInHashTable, indexInRecordStore);

   // Swap it
   recordStore[indexInRecordStore] = toDelete;
   // Delete the last vector
   recordStore.pop_back();
   return true;
}

/// @brief Finds a key(uid) in the record store and stores it in the foundRecord reference record
/// @param uid the uid to find
/// @param foundRecord the reference record
/// @param collisions the number of collisions encountered
/// @return true on success, false if can't find the uid in the indextable
bool Database::find(int uid, Record &foundRecord, int &collisions)
{
   collisions = 0;
   int index = -1;
   indexTable.find(uid, index, collisions);
   if (index == -1)
   {
      return false;
   }
   foundRecord.load(recordStore[index].getFirstName(), recordStore[index].getLastName(), recordStore[index].getUID(), recordStore[index].getYear());
   return true;
}

/// @brief Overloaded << operator to allow chaining databases to output streams
/// @param os the output stream
/// @param printMe the database to print
/// @return the output stream
ostream &operator<<(ostream &os, const Database &printMe)
{
   if (printMe.indexTable.getSlotsOccupied() == 0)
   {
      os << "Empty database." << endl;
      return os;
   }

   for (int i = 0; i < printMe.recordStore.size(); i++)
   {
      if (i == 0)
      {
         os << "Database contents:\n--------------------\n"
            << endl;
      }
      // get the current record
      Record currentRecord = printMe.recordStore[i];

      // get it's index in the hashtable
      int indexInHashTable = 0;
      printMe.indexTable.findInHashTable(currentRecord.getUID(), indexInHashTable);

      // since we are looping on the record store, i is the index in the record store so no need to look for that
      os << "HashTable Slot:\t" << to_string(indexInHashTable) << "\t--\trecordStore slot:\t" << to_string(i) << "\t--\t" << currentRecord << endl;
   }
   return os;
}