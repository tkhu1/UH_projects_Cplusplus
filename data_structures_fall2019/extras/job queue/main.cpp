#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <math.h>
#include <assert.h>

using namespace std;

//inspired by code posted by Dr. Rizk and Dr. Malik (textbook)
///////////////////////////////////////////////////////////////////////////////////////
class job 
{
	public:
		string name;     //holds job name
		int priority;    //holds priority (1-5, with 1 being highest priority)
		int initLength;  //holds time needed for execution
		int jobTime;     //holds jobTime
		int beg_time;    //holds beginning time
		int w_time;      //holds waiting time
		int end_time;    //holds ending time
		bool isExecuted; //holds bool value if node has been executed yet
		job *link;

		//default constructor
		job () {
			this->name = "DEFAULT";
			this->priority = -1;
			this->initLength = -1; 
			this->jobTime = -1;
			this->beg_time = 0; 
		 	this->w_time = 0; 
			this->end_time = 0; 
			this->isExecuted = false;
			this->link = NULL;
		}
};

///////////////////////////////////////////////////////////////////////////////////////
class priorityQueue
{
	public:
		job *front; //pointer to the front of the queue
		job *rear; //pointer to the rear of the queue

		//default constructor
		priorityQueue()
		{
			this->front = NULL;
			this->rear = NULL;
		}

		//reinit queue to empty
		void reinitQueue ()
		{
			//pointer to delete node
			job *temp;

			//while there are elements in the queue
			while (front != NULL) {
				temp = front;
				front = front->link; 

				delete temp;
			}
			rear = NULL;
		}

		//checks if queue is empty
		bool isEmpty () const
		{
			if (front == NULL)
				return true; 
			else
				return false;
		}

		//always false as queue is never full
		bool isFull () const
		{
			return false;
		}

		//adds new node to queue and sorts
		void push(string addName, int addPriority, int addTimeNeeded)
		{	
			job *newNode = new job; //creates the node
			newNode->name = addName; //stores the name
			newNode->priority = addPriority; //stores the priority
			newNode->initLength = addTimeNeeded; //stores the job execution time
			newNode->jobTime = addTimeNeeded; //stores the job execution time
			newNode->link = NULL;
			//creates queue if initially the queue is empty
			if (front == NULL) { 
				newNode->link = NULL;
				front = newNode;
				rear = newNode;
				return;
			}
			//if the new node has higher priority
			if (addPriority < front->priority) {
				newNode->link = front;
				front = newNode;
				return;
			}
			//adds newNode at the end
			else {
				job *temp = front;
				job *prev = NULL;

				while (temp != NULL)	{			
					if (addPriority >= temp->priority) {
						//traverses to the location we want to insert the node + 1 node
						prev = temp;	
						temp = temp->link;
						continue;
					}	
					else {
						//inserts the node
						prev->link = newNode;
						newNode->link = temp;											
						return;
					}				
				}
				//inserts node at the end
				prev->link = newNode;
				rear = newNode;
    	}		
		}

		//deletes first node from queue
		void pop()
		{
			job *temp;
			if (!isEmpty())	{
				temp = front;
				front = front->link;
				delete temp;

				//if after deletion the queue is empty
				if (front == NULL) 
					rear = NULL;
			}
			else
				cout << "\nCannot remove from an empty queue.\n";
		}

		//outputs job name at front of queue
		string accessFront() const
		{
			assert(front != NULL);
			return front->name;
		}

		//outputs job name at back of queue
		string accessRear() const
		{
			assert(rear != NULL);
			return rear->name;
		}

