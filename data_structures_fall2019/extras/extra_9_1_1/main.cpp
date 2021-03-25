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

/*Circular linked list: read a name, put it in a linked list, then delete every other letter, print the number of rounds taken to delete all letters.*/

// NODE ///////////////////////////////////////////////////////////////////////////////
class Letter
{
	public:
		Letter();		

		char letter;
		Letter* next;
};

// NODE CLASS FUNCTIONS ///////////////////////////////////////////////////////////////
//default constructor
Letter::Letter()
{
	letter = 'a';
	
	next = NULL;
}

// LINKED LIST CLASS //////////////////////////////////////////////////////////////////
class Name  
{  
	private: 
    Letter *head;
		Letter *tail;
  public:
	  Name();

		void AddEnd(char l);

		int DelMid(); 
		
		void Print();
};

// LIST CLASS FUNCTIONS ///////////////////////////////////////////////////////////////
//default constructor 
Name::Name()
{
	head = NULL;
	tail = NULL;
}

//adds node at end
void Name::AddEnd (char l) 
{
	Letter *newLetter = new Letter;
	newLetter->letter = l;

	//if head does not exist
	if (head == NULL) {
		//cout << "ERROR detected: Empty list found. Creating list..." << endl;
		head = tail = newLetter;
		return;
	}

	newLetter->next = tail->next;
	tail->next = newLetter;
	tail = newLetter;  
}

//removes node from middle
int Name::DelMid()
{
	//ERROR checking
	if (head == NULL) {
		cout << "ERROR detected: List is empty." << endl;
		return 1;
	}

	int counter = 0;
	int rounds = 0;

	Letter *temp = head;
	Letter *delNode;
	Letter *prev;

	while (temp != tail->next) {
		counter++;
		if (counter%2 == 0) {
			delNode = temp;
			if (delNode == tail) {
				tail = prev;
			}
			prev->next = delNode->next;
			delete delNode;
			rounds++;
		}
		prev = temp;
		temp = temp->next;
	}

	return rounds;	
}

//prints list
void Name::Print()
{
	Letter *temp = head; //CCes head pointer
	
	while (temp != tail->next) {
		cout << temp->letter;
		temp = temp->next;
	}
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	Name word;

	string input;

	cout << "\nEnter a name: ";
	cin >> input;

	for (int i=0; i<input.size(); i++) {
		word.AddEnd(input[i]);
	}

	int numRounds = word.DelMid();

	cout << "\nYour name after deletion of every other letter: ";
	word.Print();

	cout << "\n\nNumber of deletion rounds needed: " << numRounds;

	return 0;
}

