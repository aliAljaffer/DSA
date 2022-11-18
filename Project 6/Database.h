#pragma once
#include "Slot.h"
#include "Record.h"
#include "hashfunction.h"
#include "HashTable.h"
#include <vector>
#define MAXHASH 20
using namespace std;
class Database
{
private:
   HashTable indexTable;
   vector<Record> recordStore;

public:
   bool insert(const Record &newRecord, int &collisions);
   bool remove(int key);
   bool find(int uid, Record &foundRecord, int &collisions);
   friend ostream &operator<<(ostream &, const Database &);
   float alpha()
   {
      return indexTable.alpha();
   }
};