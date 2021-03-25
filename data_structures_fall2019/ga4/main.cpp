#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHORS: TYLER HU,     ID: 0276538                                                //
//          ARMANDO MATA, ID: 1656706                                                //
//																																									 //
// Inspired by code from Dr. Malik (textbook), Sunny (TA) & Geek4Geeks               //
///////////////////////////////////////////////////////////////////////////////////////

// CLASSES ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class UnsortedArray
{
	public:
		int *arr;
		int count; //number of elements in the array
		int size;  //max size of the array

		//constructor
		UnsortedArray(int size) 
		{
			this->count = 0;
			this->size = size;
			this->arr = new int[size];
			for (int i=0; i < size; i++) {
				arr[i] = 0;
			}
		}

		//returns true boolean value if input value is added to array
		bool insert(int val) 
		{
			//checks if array is full
			if (count >= size) {
				cout << "\nERROR: Cannot add to full unsorted array.\n";
				return false;
			}
			
			for (int i = 0; i < size; i++) {
				if (arr[i] == 0) {
					arr[i] = val;
					//increments counter of number of elements
					++count;
					return true;
				}
			}
			//default return
			return false;
		}
		
		//returns true boolean value if value is found
		bool search(int val) 
		{
			for (int i = 0; i < size; i++) {
				if (arr[i] == val)
					return true;
			}
			//if value not found
			return false;
		}
		
		//returns true bool value if element is deleted from array
		bool remove(int val) 
		{
			for (int i = 0; i < size; i++) {
				if (arr[i] == val) {
					arr[i] = 0;
					count--;
					return true;
				}
			}
			//element to be deleted not found
			return false;
		}
		
		//displays array
		void print() 
		{
			cout << "Unsorted array: ";
			for (int i = 0; i < size; i++) {
				cout << arr[i] << " ";
			}
			cout << endl;
		}
};

///////////////////////////////////////////////////////////////////////////////////////
class SortedArray
{
	public:
		int *arr;
		int count; //number of elements in the array
		int size;  //max size of the array

		//constructor
		SortedArray(int size) 
		{
			this->count = 0;
			this->size = size;
			this->arr = new int[size];
			for (int i=0; i < size; i++) {
				arr[i] = 0;
			}
		}

		//returns true boolean value if input value is added to array
		bool insert(int val) 
		{
			//checks if array is full
			if (count >= size) {
				cout << "\nERROR: Cannot add to full sorted array.\n";
				return false;
			}
			
			for (int i = 0; i < size; i++) {
				if (arr[i] == 0) {
					arr[i] = val;
					//increments counter of number of elements
					++count;
					return true;
				}
			}
			//default return
			return false;
		}
		
		//returns true boolean value if value is found
		bool search(int val) 
		{
			for (int i = 0; i < size; i++) {
				if (arr[i] == val)
					return true;
			}
			//if value not found
			return false;
		}
		
		//returns true bool value if element is deleted from array
		bool remove(int val) 
		{
			for (int i = 0; i < size; i++) {
				if (arr[i] == val) {
					arr[i] = 0;
					count--;
					return true;
				}
			}
			//element to be deleted not found
			return false;
		}
		
		//displays array
		void print() 
		{
			cout << "Sorted array: ";
			for (int i = 0; i < size; i++) {
				cout << arr[i] << " ";
			}
			cout << endl;
		}
};

///////////////////////////////////////////////////////////////////////////////////////
class HashTable 
{
	public:
		int *arr;  //dynamic array of hash values
		int count; //number of elements in the hash table
		int size;  //max size of the hash table
		
		//constructor
		HashTable(int size) 
		{
			this->count = 0;
			this->size = size;
			this->arr = new int[size];
			for (int i=0; i < size; i++) {
				arr[i] = 0;
			}
		}
		
		//returns hash index of input int
		int getHash(int val) 
		{
			return (val % 17);
		}
		
		//returns true boolean if hash index is added successfully to hash table
		bool insert(int val) 
		{
			//checks if hash table is full
			if (count >= size) {
				cout << "\nERROR: Cannot add to full hash table.\n";
				return false;
			}
			
			//gets hash index value
			int hashIdx = getHash(val);
			
			//linear probing
			//if hash array position is empty
			if (arr[hashIdx] == 0)
				arr[hashIdx] = val;
			//else finds next empty position 
			else {
				int index = hashIdx + 1;
				
				while (index != hashIdx) {
					if (arr[index] == 0) {
						arr[index] = val;
						break;
					}
						
					index++;
					index %= size;
				}
			}
			//increments counter of number of elements
			++count;
			return true;
		}
		
