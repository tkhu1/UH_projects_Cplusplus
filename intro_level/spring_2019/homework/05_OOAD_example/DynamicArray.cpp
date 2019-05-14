//Use this file to write the definition of all of your class' functions. Remember to include headers and libraries.
#include <iostream>
#include <string>
using namespace std;

#include "DynamicArray.h"

// default constructor
DynamicArray::DynamicArray() {  
  arraySize = 1;
  arr = new int[arraySize];
  numOfElements = 0;
}

// constructor
DynamicArray::DynamicArray(int size) {
  arraySize = size;

  if (arraySize < 1) {
      arraySize = 1;
  }
  arr = new int[arraySize];
  numOfElements = 0;
}

// copy constructor
DynamicArray::DynamicArray(const DynamicArray &a) {
  arr = new int[a.arraySize];
  // loops and copies array 'a' into arr pointer
  for (int i = 0; i < a.arraySize; i++) {
      arr[i] = a.arr[i];
  }
  // copies members   
  arraySize = a.arraySize;
  numOfElements = a.numOfElements;
}

// assignment operator
DynamicArray& DynamicArray::operator=(const DynamicArray& rhs) {
  // check for self assignment 
  if (this != &rhs) { 
    delete [] arr;
    
	  arr = new int[rhs.arraySize];
	  for(int i = 0; i < rhs.arraySize; i++) {
		  arr[i] = rhs.arr[i];
    }
    // assigns members   
    arraySize = rhs.arraySize;
    numOfElements = rhs.numOfElements;
  }
  return *this;
}

// destructor
DynamicArray::~DynamicArray() {
  delete [] arr;
}

// accessors //////////////////////////////////////////////////////////////////////////
string DynamicArray::toString() const {
  string result = "";
  if (numOfElements > 0) {
    for (int i = 0; i < numOfElements; i++) {
      result += to_string(arr[i]);
      result += ",";
    }
    result.pop_back();
    return result;
  }
  else {
    cout << "No element\n";
  }
}

string DynamicArray::toString(int pos) const {
  string result = "";
  // checks for valid index parameter
  if ( (pos >= 0) && (pos < numOfElements) ) {
    for (int i = 0; i < numOfElements; i++) {
      if (i == pos)
        result += to_string(arr[i]);
    }
    return result;
  }
  else {
    cout << "Invalid index\n";
  }
}

// mutators ///////////////////////////////////////////////////////////////////////////
void DynamicArray::addElement(int num) {
  numOfElements++;
  if (numOfElements > arraySize) {
    // temp array   
    int tempSize = arraySize * 2;
	  int *tempArr = new int[tempSize];
    // copies array into temp array
	  for (int i = 0; i < tempSize; i++) {
		  tempArr[i] = arr[i];
    }
    delete [] arr;

    // resizing and recopying into array
    arr = new int[tempSize];
	  for (int i = 0; i < tempSize; i++) {
		  arr[i] = tempArr[i];
    }
    arr[numOfElements - 1] = num;

    arraySize = tempSize;

    delete [] tempArr;
  }
  else {
    arr[numOfElements - 1] = num;
  }
}

void DynamicArray::deleteElement(int num) {
  for (int i = 0; i < arraySize; i++) {
    if (arr[i] == num) {
      // starts deletion
      numOfElements--;
      // if array needs to be shrinked
      if (numOfElements <= (arraySize / 2)) {
        // temp array   
        int tempSize = arraySize / 2;
        int *tempArr = new int[tempSize];
        // starts copying array into temp array
        for (int j = 0; j < i; j++) {
          tempArr[j] = arr[j];
        }
        // skips position of deleted element and resumes copy
        for (int k = i; k < tempSize; k++) {
            tempArr[k] = arr[k+1];
        }

        delete [] arr;

        // resizing and recopying into array
        arr = new int[tempSize];
        for (int i = 0; i < tempSize; i++) {
          arr[i] = tempArr[i];
        }
        arraySize = tempSize;

        delete [] tempArr;
      }
      // else array does not need to be shrinked
      else {
        // temp array   
        int tempSize = arraySize;
        int *tempArr = new int[tempSize];
        // starts copying array into temp array
        for (int j = 0; j < i; j++) {
          tempArr[j] = arr[j];
        }
        // skips position of deleted element and resumes copy
        for (int k = i; k < tempSize; k++) {
            tempArr[k] = arr[k+1];
        }

        delete [] arr;

        // resizing and recopying into array
        arr = new int[tempSize];
        for (int i = 0; i < tempSize; i++) {
          arr[i] = tempArr[i];
        }
        arraySize = tempSize;

        delete [] tempArr;
        }
      // ends loop
      break;
    }
  }
}
