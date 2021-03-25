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

// NODE ///////////////////////////////////////////////////////////////////////////////
class Node
{
	public:
		Node();		

		int data;
		Node* next;
		Node* prev;
};

// NODE CLASS FUNCTIONS ///////////////////////////////////////////////////////////////
//default constructor
Node::Node()
{
	data = -1;
	
	next = NULL;
	prev = NULL;
}

// DOUBLE LINKED LIST CLASS ///////////////////////////////////////////////////////////
class DLList  
{  
	private: 
    Node *head;

  public:
	  DLList();

		void AddBeg(int info); 
		void AddMid(int key, int info);
		void AddEnd(int info);

		void DelBeg(); 
		void DelMid(int key);
		void DelEnd();

		bool Search(int key); 
		void Swap(Node *a, Node *b); 
		void Sort();
		void Print();
		void PrintReverse();
};

// LIST CLASS FUNCTIONS ///////////////////////////////////////////////////////////////
//default constructor 
DLList::DLList()
{
	head = NULL;
}

//adds node at beginning 
void DLList::AddBeg (int info) 
{
	Node *newNode = new Node;
	newNode->data = info;

	//if head does not exist
	if (head == NULL) {
		//cout << "ERROR detected: Empty list found. Creating list..." << endl;
		newNode->next = NULL;
		newNode->prev = NULL;
		head = newNode;
		return;
	}

	newNode->next = head;
	newNode->prev = NULL;
	head->prev = newNode;
	head = newNode;
}

//adds node in middle 
void DLList::AddMid (int key, int info) 
{
	Node *newNode = new Node;
	newNode->data = info;

	//if head does not exist
	if (head == NULL) {
		//cout << "ERROR detected: Empty list found. Creating list..." << endl;
		newNode->next = NULL;
		newNode->prev = NULL;
		head = newNode;
		return;
	}

	//CCes head
	Node *temp = head;

	while (temp != NULL) {
		if (temp->data == key) {
			//adjusts pointers
			newNode->next = temp->next;  
			newNode->prev = temp;
			temp->next->prev = newNode;
			temp->next = newNode;
			return;
		}
		temp = temp->next;
	}
}

//adds node at end
void DLList::AddEnd (int info) 
{
	Node *newNode = new Node;
	newNode->data = info;

	//if head does not exist
	if (head == NULL) {
		//cout << "ERROR detected: Empty list found. Creating list..." << endl;
		newNode->next = NULL;
		newNode->prev = NULL;
		head = newNode;
		return;
	}

	Node *temp = head;

	//finds last node to add to
	while (temp->next != NULL) { 
		temp = temp->next;
	}

	newNode->next = NULL;
	newNode->prev = temp;
	temp->next = newNode;
}

//removes node from beginning
void DLList::DelBeg()
{
	//ERROR checking
	if (head == NULL) {
		cout << "ERROR detected: List is empty." << endl;
		return;
	}

	Node *temp = head;
	head = temp->next;
	head->prev = NULL;
	delete temp;
}

//removes node from middle
void DLList::DelMid(int key)
{
	//ERROR checking
	if (head == NULL) {
		cout << "ERROR detected: List is empty." << endl;
		return;
	}

	Node *temp = head;
	Node *delNode;

	while (temp != NULL) {
		if (temp->data == key) {
			//adjusts pointers
			delNode = temp;
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			delete delNode;
			return;
		}
		temp = temp->next;
	}
}

//removes node from end
void DLList::DelEnd()
{
	//ERROR checking
	if (head == NULL) {
		cout << "ERROR detected: List is empty." << endl;
		return;
	}

	Node *temp = head;

	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->prev->next = NULL;
	delete temp;
}

//searches list for data
bool DLList::Search(int key) 
{
	Node *temp = head; //CCes head pointer
	
	while (temp != NULL) {
		if (temp->data == key)
			return true;
		temp = temp->next;
	}
	return false;
} 

//swaps data of two nodes
void DLList::Swap(Node *a, Node *b) 
{ 
	int temp = a->data; 
	a->data = b->data; 
	b->data = temp;
}

//sorts list by year
void DLList::Sort()
{
	int swapped, i; 
	Node *ptr1 = NULL; 
	Node *ptr2 = NULL; 

	if (head == NULL) 
		return; 

	do
	{ 
		swapped = 0; 
		ptr1 = head; 

		while (ptr1->next != ptr2) { 
			if (ptr1->data > ptr1->next->data) {  
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
void DLList::Print()
{
	Node *temp = head; //CCes head pointer
	
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
}

//prints list in reverse
void DLList::PrintReverse()
{
	Node *temp = head; //CCes head pointer
	
	while (temp->next != NULL) {
		temp = temp->next;
	}

	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->prev;
	}
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	DLList list;

	bool isFound;

	list.AddEnd(18);
	cout << " \n\nAdding number. The current list is: ";
	list.Print();

	list.AddEnd(5);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddBeg(11);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddEnd(1);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddBeg(6);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddMid(11, 7);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddMid(7, 3);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddMid(5, 9);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddBeg(17);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	list.AddEnd(4);
	cout << "\n\nAdding number. The current list is: ";
	list.Print();

	cout << "\n\nSorting list. The current list is: ";
	list.Sort();
	list.Print();

	cout << "\n\nList in reverse: ";
	list.PrintReverse();

	cout << "\n\nSearching for number (9): ";
	isFound = list.Search(9);
	if (isFound)
		cout << "Number found!";
	else
		cout << "Number not found!";

	cout << "\n\nSearching for number (20): ";
	isFound = list.Search(20);
	if (isFound)
		cout << "Number found!";
	else
		cout << "Number not found!";

	cout << "\n\nDeleting number at beginning. The current list is: ";
	list.DelBeg();
	list.Print();

	cout << "\n\nDeleting number at end. The current list is: ";
	list.DelEnd();
	list.Print();

	cout << "\n\nDeleting number in middle (7). The current list is: ";
	list.DelMid(7);
	list.Print();

	cout << "\n\nList in reverse: ";
	list.PrintReverse();

	cout << "\n\nSearching for number (7): ";
	isFound = list.Search(7);
	if (isFound)
		cout << "Number found!";
	else
		cout << "Number not found!";

	cout << "\n\nSearching for number (5): ";
	isFound = list.Search(5);
	if (isFound)
		cout << "Number found!";
	else
		cout << "Number not found!";

	return 0;
}

