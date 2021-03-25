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

class lineType
{
	private:
		double xCoeff;
		double yCoeff;
		double constTerm;
		bool hasSlope;
		
	public:
		lineType();
		lineType(double a, double b, double c);

		double getXCoefficient() const;
		double getYCoefficient() const;
		double getConstantTerm() const;

		void setXCoefficient(double coeff);
		void setYCoefficient(double coeff);
		void setConstantTerm(double c);

		void setLine(double a, double b, double c);
				
		string equation() const;

		double slope() const;

		bool verticalLine() const;
		bool horizontalLine() const;

		bool equalLines(lineType otherLine) const;

		bool parallel(lineType otherLine) const;

		bool perpendicular(lineType otherLine) const;

		string pointOfIntersection(lineType otherLine);

		void printComparison(lineType otherLine);
};

// CLASS FUNCTIONS ////////////////////////////////////////////////////////////////////

//default constructor
lineType::lineType()
{
	xCoeff = 0;
	yCoeff = 0;
	constTerm = 0;
	hasSlope = false;
}

//constructor
lineType::lineType(double a, double b, double c)
{
	xCoeff = a;
	yCoeff = b;
	constTerm = c;
}

double lineType::getXCoefficient() const
{
	double result = xCoeff;
	return result;
}

double lineType::getYCoefficient() const
{
	double result = yCoeff;
	return result;
}

double lineType::getConstantTerm() const
{
	double result = constTerm;
	return result;
}

void lineType::setXCoefficient(double coeff) 
{
	xCoeff = coeff;
}
	
void lineType::setYCoefficient(double coeff)
{
	yCoeff = coeff;
}

void lineType::setConstantTerm(double c)
{
	constTerm = c;
}

void lineType::setLine(double a, double b, double c)
{
	if (a == 0 && b == 0) {
		cout << "\nERROR: The a & b coefficients cannot both be 0. Exiting program.";
		exit(0);
	}
	else {
		xCoeff = a;
		yCoeff = b;
		constTerm = c;
	}
} //end setLine

//Returns string containing line equation.
string lineType::equation() const
{
	string result = "";

	stringstream xStream;
	xStream << fixed << setprecision(0) << getXCoefficient();
	string x = xStream.str();
	if (x == "1")
		x = "";

	stringstream yStream;
	string y;

	stringstream cStream;
	cStream << fixed << setprecision(0) << getConstantTerm();
	string c = cStream.str();

	result = result + x;

	if (getYCoefficient() > 0 || getYCoefficient() == 0) {
		yStream << fixed << setprecision(0) << getYCoefficient();
		y = yStream.str();
		if (y == "1")
			y = "";
		result = result + "x + ";
	}
	else {
		yStream << fixed << setprecision(0) << (-1*getYCoefficient());
		y = yStream.str();
		result = result + "x - ";
	}

	result = result + y;
	result = result + "y = ";
	result = result + c;
	return result;
} //end equation

//Returns the slope.
double lineType::slope() const
{
	bool hasSlope = true;

	if (horizontalLine())
		return 0;

	return (-1 * getXCoefficient()) / getYCoefficient();
} //end slope

//Returns true if line is vertical.
bool lineType::verticalLine() const
{
	if (getYCoefficient() == 0) {
		bool hasSlope = false;
		return true;
	}
	return false;
}

//Returns true if line is horizontal.
bool lineType::horizontalLine() const
{
	if (getXCoefficient() == 0)
		return true;
	return false;
}

//Returns true if both lines are the same.
bool lineType::equalLines(lineType otherLine) const
{
	if (equation() == otherLine.equation())
		return true;
	return false;
}    

//Function to determine if this line is parallel to otherLine.
bool lineType::parallel(lineType otherLine) const
{
	if ((verticalLine() == true && otherLine.verticalLine() == true) && 
			round(getConstantTerm()) != round(otherLine.getConstantTerm()))
		return true;
	if (!verticalLine() && !otherLine.verticalLine()) {
		if (slope() == otherLine.slope() && 
			  round(getConstantTerm()) != round(otherLine.getConstantTerm()))
			return true;
	}
	return false;
}

//Function to determine if this line is perperdicular to otherLine.
bool lineType::perpendicular(lineType otherLine) const
{
	if ((horizontalLine() && otherLine.verticalLine()) ||
			(verticalLine() && otherLine.horizontalLine()))
		return true;
		if (!verticalLine() && !otherLine.verticalLine())
			if (slope() * otherLine.slope() == -1)
				return true;
	return false;
}

//If lines intersect, then this function finds the point of intersection.
string lineType::pointOfIntersection(lineType otherLine) 
{
	string result = "";

	//inspired by geeks4geeks website
	if (!parallel(otherLine)) {

		double det = getXCoefficient()*otherLine.getYCoefficient() - 
								 otherLine.getXCoefficient()*getYCoefficient(); 

		double interX = (otherLine.getYCoefficient()*getConstantTerm() - 
										 getYCoefficient()*otherLine.getConstantTerm()) / det; 
    double interY = (getXCoefficient()*otherLine.getConstantTerm() - 
										 otherLine.getXCoefficient()*getConstantTerm()) / det; 

		stringstream xStream;
		xStream << fixed << setprecision(3) << interX;
		string x = xStream.str();

		stringstream yStream;
		yStream << fixed << setprecision(3) << interY;
		string y = yStream.str();

		result = result + "(";
		result = result + x;
		result = result + ", ";
		result = result + y;
		result = result + ")";
		return result;
	}
	else
		return result = "None, the lines do not intersect.";
} //end pointOfIntersection

//output
void lineType::printComparison(lineType otherLine)
{
	cout << "\nLine 1 is " << equation() << endl;
	cout << "\nLine 2 is " << otherLine.equation() << endl;

	//error checking
	if ((getXCoefficient() == 0 && getYCoefficient() == 0 ) || 
			(otherLine.getXCoefficient() && otherLine.getYCoefficient() == 0)) {
		cout << "\nERROR: The x & y coefficients of a line cannot both be 0." << 
						" Exiting program.";
		exit(0);
	}

	if (equalLines(otherLine)) {
		cout << "\nThe two lines are the same line and have infinite intersection points.";
	}
	else {
		if (parallel(otherLine))
			cout << "\nThe two lines are parallel to each other.\n";
		else
			cout << "\nThe two lines are NOT parallel to each other.\n";
		if (perpendicular(otherLine))
			cout << "\nThe two lines are perpendicular to each other.\n";
		else
			cout << "\nThe two lines are NOT perpendicular to each other.\n";
		cout << "\nThe intersection point of the two lines is: " << 
		        pointOfIntersection(otherLine);
	}
} //end printComparison

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
	lineType line1(2, 2, 5);
	lineType line2(2, 2, 5);

	line1.printComparison(line2);

	cout << "\n\n--------------------------------------------------------------------\n";

	lineType line3(4, 7, 9);
	lineType line4(4, 7, 3);

	line3.printComparison(line4);

	cout << "\n\n--------------------------------------------------------------------\n";

	lineType line5(2, 3, 1);
	lineType line6(3, -2, 1);

	line5.printComparison(line6);

	cout << "\n\n--------------------------------------------------------------------\n";

	lineType line7(1, 2, 24);
	lineType line8(32, -3, 31);

	line7.printComparison(line8);

	cout << "\n\n--------------------------------------------------------------------\n";

	lineType line9(0, 0, 4);
	lineType line10(3, 1, 2);

	line9.printComparison(line10);

	return 0;
}

