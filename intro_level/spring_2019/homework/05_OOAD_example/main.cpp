#include <iostream>
#include <string>
using namespace std;

#include "DynamicArray.h"

int main(){

//***********  addElements Function is Tested  ***********

   DynamicArray Darr(1);
   Darr.addElement(1);
   Darr.addElement(2);
   Darr.addElement(3);
   Darr.addElement(4);
   Darr.addElement(5);
   if (Darr.getArraySize() == 8 )
   { 
       cout << "\nCorrect Result"<<  endl;
       cout << "array Size after expansion is : 8" << endl<< endl;
   }
   else
   {
       cout << "\nYour addElement Function is not correct" << endl;
       cout << "Your arraySize after Expansion is : " << Darr.getArraySize() << endl;
       cout << "Expected Output : 8 " <<endl<< endl;
   }
   
   //*********** Constructor with invalid input  is Tested  ***********
   DynamicArray Darr2(0);
   if (Darr2.getArraySize() == 1 )
   {
       cout << "Correct Result" << endl;
       cout << "array Size after given wrong value (less than one) : 1" << endl<< endl;
   }
   else
   {
       cout << "Your constructor is not correct" << endl;
       cout << "The arraySize should be at least One" << endl<<endl;
   }

   //*********** toString Function  is Tested  ***********
   DynamicArray Darrd1(1);
   Darrd1.addElement(1);
   Darrd1.addElement(2);
   Darrd1.addElement(3);
   Darrd1.addElement(11);
   Darrd1.deleteElement(5);
   string s = Darrd1.toString();
   string str1 = "1,2,3,11";

   if(s == str1 ) {
      cout << "Correct Result for toString" << endl << endl;
   }
   else {
      cout << "Result is incorrect " << endl;
      cout << "your function prints:" ;
      cout << s << endl;
      cout << " But, expected output should be:" << str1 <<endl<<endl;
   }

   //*********** Copy Constructor  is Tested  ***********
   DynamicArray Darr5(1);
   Darr5.addElement(10);
   DynamicArray Darr6 = Darr5;
   //Darr6.addElement(10);
   Darr6.addElement(100);
   Darr6.addElement(1000);
   Darr6.deleteElement(100);
   string s1 = Darr5.toString();
   string output1 = "10";
   string s2 = Darr6.toString();
   string output2 = "10,1000";
   //if(Darr.getnumOfElements() == 3 && Darr.getarraySize() == 4)
   if (s1==output1 && s2==output2) {
        cout << "Correct Result"<< endl;
        cout << "First array has " << Darr5.toString() << endl;
        cout << "Copied array after modification has " << Darr6.toString() << endl<< endl;
   }
   else {
      cout << "Result is incorrect " << endl;
      cout << "First array has " << Darr5.toString() << " should have: 10" << endl;
      cout << "Copied array after modification has " << Darr6.toString() << " should have: 10,1000";
   }

   return 0;
}
