#include <iostream>
#include <string>

using namespace std;

//node template
template <typename T>
class Node { 
	public:
    T data; 
    Node<T> *link; 

		//default constructor
    Node<T>()
    {
			this->data = -1;
			this->link = NULL;
    }
};

//linked list node template
template <typename T>  
class LLstack { 
	public:
		//pointer to top of stack
    Node<T> *top; 

		//default constructor
		LLstack()
		{
			this->top = NULL;
		}

		//reinit stack to empty
		void reinitStack ()
		{
			//pointer to delete node
			Node<T> *temp;

			//while there are elements in the stack
			while (top != NULL) {
				temp = top;
				top = top->link; 

				delete temp;
			}
		}

		//checks if stack is empty
		bool isEmpty () const
		{
			if (top == NULL)
				return true; 
			else
				return false;
		}

		//returns false as linked list is never full
		bool isFull () const
		{
			return false;
		}

		//adds data node to top of stack
		void push(T newData) 
		{
			//pointer to create the new node
			Node<T> *newNode = new Node<T>;

			newNode->data = newData; //copies data into node
			newNode->link = top;     //insert newNode before top of stack
			top = newNode;           //set top pointer to the new top node
		}

		//removes data node from top of stack
		void pop() 
		{
			//error checking
			if (top == NULL) 
				return;

			//pointer to delete node
			Node<T> *temp;

			//checks if stack is empty
			if (top != NULL)
			{ 
				temp = top;      //set temp to point to the top node
			  top = top->link; //moves top pointer to next node

				delete temp; //deletes top node
			}
			else
				cout << "\nCannot remove from an empty stack." << endl;
		}

		//returns pointer to top node in stack
		Node<T> *peek()
		{
			//checks for empty stack 
    	if (!isEmpty()) 
        return top; 
    	else
				cout << "\nCannot peek at empty stack." << endl; 
        exit(0);
		}

		//reverses stack
		void reverser()
		{
			//error checking
			if (top == NULL) 
				return;

			//init reverse stack to store elements of original stack
			LLstack<T> revStack; 
  
			//pushes elements of list to reverse stack 
			Node<T> *ptr = top; 
			while (ptr != NULL) { 
				revStack.push(ptr->data); 
				ptr = ptr->link; 
			} 
			ptr = top; 

			//revStack.print(); DEBUG

			//pops from stack and replace current nodes value 
			while (!revStack.isEmpty()) { 
				ptr->data = (revStack.peek())->data; 
				revStack.pop();
				ptr = ptr->link; 
			} 
			//sets last node link to NULL
			ptr = NULL; 
		}

		//prints stack data
		void print()
		{
			//pointer to traverse stack
			Node<T> *temp; 

			// checks for empty stack 
			if (top == NULL) { 
				cout << "\nCannot print empty stack." << endl;  
			} 
   		 else { 
        temp = top; 
        while (temp != NULL) {
					// print node data 
					cout << temp->data << " "; 

					temp = temp->link; 
        } 
				cout << endl;
    	} 
		}

}; 

int main () 
{
	//init stack
	LLstack<int> stackInt; 
	LLstack<double> stackDouble; 
	LLstack<char> stackChar; 
	LLstack<string> stackString; 

	//stack of ints//////////////////////////////////////////////////////////////////////
	stackInt.push(1);
	stackInt.push(2);
	stackInt.push(3);
	stackInt.push(4);

	cout << "\nInt Max stack: ";
	stackInt.print();

	stackInt.reverser();
	cout << "\nReversed stack: ";
	stackInt.print();

	stackInt.pop();
	cout << "\nStack after pop: "; //should be 3,2,1
	stackInt.print();

	cout << "\nPeeking data: " << (stackInt.peek())->data << endl; //3

	stackInt.pop();
	cout << "\nStack after pop: "; //should be 2,1
	stackInt.print();

	stackInt.pop();
	cout << "\nStack after pop: "; //should be 1
	stackInt.print();

	cout << "\nPeeking data: " << (stackInt.peek())->data << endl; //1

	stackInt.pop();
	cout << "\nStack after pop: "; //should be empty
	stackInt.print(); //should be error

	stackInt.pop(); //should be error

	//cout << "\nPeeking data: " << (stackInt.peek())->data << endl; //error

	//stack of doubles///////////////////////////////////////////////////////////////////
	stackDouble.push(1.11);
	stackDouble.push(2.222);
	stackDouble.push(3.1451);
	stackDouble.push(4.420);

	cout << "\n\nDouble Max stack: ";
	stackDouble.print();

	stackDouble.reverser();
	cout << "\nReversed stack: ";
	stackDouble.print();

	stackDouble.pop();
	cout << "\nStack after pop: "; //should be 3,2,1
	stackDouble.print();

	cout << "\nPeeking data: " << (stackDouble.peek())->data << endl; //3

	stackDouble.pop();
	cout << "\nStack after pop: "; //should be 2,1
	stackDouble.print();

	stackDouble.pop();
	cout << "\nStack after pop: "; //should be 1
	stackDouble.print();

	cout << "\nPeeking data: " << (stackDouble.peek())->data << endl; //1

	stackDouble.pop();
	cout << "\nStack after pop: "; //should be empty
	stackDouble.print(); //should be error

	stackDouble.pop(); //should be error

	//cout << "\nPeeking data: " << (stackDouble.peek())->data << endl; //error

	//stack of chars/////////////////////////////////////////////////////////////////////
	stackChar.push('A');
	stackChar.push('B');
	stackChar.push('C');
	stackChar.push('D');

	cout << "\n\nChar Max stack: ";
	stackChar.print();

	stackChar.reverser();
	cout << "\nReversed stack: ";
	stackChar.print();

	stackChar.pop();
	cout << "\nStack after pop: "; //should be 3,2,1
	stackChar.print();

	cout << "\nPeeking data: " << (stackChar.peek())->data << endl; //3

	stackChar.pop();
	cout << "\nStack after pop: "; //should be 2,1
	stackChar.print();

	stackChar.pop();
	cout << "\nStack after pop: "; //should be 1
	stackChar.print();

	cout << "\nPeeking data: " << (stackChar.peek())->data << endl; //1

	stackChar.pop();
	cout << "\nStack after pop: "; //should be empty
	stackChar.print(); //should be error

	stackChar.pop(); //should be error

	//cout << "\nPeeking data: " << (stackChar.peek())->data << endl; //error

	//stack of strings///////////////////////////////////////////////////////////////////
	stackString.push("Hello, ");
	stackString.push("I ");
	stackString.push("Am ");
	stackString.push("HAL 8999");

	cout << "\n\nString Max stack: ";
	stackString.print();

	stackString.reverser();
	cout << "\nReversed stack: ";
	stackString.print();

	stackString.pop();
	cout << "\nStack after pop: "; //should be 3,2,1
	stackString.print();

	cout << "\nPeeking data: " << (stackString.peek())->data << endl; //3

	stackString.pop();
	cout << "\nStack after pop: "; //should be 2,1
	stackString.print();

	stackString.pop();
	cout << "\nStack after pop: "; //should be 1
	stackString.print();

	cout << "\nPeeking data: " << (stackString.peek())->data << endl; //1

	stackString.pop();
	cout << "\nStack after pop: "; //should be empty
	stackString.print(); //should be error

	stackString.pop(); //should be error

	cout << "\nPeeking data: " << (stackString.peek())->data << endl; //error

	return 0;
}