#ifndef PROTAGONIST_H
#define PROTAGONIST_H
//include weapon header file
#include "Weapon.h"
#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

/*syntax to make class Protagonist derived from class Character*/
class Protagonist : public Character {
	public:
	//constructors
	Protagonist();
	Protagonist(string ty, int ag);

	//getter functions
	string getType() const;
	int getAge() const;
	string getEquipment() const;

	//setter functions
	void setType(string t);
	void setAge(int a);
	void setEquipment(string e);

	//overloaded operator function
	bool operator==(const Protagonist &protag);

	//stats function
	void stats() const;

	private:
	//variables
	int age;
	Weapon equipment;

	protected:
	//variable
  string type;
};

#endif