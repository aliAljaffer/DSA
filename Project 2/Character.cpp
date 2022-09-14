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
// random values, but given name.
Character::Character(string name)
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
   // To prevent starting with 0 health and/or using negative values.
   this->health = (health == 0) ? (rand() % 100) + 1 : abs(health);
   this->bonusAttack = (bonusAttack == 0) ? (rand() % 20) + 1 : abs(bonusAttack);
   this->bonusDamage = (bonusDamage == 0) ? (rand() % 10) + 1 : abs(bonusDamage);
   this->armorClass = (armorClass == 0) ? (rand() % 15) + 1 : abs(armorClass);
}
// ATTACKS/BATTLE FUNCTIONS
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
bool Character::operator>(const Character *o)
{
   // comparing two characters is just comparing their hit points
   return health > o->health;
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