#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//FUNCTIONS////////////////////////////////////////////////////////////////////////////
//returns number of ripe kiwis in one row
int GetRipeNum (int *row, int size) {
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
	/*if (argc != 3 && argc != 2) {
		cout << "Invalid arguments" << endl;
		return 1;
	}*/

	ArgumentManager am(argc, argv);
	const string input = am.get("input");
	const string output = am.get("output");

	//init input stream
	ifstream infs(input);

	int size, temp;
	int day = 0;
	int totalRipe = 0;
	int totalRotten = 0;

	//gets size of farm
	infs >> size;

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

	return 0;
}