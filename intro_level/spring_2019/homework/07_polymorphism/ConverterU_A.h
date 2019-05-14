#ifndef CONVERTERU_A
#define CONVERTERU_A

#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ConverterU_A : public Converter {
  public:
		ConverterU_A(); //default         
		double GetExchangeRate() const; 
		virtual double GetExchangeRate(string from, string to) const;
		void SetExchangeRate(double r);         

	private:
		double exchange_rate;
};

#endif