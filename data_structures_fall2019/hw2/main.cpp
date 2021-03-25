#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// CLASSES ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class Node {
	public:
		//data
		string wordFront;
		string sentence;
		string wordBack;
		//pointers
		Node *next;
		Node *prev;

		//default constructor
    Node()
    {
			this->wordFront = "default front";
			this->sentence = "This is a default sentence.";
			this->wordFront = "default back";
			
			this->next = NULL;
			this->prev = NULL;
    }
};

class List {
	public:
		//pointers
		Node *head;

		//constructor//////////////////////////////////////////////////////////////////////
    List()
    {
			this->head = NULL;
    }

		//builds linked list///////////////////////////////////////////////////////////////
		void AddNode (string front, string line, string back) 
		{
			Node *temp = new Node;
			//if head does not exist
			if (head == NULL) {
				temp->wordFront = front;
				temp->sentence = line;
				temp->wordBack = back;
				temp->prev = NULL;
				head = temp;
				return;
			}

			temp->wordFront = front;
			temp->sentence = line;
			temp->wordBack = back;
			
			Node *last = head;

			//finds last node to add to
    	while (last->next != NULL) { 
        last = last->next;
			}
  
    	last->next = temp;  
    	temp->prev = last;  
  
   		return;  
		}

		//searches whole list for matching first/last word to find first sentence//////////
		bool SearchFirst(Node *line) 
		{	
			//ERROR checking
			if (head == NULL) {
				cout << "ERROR detected: Empty list found when searching for first." << endl;
				return true;
			}
			bool found = false;
			//cces head
			Node *temp = head;
			//finds match
			while (temp != NULL) {
				if (line->wordFront == temp->wordBack) {
					found = true;
				}
				//cout << endl << "node at: " << temp->sentence << endl; //DEBUG
				temp = temp->next;
			}
			return found;
		}

		//searches whole list for matching first/last word to find next sentence///////////
		Node *SearchMatch(Node *line) 
		{	
			//ERROR checking
			if (head == NULL) {
				cout << "ERROR detected: Empty list found when searching for matches." << endl;
				return NULL;
			}
			//CCes head
			Node *temp = head;
			//finds match and returns pointer to match
			while (temp != NULL) {
				if (line->wordBack == temp->wordFront) {
					//DEBUG
					/*cout << "matched: " << line->wordBack << "-" << line->sentence << " / " <<
								  temp->wordFront << "-" << temp->sentence << endl; */
					return temp;
				}
				temp = temp->next;
			}
			//default return
			return NULL;
		}

		//insert node at list beginning////////////////////////////////////////////////////
		void InsertNodeBeginning (Node *front) 
		{
			//if head does not exist
			if (head == NULL) {
				cout << "ERROR detected: Empty list found. Creating list..." << endl;
				head->wordFront = front->wordFront;
				head->sentence = front->sentence;
				head->wordBack = front->wordBack;
				head->prev = NULL;
				head = front;
			}

			Node *newHead = new Node;
			newHead->wordFront = front->wordFront;
			newHead->sentence = front->sentence;
			newHead->wordBack = front->wordBack; 

			newHead->next = head;
			newHead->prev = NULL;
			head = newHead;
		}

		//insert node after current node///////////////////////////////////////////////////
		void InsertNodeAfter (Node *first, Node *second) 
		{
			//if node being added to does not exist
			if (first == NULL) {
				cout << "ERROR detected: Empty list found." << endl;
				return;
			}

			//CCes first node in comparision
			Node *temp = first;
			//CCes second node data in comparison
			Node *inserted = new Node;

			inserted->wordFront = second->wordFront;
			inserted->sentence = second->sentence;
			inserted->wordBack = second->wordBack; 

			//adjusts pointers
			inserted->next = temp->next;  
			inserted->prev = temp;  
			temp->next = inserted;  
      inserted->next->prev = inserted; 
		}
  
		//removes node from list///////////////////////////////////////////////////////////
		void DelNode(Node *delPos)
		{
			//ERROR checking
			if (head == NULL || delPos == NULL) {
				cout << "ERROR detected: Invalid node deletion detected." << endl;
				return;
			}

			Node *temp = delPos;

			//deletes head if asked
    	if (head == temp) {  
        head = temp->next;  
			}
			//only deletes if not last node
			if (temp->next != NULL) {
				temp->next->prev = temp->prev;   
			}
			//only deletes if not first node
			if (temp->prev != NULL) {
				temp->prev->next = temp->next; 
			}
			delete temp;
		}

