#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

//linked list node template
template <typename T>  
class ArrStack { 
	public:
		//max stack size
		int maxSize;
		//holds top of stack position
		int top;
		//pointer to new array
    T *arr; 

		//constructor
		ArrStack(int inputSize)
		{
			//ERROR checking
			if (inputSize <= 0) {
				cout << "Size of the array to hold the stack must be positive." << endl;
				cout << "Creating an array of size 100." << endl;
				maxSize = 100;
			}
			else
				maxSize = inputSize;

		top = 0;
		//creates the array to hold the stack elements
		arr = new T[maxSize]; 
		}

		//reinit stack to empty
		void reinitStack ()
		{
			top = 0;
		}

		//checks if stack is empty
		bool isEmpty () const
		{
			if (top == 0)
				return true; 
			else
				return false;
		}

		//checks if stack is full
		bool isFull () const
		{
			return (top == maxSize);
		}

		//adds data to top of stack
		void push(T newData) 
		{
			if (!isFull()) {
				arr[top] = newData;
				top++;
			}
			else
				cout << "ERROR detected: Cannot push data to a full stack" << endl;
		}

		//removes data from top of stack
		void pop() 
		{
			if (!isEmpty()) {
				top--;
			}
			else
				cout << "ERROR detected: Cannot remove data from empty stack" << endl;
		}

		//returns data at top of stack
		T peek()
		{
			assert(top != 0); //if stack is empty, terminate the program
			return arr[top-1]; //return the element of the stack
		}

		//reverses stack
		void reverser()
		{
			//error checking
			if (isEmpty()) 
				return;

			//init reverse stack to store elements of original stack
			ArrStack<T> revArrStack(maxSize); 

			//stores original stack top
			int origTop = top;
  
			//pushes elements of array to reverse stack 
			while (!isEmpty()) { 
				revArrStack.push(peek()); 
				pop(); 
			} 

			//revArrStack.print(); //DEBUG

			//resets original stack top position
			top = origTop;

			//pops from stack and replace current array stack value 
			while (!revArrStack.isEmpty()) { 
				arr[top-1] = revArrStack.peek(); 
				revArrStack.pop(); 
				top--;
			}  

			//resets original stack top position
			top = origTop;
		}

		//prints stack data
		void print()
		{
			//saves top value
			int origTop = top;
			// checks for empty stack 
			if (isEmpty()) { 
				cout << "\nCannot print empty stack." << endl;  
			} 
   		else { 
        while (!isEmpty()) {
					// print data 
					cout << peek() << " "; 
					pop();
        } 
				cout << endl;
				top = origTop; //reassigns top value
    	} 
		}

}; 

int main () 
{
	//init max stack size
	const int MAX = 10;

	//init stack
	ArrStack<int> stackInt(MAX); 
	ArrStack<double> stackDouble(MAX); 
	ArrStack<char> stackChar(MAX); 
	ArrStack<string> stackString(MAX); 

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

	cout << "\nPeeking data: " << stackInt.peek() << endl; //3

	stackInt.pop();
	cout << "\nStack after pop: "; //should be 2,1
	stackInt.print();

	stackInt.pop();
	cout << "\nStack after pop: "; //should be 1
	stackInt.print();

	cout << "\nPeeking data: " << stackInt.peek() << endl; //1

	stackInt.pop();
	cout << "\nStack after pop: "; //should be empty
	stackInt.print(); //should be error

	stackInt.pop(); //should be error

	//cout << "\nPeeking data: " << stackInt.peek() << endl; //error

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
	cout << "\nStack after pop: "; 
	stackDouble.print();

	cout << "\nPeeking data: " << stackDouble.peek() << endl; 

	stackDouble.pop();
	cout << "\nStack after pop: "; 
	stackDouble.print();

	stackDouble.pop();
	cout << "\nStack after pop: "; 
	stackDouble.print();

	cout << "\nPeeking data: " << stackDouble.peek() << endl; 

	stackDouble.pop();
	cout << "\nStack after pop: "; 
	stackDouble.print(); 
	stackDouble.pop(); 

	//cout << "\nPeeking data: " << stackDouble.peek() << endl; //error

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
	cout << "\nStack after pop: "; 
	stackChar.print();

	cout << "\nPeeking data: " << stackChar.peek() << endl; 

	stackChar.pop();
	cout << "\nStack after pop: "; 
	stackChar.print();

	stackChar.pop();
	cout << "\nStack after pop: "; 

	cout << "\nPeeking data: " << stackChar.peek() << endl; 

	stackChar.pop();
	cout << "\nStack after pop: "; 
	stackChar.print(); 

	stackChar.pop(); 

	//cout << "\nPeeking data: " << stackChar.peek() << endl; //error

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
	cout << "\nStack after pop: "; 
	stackString.print();

	cout << "\nPeeking data: " << stackString.peek()<< endl; 

	stackString.pop();
	cout << "\nStack after pop: "; 
	stackString.print();

	stackString.pop();
	cout << "\nStack after pop: "; 
	stackString.print();

	cout << "\nPeeking data: " << stackString.peek() << endl; 

	stackString.pop();
	cout << "\nStack after pop: "; 
	stackString.print(); 

	stackString.pop(); 

	cout << "\nPeeking data: " << stackString.peek() << endl; 

	return 0;
}