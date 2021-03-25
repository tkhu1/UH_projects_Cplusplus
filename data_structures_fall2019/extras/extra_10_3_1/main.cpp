#include <iostream>
#include <iomanip>
#include <assert.h> 

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
};

// PRIORITY QUEUE CLASS ///////////////////////////////////////////////////////////////
class PriorityQueue
{
private:
	Node *list; 
	int maxQueueSize;
	int count;
	int queueFront;
	int queueRear;

public:
  PriorityQueue(int queueSize)
  {
		list = new Node[queueSize];

		for (int i = 0; i<queueSize; i++) {
			list[i].priority = 0;
			list[i].info = 0;
		}

    maxQueueSize = queueSize; 

		queueFront = 0; 
		queueRear = 0; 
		count = 0;
  }

	bool isEmptyQueue() const
	{
		return (count == 0);
	} 

	bool isFullQueue() const
	{
		return (count == maxQueueSize);
	} 

	int Search(int data, int p)
	{
		int i, j;
		int idx = 0;
    if (isEmptyQueue()) {
      return idx;
    }

    for (i = queueFront; i < queueRear; i++) {   
			if (p < list[i].priority) {
				idx = i;
				break;
			}
			else if (p == list[i].priority) {
				if (data < list[i].info) {
					idx = i;
					break;
				}
				else {
					for (j = i; j < queueRear; j++) {
						if (data < list[j].info) {
							idx = j;
							break;
						}
					}
				}
			}
			idx = i;
		}

    return idx;
	}

  void insert(int data, int p)
  {
		if (isEmptyQueue()) {
			list[queueFront].info = data;
			list[queueFront].priority = p;
			count++;
			queueRear++;
			return;
		}
	  else if (isFullQueue()) {
			cout << "Cannot add to a full queue." << endl;
			return;
		}
    else {
			queueRear++;
			count++;
			int index = Search(data, p);
			//cout << "idx: " << index << endl;
			Node temp[maxQueueSize];

			for (int i = queueFront; i < queueRear; i++) {
				temp[i] = list[i];
			}

			if (index != queueRear) {
				for (int i = index; i < queueRear; i++) {
					list[i+1] = temp[i];
				}
			}

			list[index].info = data;
			list[index].priority = p;
    }
  }

  void del() 
	{
		if (!isEmptyQueue()) {
			cout << "\nDeleting from queue (" << list[queueFront].info << ")." << endl;
			count--;
			queueFront++; 
		}
		else
			cout << "Cannot remove from an empty queue" << endl;
  }

  void display()
  {
    if (isEmptyQueue())
      cout << "\nQueue is empty\n";
    else {
      cout << "\nQueue is:\n";
			cout << "Priority   Data\n";
      for (int i = queueFront; i < queueRear; i++) {
        cout << setfill(' ') << left << setw(11) << list[i].priority << setw(5) << 
								list[i].info << endl;
      }
    }
  }
};

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
  PriorityQueue pq(10);

  pq.insert(15, 3);
	pq.insert(5, 2);
	pq.insert(10, 1);
	pq.insert(6, 4);
	pq.insert(8, 2);
	pq.insert(2, 3);
	pq.insert(11, 3);
	pq.insert(9, 4);
	pq.insert(19, 2);
	pq.insert(1, 1);

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