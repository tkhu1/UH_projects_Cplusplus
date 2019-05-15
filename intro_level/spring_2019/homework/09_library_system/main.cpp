#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//classes-----------------------------------------------------------------------------

//login handlers/////////////////////////////////////////////////////////////////////////
//base user login handler////////////////////////////////////////////////////////////////
class BaseUserLogin {
	public:
		//default constructor
		BaseUserLogin() {holder.name = "default"; holder.password = "password";}
		//constructor
		BaseUserLogin(string n, string pw) {holder.name = n; 
		                                    holder.password = pw + "\0";} //to match array
		//login info getter
		virtual bool GetFinderStatus() {return LoginFinder();}

	protected:
		//reads user/pw file into array
		virtual bool LoginFinder() {
			int size = 0; //for counting number of user/pw combos
			string filename = "users_all.txt";
			string temp;

			ifstream infs(filename);
			while (getline(infs, temp)) {
				size++;
			}
			//DEBUG
			//cout << size; 
			//cout << holder.name << " " << holder.password << endl;

			infs.close(); //closes file
			infs.clear(); //clears input buffer
			infs.open(filename); //re-inputs file content to input buffer

			userInfo loginArr[size]; //declares array of userInfo structs
			for (int i = 0; i < size; i++) {
				infs >> loginArr[i].name >> loginArr[i].password;
				if (loginArr[i].name == holder.name && loginArr[i].password == holder.password)
					return true; //if user input is found in array
			}
			infs.close();

			//DEBUG
			/*for (int i = 0; i < size; i++) {
				cout << loginArr[i].name << " " << loginArr[i].password << endl;
			}*/
			return false;
		}

	private:
		struct userInfo {
			string name;
			string password;
		};
		//declares struct that holds user info
		userInfo holder;		
};

//librarian user login handler///////////////////////////////////////////////////////////
class LibrarianUserLogin : public BaseUserLogin {
	public:
		//default constructor
		LibrarianUserLogin() : BaseUserLogin() {holder.name = "admin"; holder.password = 		 																			  "password";}
		//constructor
		LibrarianUserLogin(string n, string pw) : BaseUserLogin() {holder.name = n; 
																   holder.password = pw + "\0";} //to match array
		//login info getter
		bool GetFinderStatus() {return LoginFinder();}

	private:
		struct userInfo {
			string name;
			string password;
		};
		//declares struct that holds user info
		userInfo holder;

		//reads user/pw file into array
		bool LoginFinder() {
			int size = 0; //for counting number of user/pw combos
			string filename = "users_librarians.txt";
			string temp;

			ifstream infs(filename);
			while (getline(infs, temp)) {
				size++;
			}
			//DEBUG
			//cout << size; 
			//cout << holder.name << " " << holder.password << endl;

			infs.close(); //closes file
			infs.clear(); //clears input buffer
			infs.open(filename); //re-inputs file content to input buffer

			userInfo loginArr[size]; //declares array of userInfo structs
			for (int i = 0; i < size; i++) {
				infs >> loginArr[i].name >> loginArr[i].password;
				if (loginArr[i].name == holder.name && loginArr[i].password == holder.password)
					return true; //if user input is found in array
			}
			infs.close();

			//DEBUG
			/*for (int i = 0; i < size; i++) {
				cout << loginArr[i].name << " " << loginArr[i].password << endl;
			}
			*/
			return false;
		}
};

//user menu handlers/////////////////////////////////////////////////////////////////////
//base user//////////////////////////////////////////////////////////////////////////////
class UserBase {
	public:
		//default constructor
		UserBase() {};

		//struct for each book
		struct bookList {
			string author;
			string title;
			string year;
			string publisher;
			string ISBN;
			string status; //holds value for checked in/out
		};

		//prints login success
		void WelcomeMsg() {
			cout << "\nCustomer Login successful.\n\n";
			MainMenu();
		}

