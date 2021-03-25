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
struct point
{
	int x;
	int y;
	point *next;
};

// LINKED LIST CLASS //////////////////////////////////////////////////////////////////
class list  
{  
	private: 
    point *head;
   public:
	  list()
		{ 
			head=0;
		}
	  
		bool isempty()
		{ 
			if (head == 0)
		    return true; 
	    else 
				return false;
		}

	  void add_beg(int,int); // add one point 
	  void add_end(int,int);
	  void print_allpoints();
};

// LIST CLASS FUNCTIONS ///////////////////////////////////////////////////////////////

void list::add_beg(int a, int b)
{
	//1- create a node 
	//2- fill it 
	//3- link it 
	point *temp;
	temp= new point;
	temp->x=a;
	temp->y=b;
	temp->next=head;

	head=temp;
}
			  
void list::add_end(int a, int b)
{
	//1- traverse the list, create a node 
	//2- fill it 
	//3- link it 
	point *temp;
	point *cu=head;
	if (cu==0)
		add_beg(a, b);
	else {
		while (cu->next !=nullptr)
			cu=cu->next;

		temp=new point;
		temp->x=a;
		temp->y=b;
		cu->next=temp;
	}
}

void list::print_allpoints()
{
	point *cu=head;
	while(cu !=0)	{    
		cout <<"("<< cu->x <<","<< cu->y <<")\n";
		cu=cu->next;		  
	}
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	list n;
  n.add_beg(5,7);
	n.add_end(55,77);
	n.add_beg(1,2);
	n.add_beg(3,4);
	n.print_allpoints();

	return 0;
}

