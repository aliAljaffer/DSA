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
   void attack(Character *);
   void print(std::ostream &);
   void damage(int);
   int getHealth();
   std::string getName();
   std::string getRole();
   Character();
   Character(std::string, std::string, int, int, int, int);
   void setName(std::string);
};
