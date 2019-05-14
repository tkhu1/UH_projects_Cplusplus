#ifndef CONVERTERU_E
#define CONVERTERU_E

#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ConverterU_E : public Converter {
  public:
		ConverterU_E(); //default         
		double GetExchangeRate() const; 
		virtual double GetExchangeRate(string from, string to) const;
		void SetExchangeRate(double r);         

	private:
		double exchange_rate;
};

#endif