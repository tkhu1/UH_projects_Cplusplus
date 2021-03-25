#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Malik (textbook)                                           //
///////////////////////////////////////////////////////////////////////////////////////

class clockType
{
	private:
    int hr;
	  int min;
		int sec;
	public: 
		clockType();
		 
		clockType(int hours, int minutes, int seconds);

		void setTime(int hours, int minutes, int seconds);
		void getTime(int& hours, int& minutes, int& seconds) const;
		void printTime() const;
		void incrementSeconds();
		void incrementMinutes();
		void incrementHours();
		bool equalTime(const clockType& otherClock) const;
};

// CLASS FUNCTIONS ////////////////////////////////////////////////////////////////////

//default constructor
clockType::clockType() 
{
	hr = 0;
	min = 0;
	sec = 0;
}

//constructor
clockType::clockType(int hours, int minutes, int seconds)
{
	if (0 <= hours && hours < 24)
		hr = hours;
	else
		hr = 0;
	if (0 <= minutes && minutes < 60)
		min = minutes;
	else
		min = 0;
	if (0 <= seconds && seconds < 60)
		sec = seconds;
	else
		sec = 0;
}

void clockType::setTime(int hours, int minutes, int seconds)
{
	if (0 <= hours && hours < 24)
		hr = hours;
	else
		hr = 0;
	if (0 <= minutes && minutes < 60)
		min = minutes;
	else
		min = 0;
	if (0 <= seconds && seconds < 60)
		sec = seconds;
	else
		sec = 0;
}

void clockType::getTime(int& hours, int& minutes, int& seconds) const
{
	hours = hr;
	minutes = min;
	seconds = sec;
}

void clockType::printTime() const
{
	if (hr < 10)
		cout << "0";
	cout << hr << ":";
	if (min < 10)
		cout << "0";
	cout << min << ":";
	if (sec < 10)
		cout << "0";
	cout << sec;
}

void clockType::incrementHours()
{
	hr++;
	if (hr > 23)
		hr = 0;
}

void clockType::incrementMinutes()
{
	min++;
	if (min > 59) {
		min = 0;
		incrementHours(); //increment hours
	}
}

void clockType::incrementSeconds()
{
	sec++;
	if (sec > 59) {
		sec = 0;
		incrementMinutes(); //increment minutes
	}
}

bool clockType::equalTime(const clockType& otherClock) const
{
	return (hr == otherClock.hr
					&& min == otherClock.min
					&& sec == otherClock.sec);
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	clockType myClock(8, 12, 30);
	clockType yourClock(12, 35, 45);

	cout << "\nMy clock time is ";
	myClock.printTime();
	cout << endl;

	cout << "\nYour clock time is ";
	yourClock.printTime();
	cout << endl;

	myClock.setTime(5, 2, 30);
	cout << "\nSetting new time for my clock. My clock's new time is ";
	myClock.printTime();
	cout << endl;

	cout << "\nIncrementing my clock's time by one hour. My new time is ";
	myClock.incrementHours();
	myClock.printTime();
	cout << endl;

	cout << "\nIncrementing your clock's time by one minute. Your new time is ";
	yourClock.incrementMinutes();
	yourClock.printTime();
	cout << endl;

	if (myClock.equalTime(yourClock)) {
		cout << "\nMy clock is the same time as your clock.\n";
	}
	else {
		cout << "\nMy clock is not the same time as your clock.\n";
	}

	return 0;
}

