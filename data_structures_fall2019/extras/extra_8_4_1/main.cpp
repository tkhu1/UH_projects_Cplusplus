#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Rizk                                                       //
///////////////////////////////////////////////////////////////////////////////////////

class st
{
	private:
    int id;
	  double gpa;
	public: 
		//st(); { id=0;gpa=1;}
		//st(int,double);
		st(int=0,double=1);
		void setall(int a ,double b);
		void setgpa(double a);
		int getid();
		void getgpa(double &g);
		void print();
};

// CLASS FUNCTIONS ////////////////////////////////////////////////////////////////////
st::st(int a, double b)
{     
	setall(a,b);
}

void st::setall(int x, double y)
{
	//testing 
	if (x<=0)
	  id=999;
	else
	  id=x;
	if (y<1)
	  gpa=1;
	else 
	  gpa=y;
}

int st::getid()
{
	return id;
}

void st::getgpa(double &g)
{ 
	g=gpa;
}

void st::print()
{
  cout << "the id is ..... "<< id <<endl;
  cout << "the gpa is .... "<<gpa <<endl;
  cout <<"----------------\n";
}

void st::setgpa(double x)
{  
	if (x<1)
    gpa=1;
  else if (x>4)
	  gpa=4;
  else
    gpa=x;
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	st elio;
	st roger(-15, 4.0);
	st emile(453);
	st emilia(366,0);

	elio.print();
	roger.print();
	emile.print();
	emilia.print();
	//============================
	st *p = new st();
	 p->print();
	 delete p;
	 p=0;
	 p=new st(7,3.0);
	 p->print();

	return 0;
}

