#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//option 1
string wspace_remover(string line) {

	string result = ""; //holds desired output
			
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ' ') {
		}
		else {
			result += line[i];
		}
	}
	return result;
}

//option 2
void num_chars(string line, int& result) {

	for (int i = 0; i < line.size(); i++) {
		if (line[i] != ' ') {
			result++;
		}
	}
}

//option 3
void num_words(string line, int& result) {

	result++;
}

//option 4
string vowel_replace(string line) {

	string result = ""; //holds desired output

	for (int i = 0; i < line.size(); i++) {
    
		if ((line[i] == 'a') || (line[i] == 'A') ||
		    (line[i] == 'e') || (line[i] == 'E') ||
		    (line[i] == 'i') || (line[i] == 'I') ||
		    (line[i] == 'o') || (line[i] == 'O') ||
		    (line[i] == 'u') || (line[i] == 'U')) {
			result += '3';
		}
		else {
			result += line[i];
		}
	}
	return result;
}

//option 5
void reverser(string arr[], int last) {

	string* fptr = arr;
	string* lptr = arr + last - 1;
	
	while (fptr < lptr) { 
		string temp = *fptr; 
    		*fptr = *lptr; 
    		*lptr = temp; 

		fptr++;
		lptr--;
	} 
}

int main() {
	ifstream infs;
	ofstream outfs;
	string filename, line;
	int user_choice, total_chars = 0, total_words = 0;
	int size = 0; //stores number of lines in file
	
  
	cin >> filename;
	cin >> user_choice;
  
	infs.open(filename); //inputs file content to input buffer

	while (getline(infs, line)) {
		size++;
	}
  
        //cout << size; DEBUG

	string arr[size];

	infs.close(); //closes file
	infs.clear(); //clears input buffer
	infs.open(filename); //re-inputs file content to input buffer
  
	outfs.open("output.txt");
  
	switch (user_choice) {
		//white space remover function
		case 1:
		  while (getline(infs, line)) {
				outfs << wspace_remover(line) << endl;
			}
			break;
		//number of characters function
		case 2:
			while (getline(infs, line)) {
				num_chars(line, total_chars);
			}
			outfs << total_chars;
			break;
		//number of words function
		case 3:
			while (infs >> line) {
				num_words(line, total_words);
			}
			outfs << total_words;
			break;
		//vowel-3 replacer function
		case 4:
			while (getline(infs, line)) {
				outfs << vowel_replace(line) << endl;
			}
			break;
		//reverser function
		case 5:
			int temp_size = 0;

			while (getline(infs, line)) {
					arr[temp_size] = line;
					//cout << arr[temp_size - 1] << endl; //DEBUG
					temp_size++;
				}
					
			//function call
			reverser(arr, size);
			
			for (int j = 0; j < size; j++) {
				outfs << arr[j] << endl; 
			}
			break;
	}
 
        infs.close(); //closes input file 
	outfs.close(); //closes output file

        /* 
	DEBUG
	line = "have a great night     because it is a lit time brothers n sisters";
	cout << wspace_remover(line) << endl;
	num_chars(line, total_chars);
	cout << total_chars << endl;
        //num_words(line, total_words);
	//cout << total_words << endl;
	cout << vowel_replace(line) << endl;
	cout << reverser(line);
	*/

	return 0;
}
