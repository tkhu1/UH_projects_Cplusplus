#include <iostream>
#include <string>
#include "ConverterU_F.h"

using namespace std;

//constructor
ConverterU_F::ConverterU_F() : Converter() {}

//getters   
double ConverterU_F::GetExchangeRate() const {return exchange_rate;}

double ConverterU_F::GetExchangeRate(string from, string to) const {
	double result;
	
	if (from == "F" || to == "F") {
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
void ConverterU_F::SetExchangeRate(double r) {exchange_rate = r;}  