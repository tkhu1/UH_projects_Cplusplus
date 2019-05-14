#ifndef CONVERTERU_F
#define CONVERTERU_F

#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ConverterU_F : public Converter {
  public:
		ConverterU_F(); //default         
		double GetExchangeRate() const; 
		virtual double GetExchangeRate(string from, string to) const;
		void SetExchangeRate(double r);         

	private:
		double exchange_rate;
};

#endif