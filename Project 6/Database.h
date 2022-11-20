#pragma once
#include "Slot.h"
#include "Record.h"
#include "hashfunction.h"
#include "HashTable.h"
#include <vector>
#define MAXHASH 20
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 * Database implementation using jsHash as a hash function
 * and psuedo-random probing.
 */
class Database
{
private:
   HashTable indexTable;
   vector<Record> recordStore;

public:
   Database();
   Database(const HashTable &);
   ~Database();
   bool insert(const Record &newRecord, int &collisions);
   bool remove(int key);
   bool find(int uid, Record &foundRecord, int &collisions);
   friend ostream &operator<<(ostream &, const Database &);
   float alpha()
   {
      return indexTable.alpha();
   }
};