#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//FUNCTIONS////////////////////////////////////////////////////////////////////////////
//returns number of ripe kiwis in one row
int GetRipeNum (int *row, int size) {
	//defaults to a size of 1 for invalid size argument
	if (size < 1) {
		size = 1;
	}
	int *p = row;
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (*p >= 6 && *p <= 8)
			counter++;
		p++;
	}
	return counter;
}
//returns number of rotten kiwis in one row
int GetRottenNum (int *row, int size) {
	//defaults to a size of 1 for invalid size argument
	if (size < 1) {
		size = 1;
	}
	int *p = row;
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (*p > 8)
			counter++;
		p++;
	}
	return counter;
}
//checks if row can be harvested
bool CheckHarvest(int *row, int size) {
	//defaults to a size of 1 for invalid size argument
	if (size < 1) {
		size = 1;
	}
	int *p = row;
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (*p >= 6)
			counter++;
		p++;
	}
	if (counter >= (size/2))
		return true;
	else
		return false;
}
//MAIN/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	if (argc != 3 && argc != 2) {
		cout << "Invalid arguments" << endl;
		return 1;
	}

	ArgumentManager am(argc, argv);
	const string input = am.get("input");
	const string output = am.get("output");

	//init input stream
	ifstream infs(input);
	//exits if input not found
	if (!infs) {
    cout << "Could not open the input file. Exiting program." << endl;
    return 1;
  }
	//error catcher
	const string errorMsg;
	//global vars
	int size, temp;
	int day = 0;
	int totalRipe = 0;
	int totalRotten = 0;

	try {
		//gets size of farm
		infs >> size;
		//throws error if farm size is less than 1
		if (size < 1) {
			throw (errorMsg);
		}
	}
	//catches error and exits
	catch (const string error) {
		cout << "Invalid size found for kiwi farm. Exiting program." << endl;
		return 1;
	}

	try {
		//init pointer matrix to represent farm
		int **farm;
		farm = new int*[size];
		//creates one farm row at a time
		for (int i = 0; i < size; i++) {
			farm[i] = new int[size];
			//pointer to kiwi
			int *p = farm[i];
			for (int j = 0; j < size; j++) {
				//holds input value
				infs >> temp;
				//throws error if input is less than 0
				if (temp < 0) {
    			throw "Invalid kiwi input value found (must be at least 0). Exiting program.";
				}
				//sets the value for current pointer to kiwi
				*p = temp;
				p++;
			}
		}

		infs.close();

		//MAIN 7 DAY LOOP////////////////////////////////////////////////////////////////////
		do {
			for (int i = 0; i < size; i++) {
				int *row = farm[i];
				//replants if needed
				if (CheckHarvest(row, size) == true) {
					totalRipe += GetRipeNum(row, size);
					totalRotten += GetRottenNum(row, size);
					for (int j = 0; j < size; j++) {
						*row = 0;
						row++;
					}
				}
				//grows rows
				else {
					for (int k = 0; k < size; k++) {
						*row += 1;
						row++;
					}
				}
			}
			day++;
			/*
			//DEBUG
			cout << "Day: " << day << endl << endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					cout << farm[i][j] << " ";
				}
			cout << endl;
			}
			cout << endl;
			*/
		} while (day < 7);

		//checks and harvests for the last time at the end of day 7
		for (int i = 0; i < size; i++) {
			int *row = farm[i];
			//replants if needed
			if (CheckHarvest(row, size) == true) {
				totalRipe += GetRipeNum(row, size);
				totalRotten += GetRottenNum(row, size);
				for (int j = 0; j < size; j++) {
					*row = 0;
					row++;
				}
			}
		}

		//init output stream
		ofstream outfs(output);

		//outputs to file
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				outfs << farm[i][j] << " ";
			}
			outfs << endl;
		}
		outfs << endl << "Harvested kiwis: " << totalRipe << endl;
		outfs << "Rotten kiwis: " << totalRotten << endl;

		outfs.close();
		delete farm;
	}
	//catches error and exits
	catch (const char* error) {
		cout << error << endl;
		return 1;
	}
	//general error handling
	catch (...) { 
    cout << "Default exception generated. Exiting program." << endl;
		return 1;
  } 

	return 0;
}