#include <iostream>
#include <string>

using namespace std;

struct node {
	char c;
	struct node* next;
};

class list {
public:
	struct node* head;
	struct node* tail;

	//constructor
  list() {
    this->head = NULL;
    this->tail = NULL;
  }

	void addEnd(struct node *letter) {
		//creates head node if list is empty
		if (head == NULL) {
			head = letter;
			tail = letter;
			return;
		}
		
		tail->next = letter; //sets tail 'next' to new node
		tail = letter;       //new node is now tail
	}
	
	bool isVowel(char c) {
		switch(c) {
			case'a':case'e':case'i':case'o':case'u':case'A':case'E':case'I':case'O':case'U':case'y':case'Y':
				return true;
			default:
				return false;
		}

	}

	bool startsVowel() {
		if (isVowel(head->c)) {
			return true;
		}
		else {
			return false;
		}
	}

	void addWay() {
		struct node* cu;
		struct node* hyphen = new node;
		struct node* W = new node;
		struct node* A = new node;
		struct node* Y = new node;
		cu = tail;
		cu->next = hyphen;
		hyphen->c = '-';
		hyphen->next = W;
		W->c = 'w';
		W->next = A;
		A->c = 'a';
		A->next = Y;
		Y->c = 'y';
		tail = Y;
	}

	void addAy() {
		struct node* A = new node;
		struct node* Y = new node;
		tail->next = A;
		A->c = 'a';
		A->next = Y;
		Y->c = 'y';
		tail = Y;
	}

	bool searchAndRotate() {
    struct node *temp;
 	  struct node *cu;
  	struct node *hyphen = new node;

	  temp = head;

	  while (temp) {
		  //searches for vowels and adds hyphen
		  if (isVowel(temp->c)) {
				//cout << "found vowel\n";
			  hyphen->c = '-';
			  tail->next = hyphen;
			  tail = hyphen;
			  cu = head;
			  //rotates
			  while (head != temp) {
				  head = head->next;
				  tail->next = cu;
				  tail = cu;
			 	  cu = head;
			  }
			  return true;                        
		  }
		  else {
			  temp = temp->next;
		  }
	  }
	  return false;
	}
	
	void makeList(char arr[], int size) {
	  struct node *cu;
		char letter;
	  for (int i=0; i<size; i++) {
			struct node *cu = new node;
			cu->c = arr[i];
			addEnd(cu);
	  }
	}
	
	void print() {
		struct node* cu = NULL;
		cu = head;

		cout << "\nYour word in pig latin is: \n";
		
		while (cu != NULL) {
			cout << cu->c;
			cu = cu->next;
		}
	}
	
}; 

int main() {
	list pig;

	string word;

	cout << "Enter a word: \n";
	
	cin >> word;

  int size = word.length();
	//cout << "size: ";
	//cout << size;
	char arr[size];

	for(int i = 0; i < size; i++) {
		arr[i] = word[i];
		//cout << arr[i] << " ";
	}

	pig.makeList(arr, size);

	if (pig.startsVowel() == true) {
		pig.addWay();
	} 
	else if (pig.searchAndRotate()) {
		pig.addAy();
	} 
	else {
		pig.addWay();
	}
	
	pig.print();

	return 0;
}

