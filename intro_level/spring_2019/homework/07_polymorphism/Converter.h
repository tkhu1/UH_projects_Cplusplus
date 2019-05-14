#ifndef CONVERTER_H
#define CONVERTER_H
#include <iostream>
#include <string>

using namespace std;

class Converter {
   protected:
      double exchange_rate;
      
   public:
      Converter(); //default         
      virtual double GetExchangeRate() const; 
      virtual double GetExchangeRate(string from, string to) const;
      virtual void SetExchangeRate(double r);         
};

#endif