#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Rizk, Dr. Malik (textbook), and internet websites          //
///////////////////////////////////////////////////////////////////////////////////////

// NODE TEMPLATE //////////////////////////////////////////////////////////////////////
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

// LINKED LIST STACK TEMPLATE /////////////////////////////////////////////////////////
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
		void reinitStack()
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
		bool isEmpty() const
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

		//returns data in top node of stack
		T peek()
		{
			//checks for empty stack 
    	if (!isEmpty()) 
        return top->data; 
    	else
				//cout << "\nCannot peek at empty stack." << endl; 
				return 0;
		}

		//prints stack data
		void print()
		{
			//pointer to traverse stack
			Node<T> *temp; 

			// checks for empty stack 
			if (top == NULL) { 
				//cout << "\nCannot print empty stack." << endl;  
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
		
// EXPRESSION EVALUATION FUNCTIONS ////////////////////////////////////////////////////
		
//returns priority of operator
int priority(char op)
{
	if (op == '+' || op == '-') {
		return 1;
	}
	if (op == '*' || op == '/') {
		return 2;
	}
	return 0;
}

//returns evaluated arithmetic block value
long long int calculator(char op, long long int lhs, long long int rhs)
{
	if (op == '+') {
		return (lhs + rhs);
	}
	else if (op == '-') {
		return (lhs - rhs);
	}
	else if (op == '*') {
		return (lhs * rhs);
	}
	else {
		if (rhs == 0) {
			return -12345789;
		}
		else {
			return (lhs / rhs);
		}
	}
}

//evaluates input expression and returns result
long long int evaluator(string exp)
{
	//cout << exp << endl; //DEBUG

	//init two stacks for evaluation
	LLstack<char> opSt;
	LLstack<long long int> intSt;

	//cout <<"Infix: " << exp << endl; //DEBUG

	//main loop
	for (int i=0; i < exp.length(); i++) {
		if (exp[i] == '(') {
			opSt.push('(');

			//cout << "Opstack( push: "; //DEBUG
			//opSt.print(); //DEBUG
		}
		else if (isdigit(exp[i])) {
			long long int num = 0;
			//gets whole number 
			while (i < exp.length() && isdigit(exp[i])) { 
				num = (num*10) + (exp[i]-'0'); 
				i++; 
			} 
			i--;
			intSt.push(num); 

			//cout << "Intstack push: "; //DEBUG
			//intSt.print(); //DEBUG
		}
		else if (exp[i] == ')') {
			//loops until next evaluation block is found
			while (!opSt.isEmpty() && opSt.peek() != '(') {

				long long int rhs = intSt.peek();
				intSt.pop();

				long long int lhs = intSt.peek();
				intSt.pop();

				char op = opSt.peek(); 
        opSt.pop();

				//pushes result from arithmetic block
				long long int result = calculator(op, lhs, rhs);

				//ERROR checking for valid division operation
				if (result == -123456789) {
					return -123456789;
				}
				else {
					intSt.push(result);
			
					//cout << "Result): " << result << endl; //DEBUG
				}
			}
			//checks if opening brace needs to be popped
      if (!opSt.isEmpty()) {
      	opSt.pop();
			}
		}
		//checks if char is operator and evaluates expression arithmetic block
		else {
			//handles priority arithmetic
			while (!opSt.isEmpty() && opSt.peek() != '(' && priority(opSt.peek()) >= 
																											priority(exp[i])) {
				//opSt.print(); //DEBUG
				long long int rhs = intSt.peek();
				intSt.pop();

				long long int lhs = intSt.peek();
				intSt.pop();

				char op = opSt.peek(); 
        opSt.pop();

				//pushes result from arithmetic block
				long long int result = calculator(op, lhs, rhs);

				//ERROR checking for valid division operation
				if (result == -123456789) {
					return -123456789;
				}
				else {
					intSt.push(result);

					//cout << "ResultOp: " << result << endl; //DEBUG
				}
			}
			//pushes to operator stack
			opSt.push(exp[i]);

			//cout << "OpstackOp push: "; //DEBUG
			//opSt.print(); //DEBUG
		}
	}

	//final calculation
	while (!opSt.isEmpty()){
		long long int rhs = intSt.peek();
		intSt.pop();

		long long int lhs = intSt.peek();
		intSt.pop();

		char op = opSt.peek(); 
    opSt.pop();

		long long int result = calculator(op, lhs, rhs);

		//checks for valid division operation
		if (result == -123456789) {
			return -123456789;
		}
		else {
		intSt.push(result);
		}
	}

	//checks for valid division operation value
	if (intSt.peek() == -123456789) {
		return -123456789;
	}
	else {
		return (intSt.peek());
	}
}

// MAIN FUNCTIONS /////////////////////////////////////////////////////////////////////

//removes return breaks from expression
string returnRemover(string exp) {
	string result = "";

	int size = exp.length();

	for (int i=0; i < size; i++) { 
		if (exp[i] != '\n' && exp[i] != '\r') {
			result = result + exp[i];
		}
	}

	return result;
}

//removes spaces from expression
string spaceRemover(string exp) {
	string result = "";

	int size = exp.length();

	for (int i=0; i < size; i++) { 
		if (exp[i] != ' ') {
			result = result + exp[i];
		}
	}

	return result;
}

//checks if char is +, -, * or / operator 
bool isOp(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/') {
		return true;
	}
	return false;
}

/*prepares string for calculation by concatenating 0 in front of negation sign
  and converting numbers with positive sign in front to said number*/
string preparer (string exp) {
	string result = "";

	int size = exp.length();
	//holds number of operators in string
	int counter = 0;
	//string iterators
	int j = 0;
	int i = 0;

	for (int i = 0; i < size; i++) {
		if (isOp(exp[i])) {
			counter++;
		}
	}

	if (exp[0] == '+' and counter < 2) {
		return exp;
	}

	//handles the case if first char is -
	if (exp[0] == '-') {
		result = '0';
		result = result + '-';
		j = 1;
	}
	//handles the case if first char is +
	else if (exp[0] == '+') {
		result = exp[1];
		j = 2;
	}
	else {
		result = exp[0];
		j = 1;
	}

	//handles negation cases
	for (i=j; i < size-1; i++) {
		if (exp[i] == '-' && !isdigit(exp[i-1]) && 
			  (exp[i-1] != ')' /*&& exp[i+1] != '('*/)) {
			result = result + '0';
			result = result + exp[i];
		}
		else if (exp[i] == '+' && exp[i-1] != ')' && !isdigit(exp[i-1])) {
			result = result + exp[i+1];
			i++;
		}
		else {
			result = result + exp[i];
		}
	}

	//adds final character
	result = result + exp[size-1];

	return result;
}

//checks if expression is valid 
bool isValid(string exp) 
{
	int last = exp.length()-1;

	//checks if first or last character in expression is a * or / operator
	if (exp[0] == '*' || exp[0] == '/' || isOp(exp[last])) {
		return false;
	}
  //checks if last character is invalid character
	else if (!isOp(exp[last]) && !isdigit(exp[last]) && exp[last] != '(' && 
	         exp[last] != ')') {
		return false;
	}
	//various error checks
	else {
		for (int i=0; i < last; i++) { 
			if (!isOp(exp[i]) && !isdigit(exp[i]) && exp[i] != '(' && exp[i] != ')') {
				return false;
			}
			if (isOp(exp[i]) && isOp(exp[i+1])) {
				return false;
			}
			if (isOp(exp[i]) && exp[i+1] == ')') {
				return false;
			}
			if (exp[i] == ')' && exp[i+1] == '(') {
				return false;
			}
			if (exp[i] == ')' && isdigit(exp[i+1])) {
				return false;
			}
			if (isdigit(exp[i]) && exp[i+1] == '(') {
				return false;
			}
			if (exp[i] == '(' && exp[i+1] == '/') {
				return false;
			}
			if (exp[i] == '(' && exp[i+1] == '*') {
				return false;
			}
			if (exp[i] == '(' && exp[i+1] == ')') {
				return false;
			}
		}
		//if expression is valid
		return true;
	}
	//default return value
	return false;
}

//checks if parantheses are balanced 
bool isBalanced(string exp) 
{ 
	LLstack<char> balSt; 
	char c; 

	//pushes open parentheses to stack
	for (int i=0; i < exp.length(); i++) { 
		if (exp[i] == '(') {
			balSt.push(exp[i]);
		}
		else if (exp[i] == ')') {   
			//if first char is closing parentheses, expression is unbalanced
			if (balSt.isEmpty()) {
				return false;
			}

			c = balSt.peek();
			balSt.pop();
			
			//checks for matching pair
			if (exp[i] == ')' && c != '(')
				return false;
		}
	}
	//returns true if stack is empty
	if (balSt.isEmpty()) {
		return true;
	}
	else {
		return false;
	}
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main() {

	string eq1 = "(10+20*(2-1))/(2+(4-1))";
	string eq2 = "7+3-4+5-6+2-8";

	//holds input line
	string temp = "";
	//holds input line with return break removed
	string tempNoReturn = "";
	//holds input line with spaces removed
	string tempNoSpaces = "";
	//holds input line with prepared expression fit for evalution
	string tempPrepared = "";
	//holds calculated result
	long long int result = 0;

	tempNoReturn = returnRemover(eq1);
	tempNoSpaces = spaceRemover(tempNoReturn);
	//checks for balanced and valid expressions
	if (isBalanced(tempNoSpaces) && isValid(tempNoSpaces)) {
		//cout << "\nNospace: " << tempNoSpaces << endl << endl; //DEBUG
		tempPrepared = preparer(tempNoSpaces);
		//cout << "\nPrepared: " << tempPrepared << endl << endl; //DEBUG
		result = evaluator(tempPrepared);
		//cout << "\n\nOutfs: " << result << endl << endl; //DEBUG
		//checks for valid results
		if (result == -12345789) {
			cout << "error" << endl;
		}
		else {
			cout << tempNoReturn << " = " << result << endl <<endl;
			//cout << tempNoSpaces << endl; //DEBUG
			//outfs << "valid" << endl; //DEBUG
		}
	}
	else {
		//tempPrepared = preparer(tempNoSpaces); //DEBUG
		//cout << tempNoSpaces << endl; //DEBUG
		cout << "error" << endl;
	}

	tempNoReturn = returnRemover(eq2);
	tempNoSpaces = spaceRemover(tempNoReturn);
	//checks for balanced and valid expressions
	if (isBalanced(tempNoSpaces) && isValid(tempNoSpaces)) {
		//cout << "\nNospace: " << tempNoSpaces << endl << endl; //DEBUG
		tempPrepared = preparer(tempNoSpaces);
		//cout << "\nPrepared: " << tempPrepared << endl << endl; //DEBUG
		result = evaluator(tempPrepared);
		//cout << "\n\nOutfs: " << result << endl << endl; //DEBUG
		//checks for valid results
		if (result == -12345789) {
			cout << "error" << endl;
		}
		else {
			cout << tempNoReturn << " = " << result << endl;
			//cout << tempNoSpaces << endl; //DEBUG
			//outfs << "valid" << endl; //DEBUG
		}
	}
	else {
		//tempPrepared = preparer(tempNoSpaces); //DEBUG
		//cout << tempNoSpaces << endl; //DEBUG
		cout << "error" << endl;
	}

	return 0;
}