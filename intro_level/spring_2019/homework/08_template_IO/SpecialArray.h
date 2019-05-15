//headers here
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef SpecialArray_H
#define SpecialArray_H

template<typename TheType>
class SpecialArray {
	public:
		//default
		SpecialArray(); 

		//constructor
		SpecialArray(int _rows, int _cols): numRows(_rows), numCols(_cols) {
			arr = new TheType* [numRows];
			for (int thisRow = 0; thisRow < numRows; thisRow++) {
				arr[thisRow] = new TheType[numCols];
			}
		}

		//RO3//////////////////////////////////////////////////////////////////////////////
		//copy constructor
		SpecialArray(const SpecialArray &other) {
			arr = new TheType* [other.numRows];
			for (int thisRow = 0; thisRow < other.numRows; thisRow++) {
				arr[thisRow] = new TheType[other.numCols];
			}
			// loops and copies 'other' array into 'arr' array
			for (int row = 0; row < other.numRows; row++) {
				for (int col = 0; col < other.numCols; col++) {
					arr[row][col] = other.arr[row][col];
				}
			}
    	// copies members   
	    numRows = other.numRows;
	  	numCols = other.numCols;
		}

		//copy assignment operator
		SpecialArray& operator=(const SpecialArray& rhs) {
			// check for self assignment 
			if (this != &rhs) { 
				delete [] arr;
				
				arr = new TheType* [rhs.numRows];
				for (int thisRow = 0; thisRow < rhs.numRows; thisRow++) {
					arr[thisRow] = new TheType[rhs.numCols];
				}
				// loops and copies 'other' array into 'arr' array
				for (int row = 0; row < rhs.numRows; row++) {
					for (int col = 0; col < rhs.numCols; col++) {
						arr[row][col] = rhs.arr[row][col];
					}
				}
				// copies members   
				numRows = rhs.numRows;
				numCols = rhs.numCols;
			}
			return *this;
		}

		//destructor
		~SpecialArray() { 
			delete [] arr;
			arr = NULL;
		}
		//FUNCTIONS////////////////////////////////////////////////////////////////////////
		//file reader
		void readFile(ifstream &input) {
			TheType inElement;

			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {
					input >> inElement;
					arr[row][col] = inElement;
					//cout << arr[row][col]; DEBUG
				}
			}
		}

		//returns max 
		TheType max() {
			TheType maxResult = arr[0][0];

			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {
					if (arr[row][col] > maxResult)
						maxResult = arr[row][col];
				}
			}
			return maxResult;
		}

		//returns min 
		TheType min() {
			TheType minResult = arr[0][0];

			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {
					if (arr[row][col] < minResult)
						minResult = arr[row][col];
				}
			}
			return minResult;
		}

		//sorts array
		void sort() {
			TheType temp;
      
			for (int row = 0; row < numRows; row++) {
				//bubble sorter
				for (int col = 1; col < numCols; col++) {
					for (int element = 0; element < numCols-1; element++) {
						if (arr[row][element] > arr[row][element+1]) {
							temp = arr[row][element];
							arr[row][element] = arr[row][element+1];
							arr[row][element+1] = temp;
						}
					}
				}
			}
		}

		//prints to display
		void print() {
			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {
					cout << arr[row][col] << " ";
				}
				cout << endl;
			}
		}

		//writes to file
		void saveToFile() {
			string outFilename = "output.txt";
			TheType output;
			//output ops
			ofstream outFile;
			outFile.open(outFilename);

			if (!outFile.is_open()) {
      			cout << "Could not open file." << endl;
   			}
	
			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {
					output = arr[row][col];
					outFile << output << " ";
				}
				outFile << endl;
			}
			outFile.close();
		}

	private:
		int numRows;
		int numCols;
		TheType **arr; //pointer for a 2D dynamic array.

};

#endif

