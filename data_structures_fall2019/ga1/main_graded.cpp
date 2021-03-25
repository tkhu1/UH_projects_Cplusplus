#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

/*GROUP CONSISTED OF TYLER HU & ARMANDO MATA & MITCHELL MONTVALVO
  WE ALL CONTRIBUTED TO THE CODE */

//NODES////////////////////////////////////////////////////////////////////////////////
struct player {
	string name;
	string jerseyNum;
	string position;
	player *next;
};

//CLASSES//////////////////////////////////////////////////////////////////////////////
class list {
	private:
		int count = 0; //counts how many nodes are in list
  	player* head;
		player* cu;
		player* temp;
	public: 
   	//default constructor
		list() { 
			head = NULL;
			cu = NULL;
			temp = NULL;
		}
		// void print(); //DEBUG
		void addNode(string, string, string);
		void sortAlpha();
		int checklist(string);
};
//FUNCTIONS////////////////////////////////////////////////////////////////////////////
//DEBUG
/*
void list::print() {
	cu = head;
	for (int i = 0; i < count; i++) {
		cout << cu->name << endl;
		cu = cu->next;
	}
}*/

//creates new node to add
void list::addNode(string addName, string addJersey, string addPosition) {
	player* n = new player; 
	n->next = NULL;
	n->name = addName;
	n->jerseyNum = addJersey;
	n->position = addPosition;

	//keeps track of number of nodes in list
	count++;

	if (head != NULL) {          //checks if list exists
		cu = head;                 //start at head
		while (cu->next != NULL) { //loop until reach final node
			cu = cu->next;
		}
		cu->next = n;              //connect final node to new node
	}
	else {                       //if list doesn't exist
		head = n;                  //initialize linked list
	}
}

//sorts linked list by alphabetical name
void list::sortAlpha() {
	player* tmphead = head;
	string tmpname, tmpjnum, tmppos;

	for (int i = 0; i < count; i++) {
		while (tmphead->next) {
			if (tmphead->name > tmphead->next->name) {
				//swaps player name
				tmpname = tmphead->name;
				tmphead->name = tmphead->next->name;
				tmphead->next->name = tmpname;
				//swaps player jersey number
				tmpjnum = tmphead->jerseyNum;
				tmphead->jerseyNum = tmphead->next->jerseyNum;
				tmphead->next->jerseyNum = tmpjnum;
				//swaps player position
				tmppos = tmphead->position;
				tmphead->position = tmphead->next->position;
				tmphead->next->position = tmppos;
			}
			else {
				//moves to next node if no swap is needed
				tmphead = tmphead->next;
			}
		}
		//reassigns pointer to head
		tmphead = head;
	}
}

//checks if command input is found in list and returns wanted value
int list::checklist(string line) {
	int playerIndexNum = 0;
	cu = head;
	while (cu->next) {
		if (line == cu->name) {
			//returns index position of player
			return playerIndexNum;
		} 
		else {
			cu = cu->next;
			playerIndexNum++;
		}
	}
	//returns -1 if command / data mismatch
	return -1;
}

//MAIN/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Invalid arguments" << endl;
		return 1;
	}
	ArgumentManager am(argc, argv);
	const string input = am.get("input");
	const string output = am.get("output");
	const string command = am.get("command");

	string tempName, tempJersey, tempPosition; //holds input file value

	//init input stream
	ifstream fileIn;
	fileIn.open(input);
	//ERROR HANDLING: exits if input not found
	if (!fileIn) {
    cout << "Could not open the input file. Exiting program." << endl;
    return 1;
  }

	//creates list obj
	list psg;

	//reads file data into nodes and creates linked list
	while (getline(fileIn, tempName, ',')) {
		getline(fileIn, tempJersey, ',');
		getline(fileIn, tempPosition);

		//constructs node from temp vars
		psg.addNode(tempName, tempJersey, tempPosition);
	}

	fileIn.close();

	//sorts linked list by alphabetical order
	psg.sortAlpha();
	//psg.print(); //DEBUG

	//init command stream
	ifstream commandIn;
	commandIn.open(command);
	//ERROR HANDLING: exits if input not found
	if (!commandIn) {
    cout << "Could not open the command file. Exiting program." << endl;
    return 1;
  }

	//init output stream
	ofstream fileOut;
	fileOut.open(output);

	//outputs to file with command input as comparison
	string commandLine;
	int playerIndexResult;
	while (getline(commandIn, commandLine)) {
		//removes newline from a valid command
		if (!commandLine.empty() && commandLine[commandLine.size()-1] == '\r') {
    	commandLine = commandLine.substr(0, commandLine.size()-1);
		}
		//ERROR CHECKING: skips newline and whitespace
		if (commandLine != "") {
			//checks commands with list data
			playerIndexResult = psg.checklist(commandLine);
			fileOut << commandLine << ": " << playerIndexResult << endl;
		}
	}
	
	commandIn.close();
	fileOut.close();

	return 0;
}