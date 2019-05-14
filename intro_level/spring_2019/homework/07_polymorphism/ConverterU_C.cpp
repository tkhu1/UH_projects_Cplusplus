#include <iostream>
#include <string>
#include "ConverterU_C.h"

using namespace std;

//constructor
ConverterU_C::ConverterU_C() : Converter() {}

//getters   
double ConverterU_C::GetExchangeRate() const {return exchange_rate;}

double ConverterU_C::GetExchangeRate(string from, string to) const {
	double result;
	
	if (from == "C" || to == "C") {
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
void ConverterU_C::SetExchangeRate(double r) {exchange_rate = r;}  