#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>

using namespace std;

//O(n^2) sorting algorithms with time complexity benchmarks////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

//fills array with random ints from 0 - range
void fillArray (int arr[], int size) {
	int range = 1000;
	srand(time(0));
  for (int i=0; i < size; i++) {
		arr[i] = rand()%range+1;
  }
}

//DEBUG Print
void printArrayElements (int arr[], int size) {
	for (int i=0; i < size; i++) {
				cout << arr[i] << " ";
			}
}

//prints runtimes for one sorting algorithm
void printOne(string sortName, double t100, double t1000, double t20000) {
	cout << fixed << setprecision(4);
	cout << "\n===== Runtimes for " << sortName << " =====\n\n";
	cout << "Array size of 100:    " << t100 << " seconds\n";
	cout << "Array size of 1,000:  " << t1000 << " seconds\n";
	cout << "Array size of 20,000: " << t20000 << " seconds";
}

void printAll(string sortName, double b100, double b1000, double b20000,
													     double s100, double s1000, double s20000,
													     double i100, double i1000, double i20000) {
	cout << fixed << setprecision(4);
	cout << "\n=============== Runtimes for " << sortName << " ==============\n";
	cout << "=                                                        =\n";
	cout << "=                     Bubble     Selection    Insertion  =";
	cout << "\n==========================================================\n";
	cout << "Array size of 100:    " << b100 << "s" << "     "
																	 << s100 << "s" << "     " 
																	 << i100 << "s\n\n";
	cout << "Array size of 1,000:  " << b1000 << "s" << "     "
																	 << s1000 << "s" << "     " 
																	 << i1000 << "s\n\n";
	cout << "Array size of 20,000: " << b20000 << "s" << "     "
																	 << s20000 << "s" << "     " 
																	 << i20000 << "s\n";
}

double TimeBubbleSort(int arr[], int size) { 
	//init clock obj
  clock_t start;
  start = clock();
  //sorts via bubble
	int temp;
  for (int i=0; i < size-1; i++) {      
    for (int j=0; j < size-i-1; j++) { 
      if (arr[j] > arr[j+1]) {
        temp = arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
  //returns runtime of sort
  return (double)(clock() - start)/CLOCKS_PER_SEC;
}

double TimeSelectionSort(int arr[], int size) { 
	//init clock obj
  clock_t start;
  start = clock();
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
  //returns runtime of sort
  return (double)(clock() - start)/CLOCKS_PER_SEC;
}

double TimeInsertionSort(int arr[], int size) { 
	//init clock obj
  clock_t start;
  start = clock();
  //sorts via insertion
  int key; 
  for (int i=1; i < size; i++) {  
    key = arr[i];  
    int j = i-1;  
    while (j >= 0 && arr[j] > key) {  
      arr[j+1] = arr[j];  
      j = j-1;  
    }  
      arr[j+1] = key;  
  }  
  //returns runtime of sort
  return (double)(clock() - start)/CLOCKS_PER_SEC;
}

//main menu
int menu() {
	string algoChoice; //holds user choice for menu

	//menu for selecting algorithm
	cout << "Please select one of the following options:\n";
	cout << "1. Bubble sort algorithm\n";
	cout << "2. Selection sort algorithm\n";
	cout << "3. Insertion sort algorithm\n";
	cout << "4. All algorithms\n";
	cout << "0. Exit program\n\n";
	cout << "Choice: ";

	cin >> algoChoice;

	//checks for valid input
	if (algoChoice == "1") {
		return 1;
	}
	else if (algoChoice == "2") {
		return 2;
	}
	else if (algoChoice == "3") {
		return 3;
	}
	else if (algoChoice == "4") {
		return 4;
	}
	else if (algoChoice == "0") {
		exit(0); //exits program
	}
	else {
		cout << "\nInvalid choice.\n\n";
		menu(); //loops back to menu
	}
}

int main() {
	int userChoice; //holds user choice for menu
	//holds runtimes
	double bTime100, bTime1000, bTime20000,
				 sTime100, sTime1000, sTime20000,
				 iTime100, iTime1000, iTime20000; 
	string sortChoice; //holds name of chosen algorithm
	//init arrays
	int arr100[100];
	int arr1000[1000];
	int arr20000[20000];

  cout << "\nWelcome to the benchmark program for O(n^2) sorting algorithms.\n\n";
	userChoice = menu();

	//calls appropriate function
	switch(userChoice) {
		//benchmarks bubble sort
		case 1:
			sortChoice = "Bubble Sort";
			fillArray(arr100, 100);                //fills array
			bTime100 = TimeBubbleSort(arr100, 100); //holds runtime for array
			fillArray(arr1000, 1000); 
			bTime1000 = TimeBubbleSort(arr1000, 1000); 
			fillArray(arr20000, 20000); 
			bTime20000 = TimeBubbleSort(arr20000, 20000);
			//prints output
			printOne(sortChoice, bTime100, bTime1000, bTime20000);
			cout << endl;
			//printArrayElements(arr100, 100); //DEBUG
			break;
		//benchmarks selection sort
		case 2:
			sortChoice = "Selection Sort";
			fillArray(arr100, 100);                  
			sTime100 = TimeSelectionSort(arr100, 100); 
			fillArray(arr1000, 1000); 
			sTime1000 = TimeSelectionSort(arr1000, 1000); 
			fillArray(arr20000, 20000); 
			sTime20000 = TimeSelectionSort(arr20000, 20000);
			//prints output
			printOne(sortChoice, sTime100, sTime1000, sTime20000);
			cout << endl;
			//printArrayElements(arr100, 100); //DEBUG
			break;
		//benchmarks insertion sort
		case 3:
			sortChoice = "Insertion Sort";
			fillArray(arr100, 100);         
			iTime100 = TimeInsertionSort(arr100, 100); 
			fillArray(arr1000, 1000); 
			iTime1000 = TimeInsertionSort(arr1000, 1000); 
			fillArray(arr20000, 20000); 
			iTime20000 = TimeInsertionSort(arr20000, 20000);
			//prints output
			printOne(sortChoice, iTime100, iTime1000, iTime20000);
			cout << endl;
			//printArrayElements(arr100, 100); //DEBUG
			break;
		//benchmarks all sorts
		case 4:
			sortChoice = "all algorithms";
			//bubble sort
			fillArray(arr100, 100);               
			bTime100 = TimeBubbleSort(arr100, 100);
			fillArray(arr1000, 1000); 
			bTime1000 = TimeBubbleSort(arr1000, 1000); 
			fillArray(arr20000, 20000); 
			bTime20000 = TimeBubbleSort(arr20000, 20000);
			//selection sort
			fillArray(arr100, 100);               
			sTime100 = TimeSelectionSort(arr100, 100);
			fillArray(arr1000, 1000); 
			sTime1000 = TimeSelectionSort(arr1000, 1000); 
			fillArray(arr20000, 20000); 
			sTime20000 = TimeSelectionSort(arr20000, 20000);
			//insertion sort
			fillArray(arr100, 100);               
			iTime100 = TimeInsertionSort(arr100, 100);
			fillArray(arr1000, 1000); 
			iTime1000 = TimeInsertionSort(arr1000, 1000); 
			fillArray(arr20000, 20000); 
			iTime20000 = TimeInsertionSort(arr20000, 20000);
			//prints output
			printAll(sortChoice, bTime100, bTime1000, bTime20000,
													 sTime100, sTime1000, sTime20000,
													 iTime100, iTime1000, iTime20000);
			break;
		default:
			cout << "\nERROR: Wrong input detected. Exiting program.\n"; 
			break;
	}
	
	return 0;
}