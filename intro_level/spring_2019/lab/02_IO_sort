/*
Open a text file and read it. The file would contain integers in each line (total number of integers not exceeding 100).

Read all the integers into an integer array. Sort the array in ascending order and then display the integers in a line with space between 
them.

Sample input file would contain:

  12
  4
  22
  94
  6
  284
  99
  3
  56
  45
  
Input is: input.txt

Output should contain:

  3 4 6 12 22 45 56 94 99 284
  
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define MAX_SIZE 100

using namespace std;

void BubbleSort (int arr[], int n)
{
	int i, j;
	int temp;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n-i-1; ++j)
		{
			// Comparing consecutive data and switching values if value at j > j+1.
			if (arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main(){

    string filename;
    int *data = new int[MAX_SIZE];
    int count = 0;

    ifstream ifs;

    cin >> filename;

    ifs.open(filename);

    while (ifs >> data[count]) {
        count++;
    }

    BubbleSort(data, count);

    for(int i=0;i<count;i++){
        cout << data[i] << " ";
    }

    ifs.close();
    delete [] data;

    return 0;

}
