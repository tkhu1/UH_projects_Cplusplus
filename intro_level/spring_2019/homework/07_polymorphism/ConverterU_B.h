#ifndef CONVERTERU_B
#define CONVERTERU_B

#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ConverterU_B : public Converter {
  public:
		ConverterU_B(); //default         
		double GetExchangeRate() const; 
		virtual double GetExchangeRate(string from, string to) const;
		void SetExchangeRate(double r);         

	private:
		double exchange_rate;
};

#endif