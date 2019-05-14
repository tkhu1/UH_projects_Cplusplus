#ifndef CONVERTERU_C
#define CONVERTERU_C

#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ConverterU_C : public Converter {
  public:
		ConverterU_C(); //default         
		double GetExchangeRate() const; 
		virtual double GetExchangeRate(string from, string to) const;
		void SetExchangeRate(double r);         

	private:
		double exchange_rate;
};

#endif