		//returns true boolean value if value is found
		bool search(int val) 
		{
			//gets hash index value
			int hashIdx = getHash(val);
			
			if (arr[hashIdx] == val)
				return true;
			
			//linear probing
			//loops through hash table array
			int index = hashIdx + 1;
			while (index != hashIdx) {
				if (arr[index] == val)
					return true;
					
				index++;
				index %= size;
			}
			
			return false;
		}
		
		//returns true boolean value if element is deleted
		bool remove(int val) 
		{
			int hashIdx = getHash(val);
			
			if (arr[hashIdx] == val) {
				//resets value at hash index
				arr[hashIdx] = 0;
				//decrements counter of number of elements
				--count;
				return true;
			}
			
			//linear probing
			//loops through hash table array
			int index = hashIdx + 1;
			while (index != hashIdx) {
				if (arr[index] == val) {
					arr[index] = 0;
					--count;
					return true;
				}
				
				index++;
				index %= size;
			}
			//element to be deleted not found
			return false;
		}
		
		//displays hash table array
		void print() 
		{
			cout << "Hash table array: ";
			for (int i = 0; i < size; i++) {
				cout << arr[i] << " ";
			}
			cout << endl;
		}
		
};

// MAIN FUNCTIONS /////////////////////////////////////////////////////////////////////

//sorts via selection sort
void selectionSort(int arr[], int size) 
{ 
  //sorts via selection
  int temp, min;
  for (int i=0; i < size-1; i++) {
    min = i;
    for (int j = i+1; j < size; j++) {
      if (arr[j] < arr[min]) 
				min = j;
    }
    temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
  }
}

//fills array with random ints from 1 - range
void fillArray(int arr[], int size, int range) 
{
	srand(time(0));
	for (int i=0; i < size; i++) {
		if (arr[i] == 0) {
			int num = rand()%range+1;
			//rerolls duplicate numbers
			for (int j=0; j < size; j++) {
				if (num == arr[j]) {
					num = rand()%range+1;
				}
			}
			arr[i] = num;
		}
	}
}

//reads input file and puts data into array
void inputRead(int arr[], int size) 
{
	int num = 0;
	//init output stream
	ifstream infs("input.txt");

	for (int i = 0; i < size; i++) {
		infs >> num;
		if (num != 0)
			arr[i] = num;
	}

	infs.close();
}

//prints runtimes for one command
void printTime(string command, int val, double unsArrT, double sortedArrT, 
double hashTT) 
{
	//formatting
	if (command == "Deleting") {
		cout << endl;
		cout << fixed << setprecision(10);
		cout << setfill(' ') << command << " " << left << setw(10) << val << setw(20) << 
						"Unsorted Array" << unsArrT << " sec\n";
		cout << setfill(' ') << right << setw(31) << "Sorted Array" << left << setw(8) <<
						" " << sortedArrT << " sec\n";					
		cout << setfill(' ') << right << setw(29) << "Hash Table" << left << setw(10) << 
						" " << hashTT << " sec\n";				

		//init output stream
		ofstream outfs("output.txt", fstream::app);

		outfs << endl;
		outfs << fixed << setprecision(10);
		outfs << setfill(' ') << command << " " << left << setw(10) << val << setw(20) << 
						"Unsorted Array" << unsArrT << " sec\n";
		outfs << setfill(' ') << right << setw(31) << "Sorted Array" << left << setw(8) <<
						" " << sortedArrT << " sec\n";					
		outfs << setfill(' ') << right << setw(29) << "Hash Table" << left << setw(10) << 
						" " << hashTT << " sec\n";				

		outfs.close();
	}
	else {
		cout << endl;
		cout << fixed << setprecision(10);
		cout << setfill(' ') << command << " " << left << setw(10) << val << setw(20) << 
						"Unsorted Array" << unsArrT << " sec\n";
		cout << setfill(' ') << right << setw(32) << "Sorted Array" << left << setw(8) <<
						" " << sortedArrT << " sec\n";					
		cout << setfill(' ') << right << setw(30) << "Hash Table" << left << setw(10) << 
						" " << hashTT << " sec\n";				

		//init output stream
		ofstream outfs("output.txt", fstream::app);

		outfs << endl;
		outfs << fixed << setprecision(10);
		outfs << setfill(' ') << command << " " << left << setw(10) << val << setw(20) << 
						"Unsorted Array" << unsArrT << " sec\n";
		outfs << setfill(' ') << right << setw(32) << "Sorted Array" << left << setw(8) <<
						" " << sortedArrT << " sec\n";					
		outfs << setfill(' ') << right << setw(30) << "Hash Table" << left << setw(10) << 
						" " << hashTT << " sec\n";				

		outfs.close();
	}
}