		//shows menu and gets choice
		virtual void MainMenu() {
			string userMenuChoice;
			const string errorMsgBook; //throw value
			
			cout << setfill('*') << setw(65) << ""; 
			cout << "\n*                                                               *";
			cout << "\n*                    LIBRARY OF ALEXANDRIA                      *";
			cout << "\n*                     CUSTOMER MAIN MENU                        *";
			cout << "\n*                                                               *";
			cout << "\n*   -To search for a book to checkout/return, please enter 1.   *";
			cout << "\n*   -To see all our books for checkout/return, please enter 2.  *";
			cout << "\n*   -To exit the portal, please enter 0.                        *";
			cout << "\n*                                                               *";
			cout << endl << setfill('*') << setw(65) << "" << endl; 
			cout << "\nChoice: ";

			try {
				cin >> userMenuChoice;

				if (userMenuChoice == "1") {
					SearchBooks();
				}
				else if (userMenuChoice == "2") {
					AllBooks();
				}
				else if (userMenuChoice == "0") {
					cout << "\nExiting portal. Please visit us again soon.";
					exit(0);
				}
				//error handling
				else
					throw (errorMsgBook);
			}
			//error catch for login menu
			catch (string error) {
				cout << "\nInvalid choice. Please enter your selection again.\n" << endl;
				MainMenu();
			}
		}
		
	protected:
		//prints out all books fitting search term for librarian editing
		void SearchBooks() {
			int size = 0; //for counting number of books
			string filename = "books.txt";
			string temp, temp2;
			//gets the number of books
			ifstream infsSearchBook(filename);
			while (getline(infsSearchBook, temp)) {
				if (temp == "BOOK")
					size++;
			}
			infsSearchBook.close(); //closes file
			infsSearchBook.clear(); //clears input buffer
			infsSearchBook.open(filename); //re-inputs file content to input buffer

			//builds array of bookList structs from file
			bookList bookArr[size]; //declares array of bookList structs
			for (int i = 0; i < size; i++) {
				getline (infsSearchBook, temp2); //holds BOOK
				getline (infsSearchBook, bookArr[i].author);
				getline (infsSearchBook, bookArr[i].title);
				getline (infsSearchBook, bookArr[i].year);
				getline (infsSearchBook, bookArr[i].publisher);
				getline (infsSearchBook, bookArr[i].ISBN);
				getline (infsSearchBook, bookArr[i].status);
				getline (infsSearchBook, temp2); //holds newline
			}
			infsSearchBook.close();
		
			string userMenuChoice, search;
			bool found = false; //checks if book found
			const string errorMsgBook; //throw value

			cout << "\nYou may search for a book by Title, Author, " <<
			        "Year, Publisher, ISBN, or Availabilty.";
			cout << "\nBook availibility is denoted by 'Available' or 'Not Available'.";
			cout << "\n\n(Search term must be exact)";
			cout << "\nPlease enter your search term: ";

			try {
				cin >> search;
				//searchs book array
				for (int i = 0; i < size; i++) {
					if (search == bookArr[i].author || search == bookArr[i].title ||
						search == bookArr[i].year || search == bookArr[i].publisher ||
						search == bookArr[i].ISBN || search == bookArr[i].status) {
						//prints out found books
						cout << "\nBOOK NUMBER (" << i+1 << ")" << endl;
						cout << setfill('-') << setw(40) << ""; 
						cout << "\nTITLE:        " << bookArr[i].title;
						cout << "\nAUTHOR:       " << bookArr[i].author;
						cout << "\nYEAR:         " << bookArr[i].year;
						cout << "\nPUBLISHER:    " << bookArr[i].publisher;
						cout << "\nISBN:         " << bookArr[i].ISBN;
						cout << "\nAVAILABILITY: " << bookArr[i].status << endl;	
						found = true;
					}
				}

				//if books are not found
				if (found == false) {
					cout << endl << setfill('-') << setw(40) << ""; 
					cout << "\nBook not found. Returning to the main menu.\n\n";
					MainMenu(); //calls main menu
				}
	
				//mini-menu
				cout << setfill('-') << setw(40) << ""; 
				cout << "\n\n-To check out or return a book, please enter its book number.";
				cout << "\n-To return to the main menu, please enter 0.";
				cout << "\n\nChoice: ";

				cin >> userMenuChoice;
				
				for (int j = 0; j < size; j++) {
					string converter = to_string(j+1);
					if (userMenuChoice == converter && search == bookArr[j].status) {
						if (bookArr[j].status == "Available") {
							bookArr[j].status = "Not Available";
							cout << "\nBook checked out. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size); //calls function to modify file
							MainMenu(); //calls main menu
						}
						else {
							bookArr[j].status = "Available";
							cout << "\nBook checked in. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size);  //calls function to modify file
							MainMenu(); //calls main menu
						}
					}
				}
				//exits to main menu
				if (userMenuChoice == "0") {
					cout << endl;
					MainMenu();
				}
				//error handling
				else
					throw (errorMsgBook);
			}
			//error catch for login menu
			catch (string error) {
				cout << "\nInvalid choice. Returning to main menu.\n" << endl;
				MainMenu();
			}
		}
    