		//completes jobs in queue by allocating taskTime amount to each job sequentially
		int executer(int taskTime)
		{
			job *temp = front;
			string firstRear = rear->name;
			int time = 0;
			int rounds = 0;

			while (temp != NULL) {
				if (temp->initLength > taskTime) {
					//calculates number of full rounds executed
					if (temp->name == firstRear) {
						rounds++;
					}
					//assigns beginning time of task
					if (temp->isExecuted == false) {
						temp->beg_time = time;
						temp->isExecuted = true;
					}
					//calculates waiting time
					if (temp->initLength != temp->jobTime) {
						int waiting = time - temp->end_time; 
						temp->w_time += waiting;
					}
					//decrements job time left
					temp->initLength = temp->initLength - taskTime;
					//increments run time
					time += taskTime;
					//assigns end time of task
					temp->end_time = time;

					cout << "Time > Alloc: " << time << endl; //DEBUG
					
					pushExecute(temp);
					pop();
				}
				else {
					if (temp->initLength > 0) {
						//calculates number of full rounds executed
						if (temp->name == firstRear) {
							rounds++;
						}
						//assigns beginning time of task
						if (temp->isExecuted == false) {
							temp->beg_time = time;
							temp->isExecuted = true;
						}
						//calculates waiting time
						if (temp->initLength != temp->jobTime) {
							int waiting = time - temp->end_time; 
							temp->w_time += waiting;
						}
						//decrements job time left
						temp->initLength = 0;
						//increments run time
						time += temp->jobTime;
						//assigns end time of task
						temp->end_time = time;

						cout << "Time<Alloc: " << time << endl; //DEBUG

						pushExecute(temp);
						pop();
					}
				}
				temp = temp->link;
				/*if (rounds >= 1)
					break;*/
			}
		
			return rounds;
		}

		//adds new node to queue 
		void pushExecute(job *inputNode)
		{	
			//creates the node and copies data
			job *newNode = new job; 
			newNode->name = inputNode->name; 
			newNode->priority = inputNode->priority; 
			newNode->initLength = inputNode->initLength; 
			newNode->jobTime = inputNode->jobTime; 
			newNode->beg_time = inputNode->beg_time; 
		  newNode->w_time = inputNode->w_time; 
		  newNode->end_time = inputNode->end_time;
		  newNode->isExecuted = inputNode->isExecuted; 
			newNode->link = NULL;
			
			//inserts node at the end
			rear->link = newNode;
			rear = newNode;
		}

		//FOR DEBUGGING
		void print() {
			job *temp = front; //CCes head pointer

			cout << "RUNTIME LOG\n\n";
			cout << "JOB NAME    JOB PRIORITY    JOB LENGTH    START TIME    END TIME";
			cout << "    WAIT TIME" << endl;
        
			while (temp != NULL) {				
				cout << setfill(' ') << left << setw(12) << temp->name << setw(16) <<
								temp->priority << setw(14) << temp->jobTime << setw(14) << 
								temp->beg_time << setw(12) << temp->end_time << 
								temp->w_time << endl;
					if (temp->link != front) {
					}
					else {
						break;
					}
				temp = temp->link;
			}

			cout << endl;
		}
};

///////////////////////////////////////////////////////////////////////////////////////
int main () 
{
	int inputPriority, inputTimeNeeded, numRounds;
	string inputName;

	string jobPool[10] = {"Job 1", "Job 2", "Job 3", "Job 4", "Job 5", "Job 6", 
												"Job 7", "Job 8", "Job 9", "Job 10"};

	//init execution allocation
	int allocationTime = 3;

	//init random seed
  srand (time(NULL));

	//init job queue
	priorityQueue tasks;

	//adds ten jobs to queue
	for (int i = 0; i<10; i++) {
		//pulls job name from name array
		inputName = jobPool[i];
		//randomly picks priority (1-5, with 1 being highest priority)
		inputPriority = rand() % 5 + 1; 
		//randomly picks time of job (1-20 minutes)
		inputTimeNeeded = rand() % 20 + 1;
		//pushes data into node creation
		tasks.push(inputName, inputPriority, inputTimeNeeded);
	}

	tasks.print(); //DEBUG

	//simulates execution of jobs
	numRounds = tasks.executer(allocationTime);

	//init output stream
	ofstream outfs("job_runtime_log.txt");

	outfs << "RUNTIME LOG\n\n";
	outfs << "JOB NAME    JOB PRIORITY    JOB LENGTH    START TIME    END TIME";
	outfs << "    WAIT TIME" << endl;
	
	//outputs to log file
	while (!tasks.isEmpty()) { 
		outfs << setfill(' ') << left << setw(12) << tasks.front->name << setw(16) <<
						 tasks.front->priority << setw(14) << tasks.front->jobTime << setw(14) << 
						 tasks.front->beg_time << setw(12) << tasks.front->end_time << 
						 tasks.front->w_time << endl;
		tasks.pop(); 
	}     
	
	outfs << "\nNumber of execution rounds completed: " << numRounds;

	outfs.close();

	return 0;
}