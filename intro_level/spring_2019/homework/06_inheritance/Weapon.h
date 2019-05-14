#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include <string>
using namespace std;

class Weapon {
   
public:
   //constructors
   Weapon();
   Weapon(string weapTemp);
   
   //getter function
   string getWeapon() const;
   
   //setter function
   void setWeapon(string newWeap);
	 
   //stats function
   void stats() const;
   
private:
   string type;
};


#endif