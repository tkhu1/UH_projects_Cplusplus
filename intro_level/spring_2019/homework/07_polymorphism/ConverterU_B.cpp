#include <iostream>
#include <string>
#include "ConverterU_B.h"

using namespace std;

//constructor
ConverterU_B::ConverterU_B() : Converter() {}

//getters   
double ConverterU_B::GetExchangeRate() const {return exchange_rate;}

double ConverterU_B::GetExchangeRate(string from, string to) const {
	double result;
	
	if (from == "B" || to == "B") {
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
void ConverterU_B::SetExchangeRate(double r) {exchange_rate = r;}  