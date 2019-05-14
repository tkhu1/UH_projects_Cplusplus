#ifndef CONVERTERU_D
#define CONVERTERU_D

#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ConverterU_D : public Converter {
  public:
		ConverterU_D(); //default         
		double GetExchangeRate() const; 
		virtual double GetExchangeRate(string from, string to) const;
		void SetExchangeRate(double r);         

	private:
		double exchange_rate;
};

#endif