		//prints out entire book collection for checking in/out
		virtual void AllBooks() {
			int size = 0; //for counting number of books
			string filename = "books.txt";
			string temp, temp2;
			//gets the number of books
			ifstream infsBooks(filename);
			while (getline(infsBooks, temp)) {
				if (temp == "BOOK")
					size++;
			}
			infsBooks.close(); //closes file
			infsBooks.clear(); //clears input buffer
			infsBooks.open(filename); //re-inputs file content to input buffer

			//builds array of bookList structs from file
			bookList bookArr[size]; //declares array of bookList structs
			for (int i = 0; i < size; i++) {
				getline (infsBooks, temp2); //holds BOOK
				getline (infsBooks, bookArr[i].author);
				getline (infsBooks, bookArr[i].title);
				getline (infsBooks, bookArr[i].year);
				getline (infsBooks, bookArr[i].publisher);
				getline (infsBooks, bookArr[i].ISBN);
				getline (infsBooks, bookArr[i].status);
				getline (infsBooks, temp2); //holds newline
			}
			infsBooks.close();
			
			string userMenuChoice;
			const string errorMsgBook; //throw value

			for (int i = 0; i < size; i++) {
				cout << "\nBOOK NUMBER (" << i+1 << ")" << endl;
				cout << setfill('-') << setw(40) << ""; 
				cout << "\nTITLE:        " << bookArr[i].title;
				cout << "\nAUTHOR:       " << bookArr[i].author;
				cout << "\nYEAR:         " << bookArr[i].year;
				cout << "\nPUBLISHER:    " << bookArr[i].publisher;
				cout << "\nISBN:         " << bookArr[i].ISBN;
				cout << "\nAVAILABILITY: " << bookArr[i].status << endl;
			}
			//mini-menu
			cout << setfill('-') << setw(40) << ""; 
			cout << "\n\n-To check out or return a book, please enter its book number.";
			cout << "\n-To return to the main menu, please enter 0.";
			cout << "\n\nChoice: ";

			try {
				cin >> userMenuChoice;

				for (int i = 0; i < size; i++) {
					string converter = to_string(i+1);
					if (userMenuChoice == converter) {
						if (bookArr[i].status == "Available") {
							bookArr[i].status = "Not Available";
							cout << "\nBook checked out. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size); //calls function to modify file
							MainMenu(); //calls main menu
						}
						else {
							bookArr[i].status = "Available";
							cout << "\nBook checked in. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size);  //calls function to modify file
							MainMenu(); //calls main menu
						}
					}
				}
				//exits to main menu
				if (userMenuChoice == "0") {
					MainMenu();
				}
				//error handling
				else
					throw (errorMsgBook);
			}
			//error catch for login menu
			catch (string error) {
				cout << "\nInvalid choice. Returning to main menu.\n" << endl;
				MainMenu();
			}
		}

