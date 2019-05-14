//include the necessary header files
#include "Weapon.h"
#include "Character.h"
#include "Protagonist.h"
#include <iostream>
#include <string>
using namespace std;

//constructors
Protagonist::Protagonist():Character() {
 	type = "Warrior";
	age = 25;
}

Protagonist::Protagonist(string ty, int ag):Character() {
	type = ty;
	age = ag;
}

//getter functions
string Protagonist::getType() const {return type;}
int Protagonist::getAge() const {return age;}
string Protagonist::getEquipment() const {return equipment.getWeapon();}

//setter functions
void Protagonist::setType(string t) {type = t;}
void Protagonist::setAge(int a) {age = a;}
void Protagonist::setEquipment(string e) {equipment.setWeapon(e);}

//overloaded operator function
bool Protagonist::operator==(const Protagonist &protag) {
	if (type == protag.getType() && 
	    age == protag.getAge() && 
	    equipment.getWeapon() == protag.equipment.getWeapon() &&
	    getOccupation() == protag.getOccupation() &&
	    getRace() == protag.getRace() &&
	    getGender() == protag.getGender()
	    )
		return true;
	return false;
}

//stats function
void Protagonist::stats() const {
	cout << "Race: " << race << endl;
	cout << "Gender: " << gender << endl;
	cout << "Class: " << type << endl;
	equipment.stats();
	cout << "Age: " << age << endl;
}
