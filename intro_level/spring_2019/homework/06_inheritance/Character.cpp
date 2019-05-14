//include the necessary header files
#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

//getter functions
string Character::getOccupation() const {return occupation;}
string Character::getRace() const {return race;}
char Character::getGender() const {return gender;}

//setter functions
void Character::setRace(string r) {race = r;}
void Character::setOccupation(string o) {occupation = o;}
void Character::setGender(char g) {gender = g;}

//overloaded operator function
bool Character::operator==(const Character &other) {
	if (race == other.getRace() && gender == other.getGender())
		return true;
	return false;
}

//stats function
void Character::stats() const {
	cout << "Occupation: " << occupation << endl;
  cout << "Race: " << race << endl;
  cout << "Gender: " << gender << endl;
}