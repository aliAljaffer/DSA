#include "HashTable.h"
#include "Database.h"
#include <iostream>

int main()
{
   Database db;
   int collisions = 0;
   string userChoice;
   cout << "Would you like to (I)nsert or (D)elete a record, (S)earch for a record, \n(P)rint the database, or (Q) uit ? " << endl;
   cin >> userChoice;
   if (userChoice[0] == 'i')
   {
      string firstName, lastName, year;
      int uid;
      cout << "Inserting a new record." << endl;
      cout << "Last name: " << endl;
      cin >> lastName;
      cout << "First name: " << endl;
      cin >> firstName;
      cout << "UID: " << endl;
      cin >> uid;
      cout << "Year: " << endl;
      cin >> year;
      Record toAdd(firstName, lastName, uid, year);
      if (db.insert(toAdd, collisions))
      {
         cout << "Record inserted successfully. (" << to_string(collisions) << " collisions occured).";
      }
      else
         cout << "Unable to insert. Either the UID is a duplicate or the database is full.";
   }
}

void tests()
{
   HashTable ht = HashTable();
   int collisions = 0;
   ht.insert(13225521, 1, collisions);
   ht.insert(13225521, 2, collisions);
   ht.insert(13225521, 3, collisions);
   ht.insert(132232121, 4, collisions);
   ht.insert(132511421, 5, collisions);
   cout << ht;
   Database db(ht);
   Record r = Record("Ali", "Aljaffer", 10420322, "Junior");
   db.insert(r, collisions);
   cout << "Added record with " << to_string(collisions) << " collisions." << endl;
}