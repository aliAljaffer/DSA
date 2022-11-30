#include "HashTable.h"
#include "Database.h"
#include <iostream>
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 * Database implementation using jsHash as a hash function
 * and psuedo-random probing.
 */
int main()
{
   Database db;
   int collisions = 0;
   string userChoice;
   while (userChoice[0] != 'Q' && userChoice[0] != 'q')
   {
      cout << "\nWould you like to (I)nsert or (D)elete a record, (S)earch for a record, \n(P)rint the database, or (Q) uit ? " << endl;
      cin >> userChoice;

      if (userChoice[0] == 'I' || userChoice[0] == 'i')
      {
         string firstName, lastName, year;
         int uid;
         if (db.alpha() == 1)
         {
            cout << "Error: The database is full. Unable to insert." << endl;
            continue;
         }
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
            cout << "\nError: Unable to insert. UID is a duplicate." << endl;
      }
      else if (userChoice[0] == 'D' || userChoice[0] == 'd')
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
      else if (userChoice[0] == 'S' || userChoice[0] == 's')
      {
         int uid = -1;
         int collisions = 0;
         Record searchedForRecord;
         cout << "Searching for a record. Enter UID to search for: ";
         cin >> uid;
         cout << "Searching... ";
         if (db.find(uid, searchedForRecord, collisions))
         {
            cout << "Found it! Collisions: " << to_string(collisions) << "\n--------------------" << endl;
            cout << searchedForRecord << endl;
            cout << "--------------------" << endl;
         }
         else
            cout << "Error: Record not found." << endl;
      }
      else if (userChoice[0] == 'P' || userChoice[0] == 'p')
      {
         cout << "Printing the database...\n";
         cout << db << endl;
      }
   }
   cout << "Quitting.. Bye!" << endl;
}
