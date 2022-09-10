#include <iostream>
#include <string>

class Character
{
private:
   std::string name;
   std::string role;
   int health;
   int bonusAttack;
   int bonusDamage;
   int armorClass;

public:
   void attack(Character &); // making this return bool to know if attack hit or missed.
   void print(std::ostream &);
   void damage(int);
   int getHealth();
   std::string getName();
   std::string getRole();
   Character(); // no args. all fields randomized
   Character(std::string, std::string, int, int, int, int);
   Character(std::string); // given a name, randomizes other attributes
   bool operator>(const Character &);
   void setName(std::string);
};
