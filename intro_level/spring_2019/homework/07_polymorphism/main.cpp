#include <iostream>
#include <iomanip>
#include <string>
#include "Converter.h"
#include "ConverterU_A.h"
#include "ConverterU_B.h"
#include "ConverterU_C.h"
#include "ConverterU_D.h"
#include "ConverterU_E.h"
#include "ConverterU_F.h"
#include "ConverterU_G.h"

using namespace std;

int main() {
	ConverterU_A u2a;
	ConverterU_B u2b; 
	ConverterU_C u2c;
	ConverterU_D u2d;
	ConverterU_E u2e;
	ConverterU_F u2f;
	ConverterU_G u2g; 

	const int num_curr = 7; //number of currencies 
	string temp; //holds cin line
	double in_rate; //holds actual cin rate
	
	Converter* converters[] = { &u2a, &u2b, &u2c, &u2d, &u2e, &u2f, &u2g };

	string currencies[num_curr] = { "A", "B", "C", "D", "E", "F", "G" }; //for output

	for (int i = 0; i<num_curr; i++) {
		getline(cin, temp);
		temp.erase(0, 5); //truncates first five string elements
		in_rate = stod(temp); //converts string to double
		//cout << temp << endl; //DEBUG
		//cout << in_rate << endl; //DEBUG
		converters[i]->SetExchangeRate(in_rate);
	}

	// output ////////////////////////////////////////////////////////////////////
	cout << setprecision(2) << fixed;

	//sets the first currency
	for (int i = 0; i<num_curr; i++) { 
		//loops through and compares every second to first
		for (int j = 0; j<num_curr; j++) { 
			//skips self-comparison
			if (j != i) { 
				double output_rate = converters[i]->GetExchangeRate(currencies[i], "U") * 
									 converters[j]->GetExchangeRate("U", currencies[j]);
				cout << "1" << currencies[i] << " = " << output_rate << currencies[j] << "\n";
			}
		}
	}

	return 0;
}