//prints runtimes for multiple commands
void printTimeMulti(string command, double unsArrT, double sortedArrT, double hashTT) 
{
	string val;
	//formatting
	if (command == "Deleting") {
		val = "all        ";
	}
	else {
		val = "all";
	}
	cout << endl;
	cout << fixed << setprecision(10);
	cout << setfill(' ') << command << " " << left << setw(10) << val << setw(20) << 
					"Unsorted Array" << unsArrT << " sec\n";
	cout << setfill(' ') << right << setw(32) << "Sorted Array" << left << setw(8) <<
					" " << sortedArrT << " sec\n";					
	cout << setfill(' ') << right << setw(30) << "Hash Table" << left << setw(10) << 
					" " << hashTT << " sec\n";				

	//init output stream
	ofstream outfs("output.txt", fstream::app);

	outfs << endl;
	outfs << fixed << setprecision(10);
	outfs << setfill(' ') << command << " " << left << setw(10) << val << setw(20) << 
					"Unsorted Array" << unsArrT << " sec\n";
	outfs << setfill(' ') << right << setw(32) << "Sorted Array" << left << setw(8) <<
					" " << sortedArrT << " sec\n";					
	outfs << setfill(' ') << right << setw(30) << "Hash Table" << left << setw(10) << 
					" " << hashTT << " sec\n";				

	outfs.close();
}

