#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

Converter::Converter() 
{
	exchange_rate = 1.0;
}
   
double Converter::GetExchangeRate() const {return exchange_rate;}

double Converter::GetExchangeRate(string from, string to) const {
	double result;

	if (from == "U") {
		result = GetExchangeRate();
	}
	else {
		result = 1 / GetExchangeRate();
	}
	return result;
}

void Converter::SetExchangeRate(double r) {exchange_rate = r;}  