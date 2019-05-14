#ifndef CONVERTERU_G
#define CONVERTERU_G

#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ConverterU_G : public Converter {
  public:
		ConverterU_G(); //default         
		double GetExchangeRate() const; 
		virtual double GetExchangeRate(string from, string to) const;
		void SetExchangeRate(double r);         

	private:
		double exchange_rate;
};

#endif