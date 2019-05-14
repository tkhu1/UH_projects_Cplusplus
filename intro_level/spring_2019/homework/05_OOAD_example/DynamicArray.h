//Use this file to write the declaration of your class' attributes and functions. 

#ifndef DynamicArray_H
#define DynamicArray_H

//Your class here
class DynamicArray {
    public:
        DynamicArray(); //default constructor
        DynamicArray(int size); // constructor
        DynamicArray(const DynamicArray &a); //copy constructor
        DynamicArray& operator=(const DynamicArray& rhs); //overloaded copy assignment
      
        //accessors
        int getArraySize() const { return arraySize; }
        int getNumOfElements() const { return numOfElements; }
        string toString() const;
        string toString(int pos) const;

        //mutators
        void addElement(int num);
        void deleteElement(int num);

        //destructor
        ~DynamicArray();
    private:
        int *arr;
        int arraySize;
        int numOfElements;
};

#endif