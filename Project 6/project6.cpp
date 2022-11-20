#include "HashTable.h"
#include "Database.h"
#include <iostream>

int main()
{
   Database db;
   int collisions = 0;
   string userChoice;
   while (userChoice[0] != 'Q')
   {
      cout << "\nWould you like to (I)nsert or (D)elete a record, (S)earch for a record, \n(P)rint the database, or (Q) uit ? " << endl;
      cin >> userChoice;
      if (userChoice[0] == 'I')
      {
         string firstName, lastName, year;
         int uid;
         cout << "Inserting a new record." << endl;
         cout << "Last name: ";
         cin >> lastName;
         cout << "\nFirst name: ";
         cin >> firstName;
         cout << "\nUID: ";
         cin >> uid;
         cout << "\nYear: ";
         cin >> year;
         Record toAdd(firstName, lastName, uid, year);
         if (db.insert(toAdd, collisions))
         {
            cout << "\nRecord inserted successfully. (" << to_string(collisions) << " collisions occured)." << endl;
         }
         else
            cout << "\nError: Unable to insert. Either the UID is a duplicate or the database is full." << endl;
      }
      else if (userChoice[0] == 'D')
      {
         int uid = -1;
         cout << "Deleting a record. \nWhat's the UID for the record? ";
         cin >> uid;
         cout << "\nRemoving UID: " << to_string(uid) << " from the database... ";
         if (db.remove(uid))
         {
            cout << "Successfully removed." << endl;
         }
         else
            cout << "Error: UID does not exist in the database." << endl;
      }
      else if (userChoice[0] == 'S')
      {
         int uid = -1;
         int collisions = 0;
         Record searchedFor;
         cout << "Searching for a record. Enter UID to search for: ";
         cin >> uid;
         cout << "Searching... ";
         if (db.find(uid, searchedFor, collisions))
         {
            cout << "Found it! Collisions: " << to_string(collisions) << "\n--------------------" << endl;
            cout << searchedFor << endl;
            cout << "--------------------" << endl;
         }
         else
            cout << "Error: Record not found." << endl;
      }
      else if (userChoice[0] == 'P')
      {
         cout << "Printing the database...";
         if (db.alpha() != 0)
         {
            cout << "\n"
                 << db << endl;
         }
         else
            cout << "Error: data base is empty." << endl;
      }
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