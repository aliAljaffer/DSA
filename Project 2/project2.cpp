#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

void printSummary(Character &);
int getIntInput(string);
string getStringInput(string);
Character charCreator();
Character fight(Character &, Character &);

int main()
{
   // seeding
   srand(time(NULL));

   // Character creation
   Character firstCharacter = charCreator();
   printSummary(firstCharacter);
   Character secondCharacter = charCreator();
   if (firstCharacter.getName() == secondCharacter.getName())
      secondCharacter.setName(secondCharacter.getName() + " (2)"); // in case 2 bots are chosen
   printSummary(secondCharacter);

   // Fighting and assigning the winner
   Character winner = fight(firstCharacter, secondCharacter);
   cout << winner.getName() << " wins!" << endl;
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
// printSummary: A function that utilizes the Character
//               class' print()
//    Returns:  nothing. but prints out the summary to cout
//    Parameters: the Character to be summarised (Character ref&)
//----------------------------------------------------------------
void printSummary(Character &c)
{
   cout
       << "\n-----------------"
       << "\nCharacter summary" << endl
       << "-----------------" << endl;
   c.print(cout);
   cout << endl;
}

//----------------------------------------------------------------
// charCreator: Creates a character object
//              using the other input functions to
//              inquire about the needed data
//    Returns:  the newly created character(Character)
//    Parameters: none needed
//----------------------------------------------------------------
Character charCreator()
{
   // extra functionality: uses the no arg constructor to create a bot character with random stats
   string input = getStringInput("Would you like to randomize the character's attributes? (y/n)");
   if (input[0] == 'y' || input[0] == 'Y')
      return Character();
   // Character creation process in a single function, to av
   string name = getStringInput("Character name?");
   string role = getStringInput(name + "'s role?");
   cout << "-----------------\n"
        << "Inputting 0 for any of the attributes" << endl
        << "will result in a randomized number"
        << "\n-----------------" << endl;
   int health = getIntInput(name + "'s hit points?");
   int bonusAttack = getIntInput(name + "'s attack bonus?");
   int bonusDamage = getIntInput(name + "'s damage bonus?");
   int armorClass = getIntInput(name + "'s armor class?");
   Character createdCharacter(name, role, health, bonusAttack, bonusDamage, armorClass);
   return createdCharacter;
}

//----------------------------------------------------------------
// fight: Pit character one against character two
//          until one of them dies
//    Returns:  the fight winner (Character)
//    Parameters:
//       Character& one
//       Character& two
//----------------------------------------------------------------

Character fight(Character &one, Character &two)
{
   while (one.getHealth() > 0 && two.getHealth() > 0) // keep attacking while both are alive.
   {
      one.attack(two);
      if (two.getHealth() == 0)
         return one;
      // ^ checking two's HP before allowing it to attack. this prevents two from
      // attacking while having 0 HP.
      // if two is dead, returns the winner, one.
      two.attack(one);
   }
   return two; // Only case where we'd be outside the while-loop is if two kills one, since we check two's health after they get attacked by one
}
