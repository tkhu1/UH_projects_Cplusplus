#include <iostream>
#include <string>
#include "ConverterU_G.h"

using namespace std;

//constructor
ConverterU_G::ConverterU_G() : Converter() {}

//getters   
double ConverterU_G::GetExchangeRate() const {return exchange_rate;}

double ConverterU_G::GetExchangeRate(string from, string to) const {
	double result;
	
	if (from == "G" || to == "G") {
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
void ConverterU_G::SetExchangeRate(double r) {exchange_rate = r;}  