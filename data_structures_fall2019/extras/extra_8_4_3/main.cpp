#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Rizk & Dr. Malik (textbook)                                //
///////////////////////////////////////////////////////////////////////////////////////

class dayType
{
private:
  string weekDay;
public:
	static string weekDays[7];

	dayType();
  dayType(string d);
	void setDay(string d);
	string getDay() const;
	void print() const;
	string nextDay() const;
	string prevDay() const;
	void addDay(int nDays);
};


// CLASS FUNCTIONS ////////////////////////////////////////////////////////////////////

string dayType::weekDays[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", 
															 "Saturday", "Sunday"};

//default constructor
dayType::dayType() 
{
	weekDay = "";
}

//constructor
dayType::dayType(string d)
{
	setDay(d);
}

void dayType::setDay(string d)
{
	if (d == "Monday")
		weekDay = "Monday";
	else if (d == "Tuesday")
		weekDay = "Tuesday";
	else if (d == "Wednesday")
		weekDay = "Wednesday";
	else if (d == "Thursday")
		weekDay = "Thursday";
	else if (d == "Friday")
		weekDay = "Friday";
	else if (d == "Saturday")
		weekDay = "Saturday";
	else if (d == "Sunday")
		weekDay = "Sunday";
	else
		weekDay = "default";
}

string dayType::getDay() const
{
	string result = weekDay;
	return result;
}

void dayType::print() const
{
	string result = getDay();
	cout << "\nThe day is: " << result << endl;
}

string dayType::nextDay() const
{
	string result;

	for (int i=0;i<7;i++) {
		if (getDay() == weekDays[i]) {
			if (i == 6) {
				result = "Monday";
			}
			else {
				result = weekDays[i+1];
			}
		}
	}
	return result;
}

string dayType::prevDay() const
{
	string result;
	//cout << "prev day: " << getDay() << endl;

	for (int i=0;i<7;i++) {
		//cout << "list: " << weekDays[i] << endl;
		if (getDay() == weekDays[i]) {
			if (i == 0) {
				result = "Sunday";
			}
			else {
				result = weekDays[i-1];
			}
		}
	}

	return result;
}

void dayType::addDay(int nDays)
{
	int initDay = 0;

	if (nDays < 0) {
		nDays = 0;
	}

	for (int i=0;i<7;i++) {
		if (getDay() == weekDays[i])
			initDay = i;
		else 
			initDay = 0;
	}

	int newDay = initDay + nDays;

	weekDay = weekDays[newDay%7];
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	dayType myDay("Monday");
	dayType tempDay("Sunday");

	//CHANGE THIS TO ADD A DIFFERENT NUMBER OF DAYS
	int aDay = 4; 

	if (aDay < 0) {
		cout << "\nERROR: illegal number of days added. Setting days added to 0.\n";
		aDay = 0;
	}

	myDay.print();
	cout << endl;

	cout << "The previous day is: " << myDay.prevDay() << endl;

	cout << "The next day is: " << myDay.nextDay() << endl;

	myDay.addDay(aDay);
	cout << "Adding " << aDay << " days. The new day is " << myDay.getDay() << 
					"." << endl;

	tempDay.print();
	cout << endl;

	cout << "The previous day is: " << tempDay.prevDay() << endl;

	cout << "The next day is: " << tempDay.nextDay() << endl;

	tempDay.addDay(aDay);
	cout << "Adding " << aDay << " days. The new day is " << tempDay.getDay() << 
					"." << endl;

	return 0;
}

