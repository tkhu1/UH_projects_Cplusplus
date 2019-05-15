#include "SpecialArray.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int measureElementsPerLine(ifstream& inFile) {
	string temp;
	int counter = 1;
	getline(inFile, temp); //gets first line of file into temp string
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == ' ') {
			counter++;
		}
	}   
	//cout << counter << endl; //DEBUG
	return counter;
}

int measureLines(ifstream& inFile) {
	string temp;
	int counter = 0;
	while (getline(inFile, temp)) {
	 	counter++;
	}
	//cout << counter << endl; //DEBUG
	return counter;
}

int main()
{
	int numOfLines, numOfElements;
	string fileName, dataType;
	cin >> fileName >> dataType;
 	ifstream inFile(fileName);

	// Add try statement below
	try {
		//checks if file exists
		if (!inFile.is_open()) {
			throw runtime_error("File does not exist.");
		}
		//checks if file is empty
		inFile.seekg (0, inFile.end);
		if (inFile.tellg() == 0) {
			throw runtime_error("File is empty.");
		}
		inFile.clear();
		inFile.seekg(0, inFile.beg);
	   
		numOfElements = measureElementsPerLine(inFile);
		inFile.close();
		inFile.open(fileName);
		numOfLines = measureLines(inFile);
		inFile.close();

		if (dataType == "int"){
			SpecialArray<int> specialArray(numOfLines, numOfElements);
			inFile.open(fileName);
			specialArray.readFile(inFile);
			inFile.close();
			specialArray.print();
			specialArray.sort();
			cout << "\nSorted outputs: \n";
			specialArray.print();
		}
		else if (dataType == "string"){
			SpecialArray<string> specialArray(numOfLines, numOfElements);
			inFile.open(fileName);
			specialArray.readFile(inFile);
			inFile.close();   
			specialArray.print();
			specialArray.sort();
			cout << "\nSorted outputs: \n";
			specialArray.print();
		}
	}
	// Add catch statement below
	catch (runtime_error& except) {
		//prints the error message passed by throw statement
		cout << except.what() << endl;
	}
	
	return 0;
}
