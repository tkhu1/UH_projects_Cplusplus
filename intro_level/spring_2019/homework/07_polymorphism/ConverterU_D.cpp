#include <iostream>
#include <string>
#include "ConverterU_D.h"

using namespace std;

//constructor
ConverterU_D::ConverterU_D() : Converter() {}

//getters   
double ConverterU_D::GetExchangeRate() const {return exchange_rate;}

double ConverterU_D::GetExchangeRate(string from, string to) const {
	double result;
	
	if (from == "D" || to == "D") {
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
void ConverterU_D::SetExchangeRate(double r) {exchange_rate = r;}  