		//writes array of books into book file
		virtual void FileWriter(bookList arr[], int size) {
			string filename = "books.txt";

			ofstream outfsBooks;
			outfsBooks.open(filename, ofstream::out | ofstream::trunc); //clears file
			outfsBooks.close();
			outfsBooks.open(filename); //reopens file for writing

			for (int i = 0; i < size; i++) {
				outfsBooks << "BOOK\n";
				outfsBooks << arr[i].author << "\n";
				outfsBooks << arr[i].title << "\n";
				outfsBooks << arr[i].year << "\n";
				outfsBooks << arr[i].publisher << "\n";
				outfsBooks << arr[i].ISBN << "\n";
				outfsBooks << arr[i].status << "\n\n";
			}
			outfsBooks.close();
		}

};

//librarian user/////////////////////////////////////////////////////////////////////////
class UserLibrarian : public UserBase {
	public:
		//default constructor
		UserLibrarian() : UserBase() { cout << "\nLibrarian Login successful.\n\n"; }

		//struct for each book
		struct bookList {
			string author;
			string title;
			string year;
			string publisher;
			string ISBN;
			string status; //holds value for checked in/out
		};

		//shows menu and gets choice
		void MainMenu() {
			string userMenuChoice;
			const string errorMsgBook; //throw value
		
			cout << setfill('*') << setw(65) << ""; 
			cout << "\n*                                                               *";
			cout << "\n*                    LIBRARY OF ALEXANDRIA                      *";
			cout << "\n*                     LIBRARIAN MAIN MENU                       *";
			cout << "\n*                                                               *";
			cout << "\n*   -To search for a book for modification, please enter 1.     *";
			cout << "\n*   -To see all books for modification, please enter 2.         *";
			cout << "\n*   -To add a book, please enter 3.                             *";
			cout << "\n*   -To delete a book, please enter 4.                          *";
			cout << "\n*   -To exit the portal, please enter 0.                        *";
			cout << "\n*                                                               *";
			cout << endl << setfill('*') << setw(65) << "" << endl; 
			cout << "\nChoice: ";

			try {
				cin >> userMenuChoice;

				if (userMenuChoice == "1") {
					SearchBooks();
				}
				else if (userMenuChoice == "2") {
					AllBooks();
				}
				else if (userMenuChoice == "3") {
					AddBooks();
				}
				else if (userMenuChoice == "4") {
					DeleteBooks();
				}
				else if (userMenuChoice == "0") {
					cout << "\nExiting portal. Please visit us again soon.";
					exit(0);
				}
				//error handling
				else
					throw (errorMsgBook);
			}
			//error catch for login menu
			catch (string error) {
				cout << "\nInvalid choice. Please enter your selection again.\n" << endl;
				MainMenu();
			}
		}
	
