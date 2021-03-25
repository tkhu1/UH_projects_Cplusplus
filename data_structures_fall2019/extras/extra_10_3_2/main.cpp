#include <iostream>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Rizk, Dr. Malik (textbook), and internet websites          //
///////////////////////////////////////////////////////////////////////////////////////

// NODE CLASS /////////////////////////////////////////////////////////////////////////
class Node 
{
	public:
		int priority;
		int info;
		Node *next;
};

// PRIORITY QUEUE CLASS ///////////////////////////////////////////////////////////////
class PriorityQueue
{
private:
  Node *front;

public:
  PriorityQueue()
  {
    front = NULL;
  }

  void insert(int data, int p)
  {
    Node *temp, *q;

    temp = new Node;
    temp->info = data;
    temp->priority = p;

    if (front == NULL || p < front->priority) {
      temp->next = front;
      front = temp;
    }
    else {
      q = front;
      while (q->next != NULL && q->next->priority <= p)
        q = q->next;
      temp->next = q->next;
      q->next = temp;
    }
  }

  void del() 
	{
    Node *temp;

    if (front == NULL)
      cout << "Queue Underflow\n";
    else {
      temp = front;
      cout << "\nDeleting from queue (" << temp->info << ")." << endl;
      front = front->next;
      delete temp;
    }
  }

  void display()
  {
    Node *temp = front;

    if (front == NULL)
      cout << "\nQueue is empty\n";
    else {
      cout << "\nQueue is:\n";
			cout << "Priority   Data\n";
      while (temp != NULL) {
        cout << setfill(' ') << left << setw(11) << temp->priority << setw(5) << 
								temp->info << endl;
        temp = temp->next;
      }
    }
  }
};

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
  PriorityQueue pq;

  pq.insert(15, 3);
	pq.insert(5, 2);
	pq.insert(10, 1);
	pq.insert(6, 4);
	pq.insert(8, 5);
	pq.insert(2, 3);

	pq.display();

  pq.del();
  pq.display();
  
  pq.del();
  pq.display();

  pq.del();
  pq.display();

  pq.del();
  pq.display();

  pq.del();
  pq.display();

  pq.del();
  pq.display();

  return 0;
}