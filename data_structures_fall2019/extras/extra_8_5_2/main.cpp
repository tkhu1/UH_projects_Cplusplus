#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <math.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Rizk, Dr. Malik (textbook), and internet websites          //
///////////////////////////////////////////////////////////////////////////////////////

/*Full example of linked list (addbeg-addmid-addend-delbeg-delmid-delend): Using a dealership list of cars (color, make, year), create a list RedList of red cars and a list of Hondas HondaList, print all the operations */

// NODE CLASS /////////////////////////////////////////////////////////////////////////
class Car
{
	public:
		Car();		

		string color;
		string make;
		int year;
		Car* next;
};

// NODE CLASS FUNCTIONS ///////////////////////////////////////////////////////////////
//default constructor
Car::Car()
{
	color = "no color";
	make = "no make";
	year = 1900;
	
	next = NULL;
}

// LINKED LIST CLASS //////////////////////////////////////////////////////////////////
class Dealership
{
	public:
		//pointers
		Car *head;
		Car *tail;

		Dealership();

		void AddCarBeg(string c, string m, int y); 
		void AddCarMid(string c, string m, int y);
		void AddCarEnd(string c, string m, int y);

		void DelCarBeg(); 
		void DelCarMid(string choice, string data);
		void DelCarEnd();

		void Swap(Car *a, Car *b); 
		void Sort();
		void Print();
		Dealership CreateList(string choice, string data);
};

// LIST CLASS FUNCTIONS ///////////////////////////////////////////////////////////////
//default constructor 
Dealership::Dealership()
{
	head = NULL;
}

//adds car node at beginning 
void Dealership::AddCarBeg (string c, string m, int y) 
{
	Car *newHead = new Car;
	newHead->color = c;
	newHead->make = m;
	newHead->year = y; 

	//if head does not exist
	if (head == NULL) {
		//cout << "ERROR detected: Empty list found. Creating list..." << endl;
		newHead->next = NULL;
		head = newHead;
		return;
	}

	newHead->next = head;
	head = newHead;
}

//adds car node in middle 
void Dealership::AddCarMid (string c, string m, int y) 
{
	Car *newCar = new Car;
	newCar->color = c;
	newCar->make = m;
	newCar->year = y; 

	//if head does not exist
	if (head == NULL) {
		//cout << "ERROR detected: Empty list found. Creating list..." << endl;
		newCar->next = NULL;
		head = newCar;
		return;
	}

	//CCes first node in comparision
	Car *temp = head;
	//CCes previous node pointer
	Car *prev = head;

	int numCars=0;

	//gets number of cars in list
	while (temp != NULL) {
		numCars++;
		temp = temp->next;
	}

	//insert position at middle
	int insPos = numCars / 2;
	if (insPos == 0) {
		insPos = 1;
	}

	for (int i=0; i < insPos; i++) {
		if (prev->next != NULL)
			prev = prev->next;
	}

	//adjusts pointers
	newCar->next = prev->next;  
	prev->next = newCar;  
}

//adds car node at end
void Dealership::AddCarEnd (string c, string m, int y) 
{
	Car *newCar = new Car;
	newCar->color = c;
	newCar->make = m;
	newCar->year = y; 
	newCar->next = NULL;

	//if head does not exist
	if (head == NULL) {
		//cout << "ERROR detected: Empty list found. Creating list..." << endl;
		head = newCar;
		return;
	}

	Car *temp = head;

	//finds last node to add to
	while (temp->next != NULL) { 
		temp = temp->next;
	}

	temp->next = newCar;  
}

//removes car node from beginning
void Dealership::DelCarBeg()
{
	//ERROR checking
	if (head == NULL) {
		cout << "ERROR detected: List is empty." << endl;
		return;
	}

	Car *temp = head;
	head = temp->next;
	delete temp;
}

//removes car node from middle
void Dealership::DelCarMid(string choice, string data)
{
	//ERROR checking
	if (head == NULL) {
		cout << "ERROR detected: List is empty." << endl;
		return;
	}

	Car *temp = head;
	Car *delNode;
	Car *prev;

	if (choice == "color") {
		while (temp->next != NULL) {
			if (data == temp->color) {
				delNode = temp;
			}
			temp = temp->next;
		}
	}
	else {
		while (temp->next != NULL) {
			if (data == temp->make) {
				delNode = temp;
			}
			temp = temp->next;
		}
	}

	temp = head;

	while (temp != NULL) {
		if (temp->next == delNode) {
			prev = temp;
		}
		temp = temp->next;
	}

	prev->next = delNode->next;
	delete delNode;
}