	private:
		//prints out all books fitting search term for librarian editing
		void SearchBooks() {
			int size = 0; //for counting number of books
			string filename = "books.txt";
			string temp, temp2;
			//gets the number of books
			ifstream infsSearchBook(filename);
			while (getline(infsSearchBook, temp)) {
				if (temp == "BOOK")
					size++;
			}
			infsSearchBook.close(); //closes file
			infsSearchBook.clear(); //clears input buffer
			infsSearchBook.open(filename); //re-inputs file content to input buffer

			//builds array of bookList structs from file
			bookList bookArr[size]; //declares array of bookList structs
			for (int i = 0; i < size; i++) {
				getline (infsSearchBook, temp2); //holds BOOK
				getline (infsSearchBook, bookArr[i].author);
				getline (infsSearchBook, bookArr[i].title);
				getline (infsSearchBook, bookArr[i].year);
				getline (infsSearchBook, bookArr[i].publisher);
				getline (infsSearchBook, bookArr[i].ISBN);
				getline (infsSearchBook, bookArr[i].status);
				getline (infsSearchBook, temp2); //holds newline
			}
			infsSearchBook.close();
		
			string userMenuChoice, search;
			bool found = false; //checks if book found
			const string errorMsgBook; //throw value

			cout << "\nYou may search for a book by Title, Author, " <<
			        "Year, Publisher, ISBN, or Availabilty.";
			cout << "\nBook availibility is denoted by 'Available' or 'Not Available'.";
			cout << "\n\n(Search term must be exact)";
			cout << "\nPlease enter your search term: ";

			try {
				cin >> search;
				//searchs book array
				for (int i = 0; i < size; i++) {
					if (search == bookArr[i].author || search == bookArr[i].title ||
						search == bookArr[i].year || search == bookArr[i].publisher ||
						search == bookArr[i].ISBN || search == bookArr[i].status) {
						//prints out found books
						cout << "\nBOOK NUMBER (" << i+1 << ")" << endl;
						cout << setfill('-') << setw(40) << ""; 
						cout << "\nTITLE:        " << bookArr[i].title;
						cout << "\nAUTHOR:       " << bookArr[i].author;
						cout << "\nYEAR:         " << bookArr[i].year;
						cout << "\nPUBLISHER:    " << bookArr[i].publisher;
						cout << "\nISBN:         " << bookArr[i].ISBN;
						cout << "\nAVAILABILITY: " << bookArr[i].status << endl;	
						found = true;
					}
				}

				//if books are not found
				if (found == false) {
					cout << endl << setfill('-') << setw(40) << ""; 
					cout << "\nBook not found. Returning to the main menu.\n\n";
					MainMenu(); //calls main menu
				}
	
				//mini-menu
				cout << setfill('-') << setw(40) << ""; 
				cout << "\n\n-To mark a book as checked out or in, please enter its book number.";
				cout << "\n-To return to the main menu, please enter 0.";
				cout << "\n\nChoice: ";

				cin >> userMenuChoice;
				
				for (int j = 0; j < size; j++) {
					string converter = to_string(j+1);
					if (userMenuChoice == converter && search == bookArr[j].status) {
						if (bookArr[j].status == "Available") {
							bookArr[j].status = "Not Available";
							cout << "\nBook marked as checked out. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size); //calls function to modify file
							MainMenu(); //calls main menu
						}
						else {
							bookArr[j].status = "Available";
							cout << "\nBook marked checked in. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size);  //calls function to modify file
							MainMenu(); //calls main menu
						}
					}
				}
				//exits to main menu
				if (userMenuChoice == "0") {
					MainMenu();
				}
				//error handling
				else
					throw (errorMsgBook);
			}
			//error catch for login menu
			catch (string error) {
				cout << "\nInvalid choice. Returning to main menu.\n" << endl;
				MainMenu();
			}
		}
    
