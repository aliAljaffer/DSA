#include "Database.h"
#include "Record.h"
#include "HashTable.h"
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 * Database implementation using jsHash as a hash function
 * and psuedo-random probing.
 */
Database::Database()
{
   indexTable = HashTable();
   for (int i = 0; i < recordStore.size(); i++)
   {
      recordStore[i] = Record();
   }
}
Database::Database(const HashTable &insertMe)
{
   indexTable = insertMe;
   for (int i = 0; i < recordStore.size(); i++)
   {
      recordStore[i] = Record();
   }
}

Database::~Database()
{
}

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

bool Database::remove(int key)
{
   Record toDelete;
   int collisions = 0;
   if (!find(key, toDelete, collisions))
   {
      return false;
   }
   int indexInRecordStore = 0;
   indexTable.find(toDelete.getUID(), indexInRecordStore, collisions);
   indexTable.remove(toDelete.getUID());
   toDelete.recordCopy(recordStore[recordStore.size() - 1]);
   int indexInHashTable = 0;
   indexTable.findInHashTable(toDelete.getUID(), indexInHashTable);
   indexTable.adjustSlotIndex(indexInHashTable, indexInRecordStore);
   recordStore[indexInRecordStore] = toDelete;
   recordStore.pop_back();
   return true;
}
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
      Record currentRecord = printMe.recordStore[i];
      int indexInHashTable = 0;
      printMe.indexTable.findInHashTable(currentRecord.getUID(), indexInHashTable);
      os << "HashTable Slot:\t" << to_string(indexInHashTable) << "\t--\trecordStore slot:\t" << to_string(i) << "\t--\t" << currentRecord << endl;
   }
   return os;
}