		//sorts linked list by checking for equivalence////////////////////////////////////
		void Sorter()
		{
			//bool value to find first sentence node
			bool foundMatch = true;

			//CCes head pointer
			Node *firstFinder = head; 

			//holds found matching node
			Node *matchingNode = NULL;
			
			//finds and adds the first node to list
			while (firstFinder != NULL) {
				foundMatch = SearchFirst(firstFinder);
				if (foundMatch == false) {
					//cout << "\nfirst node at: " << firstFinder->sentence << endl; //DEBUG

					//does not change the first sentence if sorted first sentence is head
					if (firstFinder != head) {
					//adds node to beginning of list
					InsertNodeBeginning (firstFinder);

					DelNode (firstFinder);
					}
				}
				firstFinder = firstFinder->next;
			}

			//CCes new head pointer
			Node *matcher = head;
			
			//sorts rest of list after first sentence is sorted 
			while (matcher->next != NULL) {
				//finds matching node
				matchingNode = SearchMatch(matcher);

				//cout << matcher->sentence << "/" << matchingNode->sentence << endl; //DEBUG

				//adds node to after the matching sentence is found
				InsertNodeAfter (matcher, matchingNode);

				//cout << "\nmatching at: " << matcher->sentence << endl; //DEBUG

				DelNode (matchingNode);

				matcher = matcher->next;
			}
		}

		//FOR DEBUG////////////////////////////////////////////////////////////////////////
    void Print()
    {
			Node *temp = head; //CCes head pointer
			
			while (temp != NULL) {
				cout << temp->wordFront << " / " << temp->sentence << " / " << 
								temp->wordBack << endl << endl;
			
				temp = temp->next;
			}
    }
  
};

// FUNCTIONS //////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

//returns first word of input sentence in all lowercase////////////////////////////////
string GetFirstWordLower (string line, int size) {
	//stores the first word
	string result = "";
	for (int i = 0; i < size; i++) { 
		char letter = line[i];
		//stops after first word
		if (letter != ' ') { 
			//checks for alphabetical characters
			if (isalpha(letter)) {
				//changes uppercase letters to lowercase
				if (isupper(letter)) {  
            letter = tolower(letter);
				}
				//builds first word
				result = result + letter;
			}
		}
		else {
			return result;
		}
	}
	//returns empty string if invalid argument passed
	return result;
}

//returns last word of input sentence in all lowercase/////////////////////////////////
string GetLastWordLower (string line, int size) {
	//stores the last word
	string result = "";
	//stores reversed sentence
	string reverse = "";
	for (int i = size-1; i >= 0; i--) { 
		char letter = line[i];
		//stops after first word
		if (letter != ' ') { 
			//checks for alphabetical characters
			if (isalpha(letter)) {
				//changes uppercase letters to lowercase
				if (isupper(letter)) {  
            letter = tolower(letter);
				}
				//builds last word in reverse
				reverse = reverse + letter;
			}
		}
		else {
			//un-reverses last word
			for (int i = reverse.length()-1; i >= 0; i--) { 
				result = result + reverse[i];
			}
			return result;
		}
	}
	//returns empty string if invalid argument passed
	return result;
}

// MAIN ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	
	if (argc != 3 && argc != 2) {
		cout << "Invalid arguments" << endl;
		return 1;
	}

	ArgumentManager am(argc, argv);
	const string input = am.get("input");
	const string output = am.get("output");

	//error catcher
	const string errorMsg;
	//global vars
	string temp;
	int lineChecker = 0;
	//init list obj
	List thoughts;

	try {
		//init input stream
		ifstream infs(input);
		//exits if input not found
		if (!infs) {
			throw ("Could not open the input file. Exiting program.");
		}


		//reads from input stream
		while (!infs.eof()) {
			getline(infs, temp);
			int lineSize = 0;
			//stores length of sentence line
			if (!temp.empty() && temp != "\r") {
				//input storage
				string tempFirstWord = "";
				string tempLastWord = "";
				//stores length of sentence line
				lineSize = temp.length();
				//cout << lineSize << " ";
				//avoids empty lines
				while (lineSize == 0) { 
					getline(infs, temp); 
					lineSize = temp.length();
				}
				//checks for empty strings
				if (lineSize != 0) {
					//holds number of lines in input file
					lineChecker++;
					//cout << " " << lineChecker; //DEBUG
					//gets words ready for comparison
					tempFirstWord = GetFirstWordLower (temp, lineSize);
					tempLastWord = GetLastWordLower (temp, lineSize);

					//creates and adds a node to list (data = sentence & its first and last words)
					thoughts.AddNode (tempFirstWord, temp, tempLastWord);

					/* //DEBUG
					cout << tempFirstWord << " / " << tempLastWord << " / " << temp << 
									endl << endl;
					*/
				}
			}  
		}
		
		//thoughts.Print(); //DEBUG

		infs.close();

		//init output stream
		ofstream outfs(output);

		//sorts list if input file is not empty
		if (lineChecker > 0) {
			thoughts.Sorter();

			//thoughts.Print(); //DEBUG

			//outputs to file
			Node *outputNode = thoughts.head; 
			while (outputNode != NULL) { 
				outfs << outputNode->sentence << endl;
				outputNode = outputNode->next; 
			}     
		}

		outfs.close();
	}

	//catches error and exits
	catch (const string error) {
		cout << error << endl;
		return 1;
	}
	//general error handling
	catch (...) { 
    cout << "Default exception generated. Exiting program." << endl;
		return 1;
  } 

	return 0;
}