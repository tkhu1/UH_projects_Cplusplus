#include <iostream>
#include <assert.h> 

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
		queueType(int queueSize = 100);

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

	queueType<int> q1;
	q1.addQueue(1);
	q1.addQueue(7);
	q1.addQueue(3);
	q1.addQueue(9);
	q1.addQueue(8);
	q1.addQueue(2);
	q1.addQueue(10);
	q1.addQueue(4);
	q1.addQueue(6);
	q1.addQueue(5);

	cout << "\nInitial queue is:    ";
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	cout << "\n\nDeleting from queue: ";
	q1.deleteQueue();
	q1.display();

	return 0;
}