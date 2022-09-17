#include "Character.h"
#include <iostream>
#include <string>
#include <time.h>
#pragma once
using namespace std;

int getIntInput(string);
string getStringInput(string);
Character *charCreator();
Character *fight(Character *, Character *);

int main()
{
   // seeding
   srand(time(NULL));

   // Character creation
   Character *firstCharacter = charCreator();
   firstCharacter->print(cout);
   Character *secondCharacter = charCreator();
   secondCharacter->print(cout);

   // Fighting and assigning the winner
   Character *winner = fight(firstCharacter, secondCharacter);
   cout << winner->getName() << " wins!\n"
        << endl;

   // Program end
   cout << "Exiting.." << endl;
   delete firstCharacter;
   delete secondCharacter;
   return 1;
}
//----------------------------------------------------------------
// getStringInput: A function to take in string input from the user
//
//    Returns:  output (string)
//    Parameters: the prompt to be displayed to the user
//----------------------------------------------------------------
string getStringInput(string prompt)
{
   string output = "";
   cout << prompt << endl;
   cin >> output;
   return output;
}
//----------------------------------------------------------------
// getIntInput: A function to take in integer input from the user
//
//    Returns:  output (integer)
//    Parameters: the prompt to be displayed to the user
//----------------------------------------------------------------
int getIntInput(string prompt)
{
   int output;
   cout << prompt << endl;
   cin >> output;
   return output;
}

//----------------------------------------------------------------
// *charCreator: Creates a character object
//              using the other input functions to
//              inquire about the needed data
//    Returns:  pointer to the newly created character on the heap(Character)
//    Parameters: none needed
//----------------------------------------------------------------
Character *charCreator()
{
   string name = getStringInput("Character name?");
   string role = getStringInput(name + "'s role?");
   string nameAndRole = name + " the " + role;
   cout << "-----------------\n"
        << "Inputting 0 for any of the attributes" << endl
        << "will result in a randomized number"
        << "\n-----------------" << endl;
   int health = getIntInput(nameAndRole + "'s hit points?");
   int bonusAttack = getIntInput(nameAndRole + "'s attack bonus?");
   int bonusDamage = getIntInput(nameAndRole + "'s damage bonus?");
   int armorClass = getIntInput(nameAndRole + "'s armor class?");
   return new Character(name, role, health, bonusAttack, bonusDamage, armorClass);
}

//----------------------------------------------------------------
// *fight: Pit character one against character two
//          until one of them dies
//    Returns:  pointer to the fight winner (Character*)
//    Parameters:
//       Character* one - The first character
//       Character* two - The second character
//----------------------------------------------------------------

Character *fight(Character *one, Character *two)
{
   while (one->getHealth() > 0 && two->getHealth() > 0) // keep attacking while both are alive.
   {
      one->attack(two);
      if (two->getHealth() == 0)
         return one;
      // ^ checking two's HP before allowing it to attack. this prevents two from
      // attacking while having 0 HP.
      // if two is dead, returns the winner, one.
      two->attack(one);
   }
   return two; // Only case where we'd be outside the while-loop is if two kills one, since we check two's health after they get attacked by one
}
