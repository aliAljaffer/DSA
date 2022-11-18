#include "HashTable.h"
#include <iostream>

int main()
{
   HashTable ht = HashTable();
   int collisions = 0;
   ht.insert(13221421, 1, collisions);
   cout << "Inserting... " << to_string(collisions) << endl;
   collisions = 0;
   ht.insert(132131221, 2, collisions);
   cout << "Inserting... " << to_string(collisions) << endl;
   collisions = 0;
   ht.insert(13225521, 3, collisions);
   cout << "Inserting... " << to_string(collisions) << endl;
   collisions = 0;
   ht.insert(132232121, 4, collisions);
   cout << "Inserting... " << to_string(collisions) << endl;
   collisions = 0;
   ht.insert(132511421, 5, collisions);
   cout << "Inserting... " << to_string(collisions) << endl;
   collisions = 0;
}