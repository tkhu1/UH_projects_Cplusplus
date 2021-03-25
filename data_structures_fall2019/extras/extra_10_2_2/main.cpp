#include <iostream>
#include <string>
#include <assert.h> 
#include <stack>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Rizk, Dr. Malik (textbook), and internet websites          //
///////////////////////////////////////////////////////////////////////////////////////

// TEMPLATE QUEUE ADT /////////////////////////////////////////////////////////////////
template <class Type>
class queueADT
{
	public:
		virtual bool isEmptyQueue() const = 0;
		virtual bool isFullQueue() const = 0;
		virtual void initializeQueue() = 0;
		virtual Type front() const = 0;
		virtual Type back() const = 0;
		virtual void addQueue(const Type& queueElement) = 0;
		virtual void deleteQueue() = 0;
		virtual void display() = 0; 
};

// TEMPLATE QUEUE ARRAY ///////////////////////////////////////////////////////////////
template <class Type>
class queueType: public queueADT<Type>
{
	public:
		queueType(int queueSize = 200);

		bool isEmptyQueue() const;
		bool isFullQueue() const;
		void initializeQueue();

		Type front() const;
		Type back() const;

		void addQueue(const Type& queueElement);
		void deleteQueue();

		void display(); 

		queueType(const queueType<Type>& otherQueue);
		const queueType<Type>& operator=(const queueType<Type>&);
		~queueType();

	private:
		int maxQueueSize;
		int count;
		int queueFront;
		int queueRear;
		Type *list;
};

// TEMPLATE QUEUE ARRAY FUNCTIONS /////////////////////////////////////////////////////
//constructor
template <class Type>
queueType<Type>::queueType(int queueSize)
{
	if (queueSize <= 0)
	{
		cout << "Size of the array to hold the queue must "
		<< "be positive." << endl;
		cout << "Creating an array of size 100." << endl;
		maxQueueSize = 100;
	}
	else
		maxQueueSize = queueSize; //set maxQueueSize to queueSize

	queueFront = 0; //initialize queueFront
	queueRear = maxQueueSize - 1; //initialize queueRear
	count = 0;
	list = new Type[maxQueueSize]; //create the array to hold the queue elements
} //end constructor

template <class Type>
bool queueType<Type>::isEmptyQueue() const
{
	return (count == 0);
} //end isEmptyQueue

template <class Type>
bool queueType<Type>::isFullQueue() const
{
	return (count == maxQueueSize);
} //end isFullQueue

template <class Type>
void queueType<Type>::initializeQueue()
{
	queueFront = 0;
	queueRear = maxQueueSize - 1;
	count = 0;
} //end initializeQueue

template <class Type>
Type queueType<Type>::front() const
{
	assert(!isEmptyQueue());
	return list[queueFront];
} //end front

template <class Type>
Type queueType<Type>::back() const
{
	assert(!isEmptyQueue());
	return list[queueRear];
} //end back

template <class Type>
void queueType<Type>::addQueue(const Type& newElement)
{
	if (!isFullQueue())
	{
		queueRear = (queueRear + 1) % maxQueueSize; 
		//use the mod operator to advance queueRear because the array is circular
		count++;
		list[queueRear] = newElement;
	}
	else
		cout << "Cannot add to a full queue." << endl;
} //end addQueue

template <class Type>
void queueType<Type>::deleteQueue()
{
	if (!isEmptyQueue())
	{
		count--;
		queueFront = (queueFront + 1) % maxQueueSize; 
		//use the mod operator to advance queueFront because the array is circular
	}
	else
	cout << "Cannot remove from an empty queue" << endl;
} //end deleteQueue

template <class Type>
void queueType<Type>::display() 
{ 
	if (queueFront > queueRear) { 
		cout << "\nQueue is Empty."; 
		return; 
	} 

	for (int i = queueFront; i <= queueRear; i++) { 
		if (i == queueRear)
			cout << list[i]; 
		else
			cout << list[i] << " <-- "; 
	} 
	return; 
} //end display

template <class Type>
queueType<Type>::~queueType()
{
	delete [] list;
} //end destructor

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main() {

	queueType<char> q1;
	stack<char> s1;

	string text;
	char c;
	bool isPalindrome = true;

	cout << "\nPlease enter a line of text: ";
	getline(cin, text);
	
	for (int i=0; i<text.size(); i++) {
		c = text[i];

    if (isupper(c)) 
			c = tolower(c);
		
		q1.addQueue(c);
		s1.push(c);		
	}

	for (int i=0; i<text.size(); i++) {
		if (isPalindrome) {
			if (q1.front() == s1.top()) {
				isPalindrome = true;
				q1.deleteQueue();
				s1.pop();
			}
			else {
				isPalindrome = false;
			}		
		}
	}

	if (isPalindrome)
		cout << "\nYour line of text is a palindrome.\n";
	else
		cout << "\nYour line of text is not a palindrome.\n";

	return 0;
}