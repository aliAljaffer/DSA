#include "Database.h"
#include "Record.h"
#include "HashTable.h"
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
   recordStore.push_back(newRecord);
   indexTable.insert(newRecord.getUID(), recordStore.size() - 1, collisions);
   return true;
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
   toDelete.recordCopy(recordStore[recordStore.size() - 1]);
   int indexInHashTable = 0;
   indexTable.findInHashTable(toDelete.getUID(), indexInHashTable);
   indexTable.adjustSlotIndex(indexInHashTable, indexInRecordStore);
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
      Record currentRecord = printMe.recordStore[i];
      int indexInHashTable = 0;
      printMe.indexTable.findInHashTable(currentRecord.getUID(), indexInHashTable);
      os << "HashTable Slot: " << to_string(indexInHashTable) << ", recordStore slot " << to_string(i) << " -- " << currentRecord << endl;
   }
   return os;
}