		//prints out entire book collection for checking in/out
		void AllBooks() {
			int size = 0; //for counting number of books
			string filename = "books.txt";
			string temp, temp2;
			//gets the number of books
			ifstream infsBooks(filename);
			while (getline(infsBooks, temp)) {
				if (temp == "BOOK")
					size++;
			}
			infsBooks.close(); //closes file
			infsBooks.clear(); //clears input buffer
			infsBooks.open(filename); //re-inputs file content to input buffer

			//builds array of bookList structs from file
			bookList bookArr[size]; //declares array of bookList structs
			for (int i = 0; i < size; i++) {
				getline (infsBooks, temp2); //holds BOOK
				getline (infsBooks, bookArr[i].author);
				getline (infsBooks, bookArr[i].title);
				getline (infsBooks, bookArr[i].year);
				getline (infsBooks, bookArr[i].publisher);
				getline (infsBooks, bookArr[i].ISBN);
				getline (infsBooks, bookArr[i].status);
				getline (infsBooks, temp2); //holds newline
			}
			infsBooks.close();
			
			string userMenuChoice;
			const string errorMsgBook; //throw value

			for (int i = 0; i < size; i++) {
				cout << "\nBOOK NUMBER (" << i+1 << ")" << endl;
				cout << setfill('-') << setw(40) << ""; 
				cout << "\nTITLE:        " << bookArr[i].title;
				cout << "\nAUTHOR:       " << bookArr[i].author;
				cout << "\nYEAR:         " << bookArr[i].year;
				cout << "\nPUBLISHER:    " << bookArr[i].publisher;
				cout << "\nISBN:         " << bookArr[i].ISBN;
				cout << "\nAVAILABILITY: " << bookArr[i].status << endl;
			}
			//mini-menu
			cout << setfill('-') << setw(40) << ""; 
			cout << "\n\n-To mark a book as checked out or in, please enter its book number.";
			cout << "\n-To return to the main menu, please enter 0.";
			cout << "\n\nChoice: ";

			try {
				cin >> userMenuChoice;
				cout << endl;

				for (int i = 0; i < size; i++) {
					string converter = to_string(i+1);
					if (userMenuChoice == converter) {
						if (bookArr[i].status == "Available") {
							bookArr[i].status = "Not Available";
							cout << "\nBook marked as checked out. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size); //calls function to modify file
							MainMenu(); //calls main menu
						}
						else {
							bookArr[i].status = "Available";
							cout << "\nBook marked as checked in. Returning to main menu.\n" << endl;
							FileWriter(bookArr, size);  //calls function to modify file
							MainMenu(); //calls main menu
						}
					}
				}
				//exits to main menu
				if (userMenuChoice == "0") {
					MainMenu();
				}
				//error handling
				else
					throw (errorMsgBook);
			}
			//error catch for login menu
			catch (string error) {
				cout << "\nInvalid choice. Returning to main menu.\n" << endl;
				MainMenu();
			}
		}

		//adds a book to the book file 
		void AddBooks() {
			int size = 0; //for counting number of books
			string filename = "books.txt";
			string temp, temp2;
			//gets the number of books
			ifstream infsBooks(filename);
			while (getline(infsBooks, temp)) {
				if (temp == "BOOK")
					size++;
			}
			infsBooks.close(); //closes file
			infsBooks.clear(); //clears input buffer
			infsBooks.open(filename); //re-inputs file content to input buffer

			int newSize = size + 1;
			//builds array of bookList structs from file
			bookList bookArr[newSize]; //declares array of bookList structs
			for (int i = 0; i < size; i++) {
				getline (infsBooks, temp2); //holds BOOK
				getline (infsBooks, bookArr[i].author);
				getline (infsBooks, bookArr[i].title);
				getline (infsBooks, bookArr[i].year);
				getline (infsBooks, bookArr[i].publisher);
				getline (infsBooks, bookArr[i].ISBN);
				getline (infsBooks, bookArr[i].status);
				getline (infsBooks, temp2); //holds newline
			}
			infsBooks.close();

			cout << "\nENTER TITLE: ";
			cin >> bookArr[size].title;
			cout << "\nENTER AUTHOR: ";
			cin >> bookArr[size].author;
			cout << "\nENTER YEAR: ";
			cin >> bookArr[size].year;
			cout << "\nENTER PUBLISHER: ";
			cin >> bookArr[size].publisher;
			cout << "\nENTER ISBN: ";
			cin >> bookArr[size].ISBN;
			cout << "\nENTER AVAILABILITY: ";
			cin >> bookArr[size].status;
			
			cout << "\nBook added. Returning to main menu.\n" << endl;
			FileWriter(bookArr, newSize);  //calls function to modify file
			MainMenu(); //calls main menu
		}