//removes car node from end
void Dealership::DelCarEnd()
{
	Car *prev;

	Car *temp = head;

	while (temp->next != NULL) {
		prev = temp;
		temp = temp->next;
	}

	prev->next = NULL;
	delete temp;

}

//swaps data of two nodes
void Dealership::Swap(Car *a, Car *b) 
{ 
	int temp = a->year; 
	string temp2 = a->color;
	string temp3 = a->make;

	a->year = b->year; 
	a->color = b->color;
	a->make = b->make;
	
	b->year = temp; 
	b->color = temp2; 
	b->make = temp3; 
}

//sorts list by year
void Dealership::Sort()
{
	int swapped, i; 
	Car *ptr1 = NULL; 
	Car *ptr2 = NULL; 

	if (head == NULL) 
		return; 

	do
	{ 
		swapped = 0; 
		ptr1 = head; 

		while (ptr1->next != ptr2) { 
			if (ptr1->year > ptr1->next->year) {  
				Swap(ptr1, ptr1->next); 
				swapped = 1; 
			} 
			ptr1 = ptr1->next; 
		} 
		ptr2 = ptr1; 
	} 
	while (swapped); 
} 

//prints list
void Dealership::Print()
{
	Car *temp = head; //CCes head pointer
	int c = 1;
	
	while (temp != NULL) {
		cout << setfill(' ') << left << "Car " << setw(3) << c << " - Make: " << 
					  setw(7) << temp->make << " // Color: " << setw(7) << 
					  temp->color << " // Year: " << temp->year << endl;
		c++;
		temp = temp->next;
	}
}

//creates new list sorted by year
Dealership Dealership::CreateList(string choice, string data)
{
	Dealership newList;

	Car *temp = head; //CCes head pointer

	if (choice == "color") {
		while (temp != NULL) {
			if (data == temp->color) {
				newList.AddCarEnd (temp->color, temp->make, temp->year);
			}
			temp = temp->next;
		}
	}
	else if (choice == "make") {
		while (temp != NULL) {
			if (data == temp->make) {
				newList.AddCarEnd (temp->color, temp->make, temp->year);
			}
			temp = temp->next;
		}
	}
	else {
		while (temp != NULL) {
			if (stoi(data) == temp->year) {
				newList.AddCarEnd (temp->color, temp->make, temp->year);
			}
			temp = temp->next;
		}
	}
	
	newList.Sort();
	return newList;
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	Dealership store1;
	Dealership redList;
	Dealership hondaList;

	store1.AddCarEnd("Red", "Toyota", 1996);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarEnd("Blue", "Honda", 1999);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarBeg("Red", "Dodge", 1992);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarEnd("Black", "Toyota", 1993);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarBeg("Red", "Honda", 1994);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarMid("White", "Honda", 2011);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarMid("Yellow", "Nissan", 2007);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarMid("Black", "Ford", 2015);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarBeg("Red", "Nissan", 1998);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	store1.AddCarEnd("Blue", "Tesla", 2018);
	cout << "\nAdding car to inventory. The current stock is:\n\n";
	store1.Print();

	cout << "\nSorting inventory by year. The current stock is:\n\n";
	store1.Sort();
	store1.Print();

	cout << "\nDeleting first car in inventory. The current stock is:\n\n";
	store1.DelCarBeg();
	store1.Print();

	cout << "\nDeleting last car in inventory. The current stock is:\n\n";
	store1.DelCarEnd();
	store1.Print();

	cout << "\nDeleting car in inventory by color (yellow). The current stock is:\n\n";
	store1.DelCarMid("color", "Yellow");
	store1.Print();

	cout << "\nCreating a list of all red cars:\n\n";
	redList = store1.CreateList("color", "Red");
	redList.Print();

	cout << "\nCreating a list of all Honda cars:\n\n";
	hondaList = store1.CreateList("make", "Honda");
	hondaList.Print();

	return 0;
}

