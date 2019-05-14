//DO NOT ALTER THIS FILE
//This file is meant to help you see how some portions of code are ran and work. It will also be used for testing.

#include "Character.h"
#include "Weapon.h"
#include "Protagonist.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
	 
   Protagonist Aang("Airbender", 12);
   Aang.setRace("Avatar");
   Aang.setEquipment("Airbender Staff");
   Aang.stats();
   
   Character Daenerys_Targaryen("Princess", "Valyrian", 'F');
   Daenerys_Targaryen.stats();
   Daenerys_Targaryen.setOccupation("Dragon Tamer");
   Daenerys_Targaryen.stats();
   
   Protagonist BeastBoy;
   BeastBoy.setType("Shapeshifter");
   BeastBoy.setAge(19);
   BeastBoy.setRace("Human");
   BeastBoy.setEquipment("None");
   BeastBoy.setGender('M');
   BeastBoy.stats();
   BeastBoy.setType("Shapeshifter");
   BeastBoy.setRace("Tiger");
   BeastBoy.setEquipment("Fangs");
   BeastBoy.stats();
   BeastBoy.setType("Shapeshifter");
   BeastBoy.setRace("Grizzly Bear");
   BeastBoy.setEquipment("Claws");
   BeastBoy.stats();
	 
	 return 0;
}