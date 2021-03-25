#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Taken from code by Dr. Rizk, Dr. Malik (textbook), and internet websites          //
///////////////////////////////////////////////////////////////////////////////////////

// MAIN FUNCTIONS /////////////////////////////////////////////////////////////////////
bool balanceChecker(string eq)
{
	int i, count=0, count1=0, count2=0;

	for (i=0; i<eq.size(); i++) {
	if(eq[i] == '[')
		++count;
	else if(eq[i] == '{')
		++count1;
	else if(eq[i] == '(')
		++count2;
	else if(eq[i] == ']')
		--count;
	else if(eq[i] == '}')
		--count1;
	else if(eq[i] == ')')
		--count2;
	}

	if (count == 0 && count1 == 0 && count2 == 0)
		return true;
	return false;
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main() {

	bool isBalanced;

	string eq1 = "(7+3*[5-23]+{22-11})/2*(2-1)";

	cout << "\nThe equation " << eq1;
	
	isBalanced = balanceChecker(eq1);
	if (isBalanced)
		cout << " is balanced.\n\n";
	else
		cout << " is not balanced.\n\n";

	string eq2 = "(7+3*[5-23]+{22-11}/2*(2-1)";

	cout << "The equation " << eq2;
	
	isBalanced = balanceChecker(eq2);
	if (isBalanced)
		cout << " is balanced.\n\n";
	else
		cout << " is not balanced.\n\n";

	return 0;
}