#include <iostream>
#include <string>
#include "ConverterU_A.h"

using namespace std;

//constructor
ConverterU_A::ConverterU_A() : Converter() {}

//getters   
double ConverterU_A::GetExchangeRate() const {return exchange_rate;}

double ConverterU_A::GetExchangeRate(string from, string to) const {
	double result;
	
	if (from == "A" || to == "A") {
		if (from == "U") {
			result = GetExchangeRate();
		}
		else {
			result = 1 / GetExchangeRate();
		}
	}

	return result;
}

//setter
void ConverterU_A::SetExchangeRate(double r) {exchange_rate = r;}  