    	//delete a book 
		void DeleteBooks() {
			int size = 0; //for counting number of books
			string filename = "books.txt";
			string temp, temp2;
			//gets the number of books
			ifstream infsBooks(filename);
			while (getline(infsBooks, temp)) {
				if (temp == "BOOK")
					size++;
			}
			infsBooks.close(); //closes file
			infsBooks.clear(); //clears input buffer
			infsBooks.open(filename); //re-inputs file content to input buffer

			//builds array of bookList structs from file
			bookList bookArr[size]; //declares array of bookList structs
			for (int i = 0; i < size; i++) {
				getline (infsBooks, temp2); //holds BOOK
				getline (infsBooks, bookArr[i].author);
				getline (infsBooks, bookArr[i].title);
				getline (infsBooks, bookArr[i].year);
				getline (infsBooks, bookArr[i].publisher);
				getline (infsBooks, bookArr[i].ISBN);
				getline (infsBooks, bookArr[i].status);
				getline (infsBooks, temp2); //holds newline
			}
			infsBooks.close();
			
			string userMenuChoice;
			const string errorMsgBook; //throw value

			for (int i = 0; i < size; i++) {
				cout << "\nBOOK NUMBER (" << i+1 << ")" << endl;
				cout << setfill('-') << setw(40) << ""; 
				cout << "\nTITLE:        " << bookArr[i].title;
				cout << "\nAUTHOR:       " << bookArr[i].author;
				cout << "\nYEAR:         " << bookArr[i].year;
				cout << "\nPUBLISHER:    " << bookArr[i].publisher;
				cout << "\nISBN:         " << bookArr[i].ISBN;
				cout << "\nAVAILABILITY: " << bookArr[i].status << endl;
			}
			//mini-menu
			cout << setfill('-') << setw(40) << ""; 
			cout << "\n\n-To delete a book, please enter its book number.";
			cout << "\n-To return to the main menu, please enter 0.";
			cout << "\n\nChoice: ";

			try {
				cin >> userMenuChoice;
				cout << endl;

				for (int i = 0; i < size; i++) {
					string converter = to_string(i+1);
					if (userMenuChoice == converter) {
						int deleted = stoi(converter);
						deleted--;
						//cout << deleted;
						bookList delArr[deleted]; //declares array of bookList structs
						for (int i = 0; i < deleted; i++) {
							delArr[i].title = bookArr[i].title;
							delArr[i].author = bookArr[i].author;
							delArr[i].year = bookArr[i].year;
							delArr[i].publisher = bookArr[i].publisher;
							delArr[i].ISBN = bookArr[i].ISBN;
							delArr[i].status = bookArr[i].status;
						}
						for (int i = deleted; i < size-1; i++) {
							delArr[i].title = bookArr[i+1].title;
							delArr[i].author = bookArr[i+1].author;
							delArr[i].year = bookArr[i+1].year;
							delArr[i].publisher = bookArr[i+1].publisher;
							delArr[i].ISBN = bookArr[i+1].ISBN;
							delArr[i].status = bookArr[i+1].status;
						}
						cout << "\nBook deleted. Returning to main menu.\n" << endl;
						FileWriter(delArr, deleted); //calls function to modify file
						MainMenu(); //calls main menu
					}
				}
				//exits to main menu
				if (userMenuChoice == "0") {
					MainMenu();
				}
				//error handling
				else
					throw (errorMsgBook);
			}
			//error catch for login menu
			catch (string error) {
				cout << "\nInvalid choice. Returning to main menu.\n" << endl;
				MainMenu();
			}
		}

		//writes array of books into book file
		void FileWriter(bookList arr[], int size) {
			string filename = "books.txt";

			ofstream outfsBooks;
			outfsBooks.open(filename, ofstream::out | ofstream::trunc); //clears file
			outfsBooks.close();
			outfsBooks.open(filename); //reopens file for writing

			for (int i = 0; i < size; i++) {
				outfsBooks << "BOOK\n";
				outfsBooks << arr[i].author << "\n";
				outfsBooks << arr[i].title << "\n";
				outfsBooks << arr[i].year << "\n";
				outfsBooks << arr[i].publisher << "\n";
				outfsBooks << arr[i].ISBN << "\n";
				outfsBooks << arr[i].status << "\n\n";
			}
			outfsBooks.close();
		}

};

