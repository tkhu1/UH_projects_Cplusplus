#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>
using namespace std;

class Character { 
   
public:
   //constructors (in-line)
   Character(): occupation("Cabbage Merchant"), race("Human"), gender('M') {};
   Character(string occTemp, string raceTemp, char genderTemp): occupation(occTemp), 
							        							race(raceTemp), 
               													gender(genderTemp) {};
   
   //getter functions
   string getOccupation() const;
   string getRace() const;
   char getGender() const;
   
   //setter functions
   void setRace(string r);
   void setOccupation(string o);
   void setGender(char g);
   
   //overloaded operator function
   bool operator==(const Character &other);
   
   //stats function
   void stats() const;
   
private:
   string occupation;
	
protected:
   string race;
   char gender;

};

#endif
