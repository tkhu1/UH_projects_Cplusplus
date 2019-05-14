#include <iostream>
#include <string>
#include "ConverterU_E.h"

using namespace std;

//constructor
ConverterU_E::ConverterU_E() : Converter() {}

//getters   
double ConverterU_E::GetExchangeRate() const {return exchange_rate;}

double ConverterU_E::GetExchangeRate(string from, string to) const {
	double result;
	
	if (from == "E" || to == "E") {
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
void ConverterU_E::SetExchangeRate(double r) {exchange_rate = r;}  