//separate functions---------------------------------------------------------------------
//handles initial login menu and login checker//////////////////////////////////////////
int loginMenu() {
	int loginAttempt = 0; //init value
	const int attempts = 3; //max number of login attempts
	int result;
	string userChoice, name, password; // init value
	const string errorMsg; //throw value
	
	cout << "\n-If you are a customer, please enter 1.";
	cout << "\n-If you are a librarian, please enter 2.";
	cout << "\n-To exit, please enter 0.";
	cout << "\n\nChoice: ";

	try {
		cin >> userChoice;

		if (userChoice == "1") {
			//base user login attempt checker//////////////////////////////////////////////////
			while (loginAttempt < attempts+1) {
				cout << "\nUsername: ";
				cin >> name;
				cout << "Password: ";
				cin >> password;
				BaseUserLogin temp1(name, password); //temp base user login object
				//username/pw combo found
				if (temp1.GetFinderStatus() == true) {
					loginAttempt = attempts+1;
					result = 1;
				}
				//username/pw combo not found
				else {
					//outputs attempts remaining
					cout << "\nUsername and or password not found. You have " << 
							(attempts - loginAttempt) << 
							" attempts remaining.\n";
					loginAttempt++;
					//exits program
					if (loginAttempt > attempts) {
						cout << "Exiting portal. " << 
								"Please contact the front desk for assistance.";
						result = 3;
					}
				}
			}
		}
		else if (userChoice == "2") {
			//librarian user login attempt checker/////////////////////////////////////////////
			while (loginAttempt < attempts+1) {
				cout << "\nUsername: ";
				cin >> name;
				cout << "Password: ";
				cin >> password;
				LibrarianUserLogin temp2(name, password); //temp lib user login object
				//username/pw combo found
				if (temp2.GetFinderStatus() == true) {
					loginAttempt = attempts+1;
					result = 2;
				}
				//username/pw combo not found
				else {
					//outputs attempts remaining
					cout << "\nUsername and or password not found. You have " << 
							(attempts - loginAttempt) << 
							" attempts remaining.\n";
					loginAttempt++;
					//exits program
					if (loginAttempt > attempts) {
						cout << "Exiting portal. " << 
								"Please contact the front desk for assistance.";
						result = 3;
					}
			  }
			}
		}
		else if (userChoice == "0") {
			cout << "\nExiting portal. Please visit us again soon.";
			result = 3;
		}
		//error handling
		else
			throw (errorMsg);
	}
	//error catch for login menu
	catch (string error) {
    cout << "\nInvalid choice. Please enter your selection again." << endl;
		loginMenu();
  }
	return result;
}

//main-----------------------------------------------------------------------------------
int main() {
	int option;

	//welcome prompt///////////////////////////////////////////
	cout << setfill('*') << setw(40) << "" << endl; 
	cout << "*                                      *" << endl;
	cout << "*    WELCOME TO THE LOGIN PORTAL OF    *" << endl;
	cout << "*      THE LIBRARY OF ALEXANDRIA       *" << endl;
	cout << "*                                      *" << endl;
	cout << setfill('*') << setw(40) << "" << endl; 

	//calls login menu function
	option = loginMenu();
	
	if (option == 1) {
		UserBase* BasePtr = nullptr;
		BasePtr = new UserBase; //creates base user book menu object
		BasePtr->WelcomeMsg();
	}
	if (option == 2) {
		UserLibrarian* LibPtr = nullptr;
		LibPtr = new UserLibrarian;  //creates lib user book menu object
		LibPtr->MainMenu();
	}

return 0;
}
