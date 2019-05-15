#include <iostream>

using namespace std;

int main()
{
   int myArray[] = {10, 2, 6, 12, 4};
   int n = 5; //array size
   
   int i, j, temp;
   for (i = 0; i<n; i++) 
      // Hint: last i elements are already in place
      for (j = 0; j<n-1; j++) 
         if (myArray[j] > myArray[j+1])
			   {
            temp = myArray[j];
            myArray[j] = myArray[j+1];
            myArray[j+1] = temp;
			   }

   cout << "Sorted array:\n";
   
   for(i = 0; i<n; i++)
      cout << myArray[i] << " ";
      
   return 0;
}
