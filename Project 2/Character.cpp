#include "Character.h"
#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <cstdlib>

using namespace std;
// CONSTRUCTORS
// random values constructor
Character::Character()
{
   name = "Test Bot";
   role = "A.I.";
   health = (rand() % 100) + 1;
   bonusAttack = (rand() % 20) + 1;
   bonusDamage = (rand() % 10) + 1;
   armorClass = (rand() % 15) + 1;
}

Character::Character(string name, string role, int health, int bonusAttack, int bonusDamage, int armorClass)
{
   this->name = name;
   this->role = role;
   // To prevent starting with 0 health and/or using negative values.
   this->health = (health == 0) ? (rand() % 100) + 1 : abs(health);
   this->bonusAttack = (bonusAttack == 0) ? (rand() % 20) + 1 : abs(bonusAttack);
   this->bonusDamage = (bonusDamage == 0) ? (rand() % 10) + 1 : abs(bonusDamage);
   this->armorClass = (armorClass == 0) ? (rand() % 15) + 1 : abs(armorClass);
}
// ATTACKS/BATTLE FUNCTIONS
//----------------------------------------------------------------
// attack: this attacks other
//
//    Returns:  none
//    Parameters:
//       Character* other -The character being attacked
//----------------------------------------------------------------
void Character::attack(Character *other)
{
   // Announcement
   cout << this->name << " attacks!" << endl;
   // 1-20 roll.
   int attackRoll = (rand() % 20) + 1;
   // string to print
   string attackPrint = "Attack Roll: " + to_string(attackRoll) + " + " + to_string(bonusAttack) + " = " + to_string(attackRoll + bonusAttack);
   // checking if attack hits or misses
   if (attackRoll + bonusAttack >= other->armorClass)
   {
      cout << attackPrint << " --> HIT!" << endl;
      // rolling 1-10 then adding bonus damage
      int actualAttack = bonusDamage + (rand() % 10) + 1;
      string damagePrint = "Damage: " + to_string(actualAttack - bonusDamage) + " + " + to_string(bonusDamage) + " = " + to_string(actualAttack);

      other->damage(actualAttack);
      cout << damagePrint << endl;
      cout << other->getName() << " has " << other->getHealth() << " hit points remaining." << endl
           << endl;
   }
   else
      cout << attackPrint << " --> MISS!" << endl
           << endl
           << endl;
}
//----------------------------------------------------------------
// damage: Reduces the HP of character that called it by amount
//    Returns:  none
//    Parameters:
//       int amount - the amount to reduce the health by
//----------------------------------------------------------------
void Character::damage(int amount)
{
   // if "amount" would drop HP to negatives, just set it to 0. else subtract normally
   health = (health - amount < 0) ? 0 : health - amount;
}

//----------------------------------------------------------------
// print: prints out the details of the character calling the function
//    Returns:  none
//    Parameters:
//       ostream &os - the output stream to print out to
//----------------------------------------------------------------
void Character::print(ostream &os)
{
   os << "Name: " << name << endl
      << "Role: " << role << endl
      << "HP: " << health << endl      // Hit points
      << "AB: " << bonusAttack << endl // Attack bonus
      << "DB: " << bonusDamage << endl // Damage bonus
      << "AC: " << armorClass << endl; // Armor class
}

// GETTERS
int Character::getHealth()
{
   return health;
}
string Character::getName()
{
   return name;
}
string Character::getRole()
{
   return role;
}

// SETTERS
void Character::setName(string name)
{
   this->name = name;
}