//main menu
void menu(bool ifFirstRun, int size, int range, UnsortedArray &unsArr, 
					SortedArray &sortedArr, HashTable &hashT) 
{
	int userVal = 0;                                       //holds user input
	int intChoice = 0;																		 //holds int menu choice
	int numAdded = 0;                                      //holds number of insertions
	double unsortedArrT, sortedArrT, hashTableT;           //holds runtimes
	bool ifUnsArrInsert, ifSortedArrInsert, ifHashTInsert; //holds success flags
	bool ifUnsArrFound, ifSortedArrFound, ifHashTFound;    //holds success flags
	bool ifUnsArrDel, ifSortedArrDel, ifHashTDel;          //holds success flags
	string sortChoice = ""; 								    			     //holds name of command
	string menuChoice = "";															   //holds string menu choice
	int tempArr[size];                                     //helper array

	//menu for selecting command
	cout << "\nPlease select one of the following options:\n";
	cout << "1. Insert one integer value\n";
	cout << "2. Fills the rest of the arrays with unique random values\n";
	cout << "3. Search for a value\n";
	cout << "4. Delete one value\n";
	cout << "5. Delete ALL values\n";
	cout << "0. Exit program\n\n";
	cout << "Choice: ";

	cin >> menuChoice;

	//checks for valid input
	if (menuChoice == "1") {
		intChoice = 1;
	}
	else if (menuChoice == "2") {
		intChoice = 2;
	}
	else if (menuChoice == "3") {
		intChoice = 3;
	}
	else if (menuChoice == "4") {
		intChoice = 4;
	}
	else if (menuChoice == "5") {
		intChoice = 5;
	}
	else if (menuChoice == "0") {
		cout << "\nExiting program.";
		exit(0); //exits program
	}
	else {
		cout << "\nERROR: Invalid choice. Please try again.\n";
		menu(ifFirstRun, size, range, unsArr, sortedArr, hashT); //calls menu
	}

	//calls appropriate command
	switch (intChoice) {
		//benchmarks insertion of one value
		case 1:
			cout << "\nPlease enter a non-zero value to be inserted (0 to go back): ";
			cin >> userVal;
			//checks for valid input
			while (cin.fail()) {
        cout << "\nERROR: invalid input detected. Must be an integer." << endl;
        cin.clear();
        cin.ignore(256,'\n');
				cout << "\nPlease enter a non-zero value to be inserted (0 to go back): ";
        cin >> userVal;
				cout << endl;
			}
			//calls main menu
			if (userVal == 0) {
				menu(ifFirstRun, size, range, unsArr, sortedArr, hashT);
				break;
			}

			sortChoice = "Inserting";

			//init unsorted array clock obj
			clock_t unsArrClock;
			unsArrClock = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifUnsArrInsert = unsArr.insert(tempArr[i]);
					}
				}
			}
			//inserts into unsorted array
			ifUnsArrInsert = unsArr.insert(userVal);
			//checks if insertion was successful
			if (ifUnsArrInsert) {
				unsortedArrT = (double)(clock() - unsArrClock)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << unsortedArrT << endl; //DEBUG
			}
			else {
				unsortedArrT = (double)(clock() - unsArrClock)/CLOCKS_PER_SEC;
				cout << "\nERROR: Insertion of specified value (" << userVal <<
								") into unsorted array failed.\n";
			}

			//init sorted array clock obj
			clock_t sortedArrClock;
			sortedArrClock = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifSortedArrInsert = sortedArr.insert(tempArr[i]);
					}
				}
			}
			//inserts into sorted array
			ifSortedArrInsert = sortedArr.insert(userVal);
			//sorts
			selectionSort(sortedArr.arr, sortedArr.count);
			//checks if insertion was successful
			if (ifSortedArrInsert) {
				sortedArrT = (double)(clock() - sortedArrClock)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << sortedArrT << endl; //DEBUG
			}
			else {
				sortedArrT = (double)(clock() - sortedArrClock)/CLOCKS_PER_SEC;
				cout << "\nERROR: Insertion of specified value (" << userVal <<
								") in sorted array failed.\n";
			}			

			//init hash table clock obj
			clock_t hashTClock;
			hashTClock = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifHashTInsert = hashT.insert(tempArr[i]);
					}
				}
			}
			//inserts into hash table
			ifHashTInsert = hashT.insert(userVal);
			//checks if insertion was successful
			if (ifHashTInsert) {
				hashTableT = (double)(clock() - hashTClock)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nht time: " << hashTableT << endl; //DEBUG
			}
			else {
				hashTableT = (double)(clock() - hashTClock)/CLOCKS_PER_SEC;
				cout << "\nERROR: Insertion of specified value (" << userVal <<
								") in hash table failed.\n\nReturning to main menu...\n";
			}

			//prints output
			printTime(sortChoice, userVal, unsortedArrT, sortedArrT, hashTableT);
			cout << endl << endl;

			unsArr.print(); //DEBUG
			cout << endl;
			sortedArr.print();
			cout << endl;
			hashT.print(); //DEBUG
			cout << endl;

			//sets first run flag
			ifFirstRun = false;

			break;

		//benchmarks insertion of the rest of the values up til max size
		case 2:
			sortChoice = "Inserting";

			//init unsorted array clock obj
			clock_t unsArrClock2;
			unsArrClock2 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifUnsArrInsert = unsArr.insert(tempArr[i]);
					}
				}
			}
			//inserts random nums into unsorted array
			if (unsArr.count < size) {
				fillArray(unsArr.arr, size, range);
				unsArr.count = size;
				ifUnsArrInsert = true;
			}
			else {
				ifUnsArrInsert = false;
			}
			//checks if insertion was successful
			if (ifUnsArrInsert) {
				unsortedArrT = (double)(clock() - unsArrClock2)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << unsortedArrT << endl; //DEBUG
			}
			else {
				unsortedArrT = (double)(clock() - unsArrClock2)/CLOCKS_PER_SEC;
				cout << "\nERROR: Insertions of random values in arrays failed.\n" <<
								"\nReturning to main menu...\n";
			}

			//init sorted array clock obj
			clock_t sortedArrClock2;
			sortedArrClock2 = clock();
			//copies unsorted array into temp array
			for (int i = 0; i < size; i++) {
				tempArr[i] = unsArr.arr[i];
			}			
			//resets sorted array
			for (int i = 0; i < size; i++) {
				sortedArr.arr[i] = 0;
			}
			//resets sorted array count
			sortedArr.count = 0;
			//reinserts into sorted array
			for (int i = 0; i < size; i++) {
				ifSortedArrInsert = sortedArr.insert(tempArr[i]);
			}
			//checks for valid arrays
			if (ifSortedArrInsert) {
				//sorts
				selectionSort(sortedArr.arr, sortedArr.count);
			}
			else {
				ifSortedArrInsert = false;
			}
			//checks if insertion was successful
			if (ifSortedArrInsert) {
				sortedArrT = (double)(clock() - sortedArrClock2)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << sortedArrT << endl; //DEBUG
			}
			else {
				sortedArrT = (double)(clock() - sortedArrClock2)/CLOCKS_PER_SEC;
			}			

			//init hash table clock obj
			clock_t hashTClock2;
			hashTClock2 = clock();
			//resets hash table array
			for (int i = 0; i < size; i++) {
				hashT.arr[i] = 0;
			}
			//resets hash tables count
			hashT.count = 0;
			//re-inserts into hash table
			for (int i = 0; i < size; i++) {
				ifHashTInsert = hashT.insert(tempArr[i]);
			}
			//checks if insertion was successful
			if (ifHashTInsert) {
				hashTableT = (double)(clock() - hashTClock2)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nht time: " << hashTableT << endl; //DEBUG
			}
			else {
				hashTableT = (double)(clock() - hashTClock2)/CLOCKS_PER_SEC;
			}

			//prints output
			printTimeMulti(sortChoice, unsortedArrT, sortedArrT, hashTableT);
			cout << endl << endl;

			unsArr.print(); //DEBUG
			cout << endl;
			sortedArr.print();
			cout << endl;
			hashT.print(); //DEBUG
			cout << endl;

			//sets first run flag
			ifFirstRun = false;

			break;

		//searches for a value
		case 3:
			cout << "\nPlease enter a non-zero value to be searched (0 to go back): ";
			cin >> userVal;
			//checks for valid input
			while (cin.fail()) {
        cout << "\nERROR: invalid input detected. Must be an integer." << endl;
        cin.clear();
        cin.ignore(256,'\n');
				cout << "\nPlease enter a non-zero value to be searched (0 to go back): ";
        cin >> userVal;
				cout << endl;
			}
			//calls main menu
			if (userVal == 0) {
				menu(ifFirstRun, size, range, unsArr, sortedArr, hashT);
				break;
			}

			sortChoice = "Searching";

			//init unsorted array clock obj
			clock_t unsArrClock3;
			unsArrClock3 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifUnsArrFound = unsArr.insert(tempArr[i]);
					}
				}
			}
			//searches for value
			ifUnsArrFound = unsArr.search(userVal);
			//checks if insertion was successful
			if (ifUnsArrFound) {
				cout << "\nValue found (" << userVal << ").\n";
				unsortedArrT = (double)(clock() - unsArrClock3)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << unsortedArrT << endl; //DEBUG
			}
			else {
				unsortedArrT = (double)(clock() - unsArrClock3)/CLOCKS_PER_SEC;
				cout << "\nDid not find search value in unsorted array (" << userVal << ").\n";
			}

			//init sorted array clock obj
			clock_t sortedArrClock3;
			sortedArrClock3 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifSortedArrFound = sortedArr.insert(tempArr[i]);
					}
				}
				//sorts
				selectionSort(sortedArr.arr, sortedArr.count);
			}
			//searches for value
			ifSortedArrFound = sortedArr.search(userVal);
			//checks if insertion was successful
			if (ifSortedArrFound) {
				sortedArrT = (double)(clock() - sortedArrClock3)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << sortedArrT << endl; //DEBUG
			}
			else {
				sortedArrT = (double)(clock() - sortedArrClock3)/CLOCKS_PER_SEC;
				cout << "\nDid not find search value in sorted array (" << userVal << ").\n";
			}			

			//init hash table clock obj
			clock_t hashTClock3;
			hashTClock3 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifHashTFound = hashT.insert(tempArr[i]);
					}
				}
			}
			//searches for value
			ifHashTFound = hashT.search(userVal);
			//checks if insertion was successful
			if (ifHashTFound) {
				hashTableT = (double)(clock() - hashTClock3)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nht time: " << hashTableT << endl; //DEBUG
			}
			else {
				hashTableT = (double)(clock() - hashTClock3)/CLOCKS_PER_SEC;
				cout << "\nDid not find search value in hash table (" << userVal << ").\n";
			}

			//prints output
			printTime(sortChoice, userVal, unsortedArrT, sortedArrT, hashTableT);
			cout << endl << endl;

			unsArr.print(); //DEBUG
			cout << endl;
			sortedArr.print();
			cout << endl;
			hashT.print(); //DEBUG
			cout << endl;

			//sets first run flag
			ifFirstRun = false;

			break;

		//deletes one value
		case 4:
			cout << "\nPlease enter a non-zero value to be deleted (0 to go back): ";
			cin >> userVal;
			//checks for valid input
			while (cin.fail()) {
        cout << "\nERROR: invalid input detected. Must be an integer." << endl;
        cin.clear();
        cin.ignore(256,'\n');
				cout << "\nPlease enter a non-zero value to be deleted (0 to go back): ";
        cin >> userVal;
				cout << endl;
			}
			//calls main menu
			if (userVal == 0) {
				menu(ifFirstRun, size, range, unsArr, sortedArr, hashT);
				break;
			}

			sortChoice = "Deleting";

			//init unsorted array clock obj
			clock_t unsArrClock4;
			unsArrClock4 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifUnsArrDel = unsArr.insert(tempArr[i]);
					}
				}
			}
			//deletes into unsorted array
			ifUnsArrDel = unsArr.remove(userVal);
			//checks if deletion was successful
			if (ifUnsArrDel) {
				unsortedArrT = (double)(clock() - unsArrClock4)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << unsortedArrT << endl; //DEBUG
			}
			else {
				unsortedArrT = (double)(clock() - unsArrClock4)/CLOCKS_PER_SEC;
				cout << "\n\nERROR: Deletion of specified value (" << userVal <<
								") in unsorted array failed.\n";
			}

			//init sorted array clock obj
			clock_t sortedArrClock4;
			sortedArrClock4 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifSortedArrDel = sortedArr.insert(tempArr[i]);
					}
				}
				//sorts
				selectionSort(sortedArr.arr, sortedArr.count);
			}
			//deletes into unsorted array
			ifSortedArrDel = sortedArr.remove(userVal);
			//checks if deletion was successful
			if (ifSortedArrDel) {
				//sorts
				selectionSort(sortedArr.arr, sortedArr.count);
				sortedArrT = (double)(clock() - sortedArrClock4)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << sortedArrT << endl; //DEBUG
			}
			else {
				sortedArrT = (double)(clock() - sortedArrClock4)/CLOCKS_PER_SEC;
				cout << "\n\nERROR: Deletion of specified value (" << userVal <<
								") in sorted array failed.\n";
			}			

			//init hash table clock obj
			clock_t hashTClock4;
			hashTClock4 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifHashTDel = hashT.insert(tempArr[i]);
					}
				}
			}
			//deletes into hash table
			ifHashTDel = hashT.remove(userVal);
			//checks if deletion was successful
			if (ifHashTDel) {
				hashTableT = (double)(clock() - hashTClock4)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nht time: " << hashTableT << endl; //DEBUG
			}
			else {
				hashTableT = (double)(clock() - hashTClock4)/CLOCKS_PER_SEC;
				cout << "\n\nERROR: Deletion of specified value (" << userVal <<
								") in hash table failed.\n\nReturning to main menu...\n";
			}

			//prints output
			printTime(sortChoice, userVal, unsortedArrT, sortedArrT, hashTableT);
			cout << endl << endl;

			unsArr.print(); //DEBUG
			cout << endl;
			sortedArr.print();
			cout << endl;
			hashT.print(); //DEBUG
			cout << endl;

			//sets first run flag
			ifFirstRun = false;

			break;

		//deletes all values
		case 5:
			sortChoice = "Deleting";

			//init unsorted array clock obj
			clock_t unsArrClock5;
			unsArrClock5 = clock();
			//checks for first run
			if (ifFirstRun) {
				//init temp array elements
				for (int i=0; i < size; i++) {
					tempArr[i] = 0;
				}
				inputRead(tempArr, size);
				//cout << "Counter: " << unsArr.count << endl; //DEBUG
				for (int i=0; i < size; i++) {
					if (tempArr[i] != 0) {
					//inserts input file into unsorted array
					ifUnsArrDel = unsArr.insert(tempArr[i]);
					}
				}
			}
			//sets all elements to 0
			if (unsArr.count > 0) {
				//resets array
				for (int i = 0; i < size; i++) {
					unsArr.arr[i] = 0;
				}
				//resets array count
				unsArr.count = 0;
				ifUnsArrDel = true;
			}
			else {
				ifUnsArrDel = false;
			}
			//checks if deletion was successful
			if (ifUnsArrDel) {
				unsortedArrT = (double)(clock() - unsArrClock5)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << unsortedArrT << endl; //DEBUG
			}
			else {
				unsortedArrT = (double)(clock() - unsArrClock5)/CLOCKS_PER_SEC;
				cout << "\nERROR: Deletions of values in arrays failed - " <<
								"arrays are already empty.\n\nReturning to main menu...\n";
			}

			//init sorted array clock obj
			clock_t sortedArrClock5;
			sortedArrClock5 = clock();
			//sets all elements to 0
			if (sortedArr.count > 0) {
				//resets array
				for (int i = 0; i < size; i++) {
					sortedArr.arr[i] = 0;
				}
				//resets array count
				sortedArr.count = 0;
				ifSortedArrDel = true;
			}
			else {
				ifSortedArrDel = false;
			}
			//checks if deletion was successful
			if (ifSortedArrDel) {
				sortedArrT = (double)(clock() - sortedArrClock5)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << unsortedArrT << endl; //DEBUG
			}
			else {
				sortedArrT = (double)(clock() - sortedArrClock5)/CLOCKS_PER_SEC;
			}

			//init hash table clock obj
			clock_t hashTClock5;
			hashTClock5 = clock();
			//sets all elements to 0
			if (hashT.count > 0) {
				//resets array
				for (int i = 0; i < size; i++) {
					hashT.arr[i] = 0;
				}
				//resets array count
				hashT.count = 0;
				ifHashTDel = true;
			}
			else {
				ifHashTDel = false;
			}
			//checks if deletion was successful
			if (ifHashTDel) {
				hashTableT = (double)(clock() - hashTClock5)/CLOCKS_PER_SEC; //gets runtime
				//cout << "\nUns time: " << unsortedArrT << endl; //DEBUG
			}
			else {
				hashTableT = (double)(clock() - hashTClock5)/CLOCKS_PER_SEC;
			}

			//prints output
			printTimeMulti(sortChoice, unsortedArrT, sortedArrT, hashTableT);
			cout << endl << endl;

			unsArr.print(); //DEBUG
			cout << endl;
			sortedArr.print();
			cout << endl;
			hashT.print(); //DEBUG
			cout << endl;

			//sets first run flag
			ifFirstRun = false;

			break;

		default:
			cout << "\nERROR: Wrong input detected. Please try again."; 
			break;
	}
	//calls main menu
	menu(ifFirstRun, size, range, unsArr, sortedArr, hashT); 
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//CHANGE THIS TO GET NEW MAX ARRAY SIZE
	const int MAX = 20;
	//CHANGE THIS TO GET NEW INTS FROM 1 - RANGE
	const int range = 100;

	bool firstRun = true; //flag to set first run of program

	//init classes
	UnsortedArray unsArr(MAX);
	SortedArray sortedArr(MAX);
	HashTable hashT(MAX);

	ifstream infs("input.txt");

	//exits if input not found and writes error to output
	if (!infs) {
		cout << "ERROR: input file not found." << endl;
		return 1;
	}

	infs.close();

	//clears output file (inspired by stack overflow website)
	ofstream outfs;
  outfs.open("output.txt", ofstream::out | ofstream::trunc);
	outfs.close();

	cout << "\nWelcome to the benchmark program for hash tables.\n\n";

	//calls main menu
	menu(firstRun, MAX, range, unsArr, sortedArr, hashT);

	return 0;
}