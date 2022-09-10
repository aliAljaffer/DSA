#include "Character.h"
#include <iostream>
#include <string>
#include <time.h>
#include <random>

using namespace std;
// CONSTRUCTORS
Character::Character() // random values
{
   name = "Test Bot";
   role = "A.I.";
   health = (rand() % 100) + 1;
   bonusAttack = (rand() % 20) + 1;
   bonusDamage = (rand() % 10) + 1;
   armorClass = (rand() % 15) + 1;
}
Character::Character(string name) // random values, but given name.
{
   this->name = name;
   role = "randomPerson";
   health = (rand() % 100) + 1;
   bonusAttack = (rand() % 20) + 1;
   bonusDamage = (rand() % 10) + 1;
   armorClass = (rand() % 15) + 1;
}
Character::Character(string name, string role, int health, int bonusAttack, int bonusDamage, int armorClass)
{
   this->name = name;
   this->role = role;
   this->health = health;
   this->bonusAttack = bonusAttack;
   this->bonusDamage = bonusDamage;
   this->armorClass = armorClass;
}
// ATTACKS/BATTLE FUNCTIONS
void Character::attack(Character &other)
{
   cout << this->name << " attacks!" << endl; // Announcement

   int attackRoll = (rand() % 20) + 1;                                                                                                          // 1-20 roll.
   string attackPrint = "Attack Roll: " + to_string(attackRoll) + " + " + to_string(bonusAttack) + " = " + to_string(attackRoll + bonusAttack); // string to print
   if (attackRoll + bonusAttack >= other.armorClass)                                                                                            // checking if attack hits or misses
   {
      cout << attackPrint << " --> HIT!" << endl;
      int actualAttack = bonusDamage + (rand() % 10) + 1; // rolling 1-10 then adding bonus damage
      string damagePrint = "Damage: " + to_string(actualAttack - bonusDamage) + " + " + to_string(bonusDamage) + " = " + to_string(actualAttack);

      other.damage(actualAttack);
      cout << damagePrint << endl;
      cout << other.getName() << " has " << other.getHealth() << " hit points remaining." << endl
           << endl;
   }
   else
      cout << attackPrint << " --> MISS!" << endl
           << endl
           << endl;
}

void Character::damage(int amount)
{
   // if "amount" would drop HP to negatives, just set it to 0. else subtract normally
   health = (health - amount < 0) ? 0 : health - amount;
}

// PRINT
void Character::print(ostream &os)
{
   os << "Name: " << name << endl
      << "Role: " << role << endl
      << "HP: " << health << endl      // Hit points
      << "AB: " << bonusAttack << endl // Attack bonus
      << "DB: " << bonusDamage << endl // Damage bonus
      << "AC: " << armorClass << endl; // Armor class
}

// OPERATOR OVERLOADS
bool Character::operator>(const Character &o)
{
   return health > o.health; // comparing two characters is just comparing their hit points
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