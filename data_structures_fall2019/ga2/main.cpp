#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <math.h>
#include <iomanip>

using namespace std;

/*
 GROUP CONSISTED OF TYLER HU & ARMANDO MATA & MITCHELL MONTVALVO
 WE ALL CONTRIBUTED TO THE CODE
 */

//CLASSES//////////////////////////////////////////////////////////////////////////////
class Player {
public:
    int number;
    int age;
		string isOnCourt; //holds C/B value for player status
    
    int totalTime;
    int courtTime;
    
    //doubly linked list pointers
    Player *next;
    Player *prev;
    
    //default constructor
    Player()
    {
        this->number = -1;
        this->age = -1;
				this->isOnCourt = "B";
        
        this->totalTime = 0;
        this->courtTime = 0;
        
        this->next = NULL;
        this->prev = NULL;
    }
    
    //constructor
    Player(int number, int age)
    {
        this->number = number;
        this->age = age;
        
        this->next = NULL;
        this->prev = NULL;
    }
};

// BENCH PLAYER CLASS /////////////////////////////////////////////////////////////////
class Bench: public Player {
public:
    //pointers
    Player *head;
    Player *tail;
		//holds value for deciding bench selection
		int LeftOfBench = 0;						
    
    //constructor
    Bench()
    {
        this->head = NULL;
        this->tail = NULL;
    }
    
    //adds empty player node to end of doubly linked bench
    void addEnd(Player *baller)
    {
        //creates head node if list is empty
        if (head == NULL) {
            head = baller;
            tail = baller;
            
            return;
        }
        
        baller->prev = tail; //sets new node 'previous' to tail
        tail->next = baller; //sets tail 'next' to new node
        tail = baller;       //new node is now tail
    }
        
    //FOR DEBUG
    void print()
    {
        cout << "Bench:\n";
        
        Player *temp = head; //CCes head pointer
        
        while (temp != NULL) {
            cout << temp->number << " " << temp->age << " " << 
						        temp->isOnCourt << endl;
            if (temp->next != NULL) {
						}
            temp = temp->next;
        }
    }
    
		//takes bench player's info and swaps with old player.
    Player swapToBench(Player *old) 
    {
				Player replacePlayer;
				Player *cu = head;
				//removes second player from the head of the bench and returns its data
				if (LeftOfBench == 0) {
						cu = cu->next;
						//copies bench node's data into new court player
						replacePlayer.number = cu->number;
						replacePlayer.age = cu->age;
						replacePlayer.isOnCourt = "C";
						replacePlayer.totalTime = cu->totalTime;
						replacePlayer.courtTime = cu->courtTime;
						//copies oldest player's data into a node added to end of bench list
						Player *replacedPlayer = new Player; 
						replacedPlayer->number = old->number;
						replacedPlayer->age = old->age;
						replacedPlayer->totalTime = old->totalTime;
						addEnd(replacedPlayer);
						//delete replacedPlayer;
						//deletes current bench node
						if(cu->next != NULL)
								cu->next->prev = cu->prev;
						if(cu->prev != NULL)
								cu->prev->next = cu->next;     
						//sets next bench selection to the right of the bench
						LeftOfBench = 1;

						return replacePlayer;
				}
				//removes second player from the tail of the bench and returns its data
				else {
						cu = tail->prev;
						//copies bench node's data into new court player
						replacePlayer.number = cu->number;
						replacePlayer.age = cu->age;
						replacePlayer.isOnCourt = "C";
						replacePlayer.totalTime = cu->totalTime;
						replacePlayer.courtTime = cu->courtTime;
						//copies oldest player's data into a node added to end of bench list
						Player *replacedPlayer = new Player; 
						replacedPlayer->number = old->number;
						replacedPlayer->age = old->age;
						replacedPlayer->totalTime = old->totalTime;
						addEnd(replacedPlayer);
						//delete replacedPlayer;
						//deletes current bench node
						if(cu->next != NULL)
								cu->next->prev = cu->prev;
						if(cu->prev != NULL)
								cu->prev->next = cu->next;     
						//sets next bench selection to the right of the bench
						LeftOfBench = 0;

						return replacePlayer;
				}
		}
};


// COURT PLAYER CLASS /////////////////////////////////////////////////////////////////
class Court: public Player {
public:
    Player *head;
    Player *tail;
    int size;
    
    //default constructor
    Court()
    {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }
    
    //adds empty player node to end of circularly double linked court
    void addEnd(Player *baller)
    {
        //increments number of players on court for sorting needs
        ++size;
        //creates head node if list is empty
        if (head == NULL) {
            head = baller;
            tail = baller;
            
            return;
        }
        
        baller->prev = tail; //sets new node 'previous' to tail
        tail->next = baller; //sets tail 'next' to new node
        tail = baller;       //new node is now tail
        tail->next = head;   //loops new tail back to head
    }
    
    //returns the pointer to the specified player node
    Player *getBallerIndex(int ballerIndex)
    {
        //ERROR checking
        if (head == NULL)
            return NULL;
        if (ballerIndex < 0 || ballerIndex >= size) {
            cout << "ERROR: Invalid player selection entered" << endl;
            return NULL;
        }
        
        Player *temp = head; //CCes head pointer
        int counter = 0;
        
        while (temp != NULL) {
            if (counter == ballerIndex)
                return temp;
            
            temp = temp->next;
            ++counter;
        }
        //if not found
        return NULL;
    }
    
    //FOR DEBUG
    void print()
    {
        cout << "Court:\n";
        
        Player *temp = head; //CCes head pointer
        
        while (temp != NULL) {				
            cout << temp->number << " " << temp->age << " " << 
						        temp->isOnCourt << endl;
            if (temp->next != head) {
						}
            else {
                break;
						}
            temp = temp->next;
        }
    }

		//checks to see if a tenth of the oldest persons age has been played.
    bool ageCheck() 
    { 
				Player *baller = getOldest();
				float time = (baller->age / 10.0);
				int playTime = round(time); //rounds to nearest integer
				if (baller->courtTime >= playTime) {
					  return true;
				}
				return false;
    }

		//returns pointer to oldest player node on court
    Player *getOldest() 
		{ 
      	Player *oldestPlayer = getBallerIndex(0);
          	for (int j=0; j < size-1; j++) {
           			//retrieves nodes
             		Player *baller = getBallerIndex(j+1);
								//sorts by player age
								if (oldestPlayer->age > baller->age) {
										//oldest is older than next baller
										continue;
								}
								else { //makes oldest Player new baller
										oldestPlayer = getBallerIndex(j+1);
								}
            }
        return oldestPlayer;
    }
    
		//adds time to courtTime of each player on the court
    void addCourtTime() 
    {
				for (int i=0; i < size; i++) {
						Player *baller = getBallerIndex(i);
						baller->courtTime = baller->courtTime + 1;
				}
    }
    
		//tallies total time played at end of quarter
    void tallyTime() { 
    	  for (int i=0; i < size-1; i++) {
						Player *baller = getBallerIndex(i);
						baller->totalTime = baller->courtTime + baller->totalTime;
						baller->courtTime = 0;
				}
    }

		//laces newPlayer's data in old Player's spot
    void swapToCourt(Player *oldPlayer, Player newPlayer) 
		{ 
				Player *cu = oldPlayer;
				cu->number = newPlayer.number;
        cu->age = newPlayer.age;
				cu->isOnCourt = "C";
        cu->totalTime = newPlayer.totalTime;
        cu->courtTime = 0;
    }

    //sorts the court by player number
    void sort()
    {
        //bubble sort
        for (int i=0; i < size-1; i++) {
            for (int j=0; j < size-i-1; j++) {
                //retrieves nodes
                Player *baller1 = getBallerIndex(j);
                Player *baller2 = getBallerIndex(j+1);
                
                //sorts by player number
                if (baller1->number > baller2->number) {
                    //swaps player 1 and 2
                    int temp = baller1->number;
                    baller1->number = baller2->number;
                    baller2->number = temp;
                }
            }
        }
    }
};


// MAIN FUNCTIONS /////////////////////////////////////////////////////////////////////

/*shuffles arrays to simulate random generation. 
  NOTE: shuffle function inspired by code examples from stack overflow website*/
template <typename myType>
void shuffleArray(myType *arr, int size)
{
		if (size > 1) {
				srand(time(NULL));
				for (int i = 0; i < size-1; i++) {
						int j = i + rand() / (RAND_MAX/(size-i) + 1);
						//swaps array values
						myType temp = arr[j];
						arr[j] = arr[i];
						arr[i] = temp;
				}
		}
		else
			cout << "ERROR detected: invalid array size detected for shuffling." << endl;
}

Player* mergelists(Court court, Bench bench) 
{
		Player* finalhead; //this will be the head of our merged list
		Player* finaltail; //this will be the tail of our merged list

		Player* head1 = court.head; //just making these temp variables to make...
		Player* tail1 = court.tail; //...the nomenclature more readable
		Player* head2 = bench.head; //
		Player* tail2 = bench.tail; //

		tail1->next = head2; //connecting end of first list
		head2->prev = tail1; //to head of second list
		tail2->next = head1; //connecting end of second list
		head1->prev = tail2; //to head of first list

		finalhead = head1; //
		finaltail = tail2; //

		return finalhead;
}

void finalprint(Player* head)
{
		cout << "Merged List:\n";
		
		Player *temp = head; //CCes head pointer
		
		while (temp != NULL) {				
				cout << temp->number << " " << temp->age << " " << 
								temp->isOnCourt << " " << temp->totalTime << endl;
				if (temp->next != head) {
				}
				else {
						break;
				}
				temp = temp->next;
		}
}

Player* getPlayerIndex(Player* head, int ballerIndex)
{
		//ERROR checking
		if (head == NULL)
				return NULL;
		if (ballerIndex < 0 || ballerIndex >= 12) {
				cout << "ERROR: Invalid player selection entered" << endl;
				return NULL;
		}
		
		Player *temp = head; //CCes head pointer
		int counter = 0;
		
		while (temp != NULL) {
				if (counter == ballerIndex)
						return temp;
				
				temp = temp->next;
				++counter;
		}
		//if not found
		return NULL;
}

//sorts by total time played (ascending)
void sortTime(Player* finalHead) 
{
		//error checking for empty list
    if (finalHead == NULL) 
        return; 

		//holds value to keep loop running
		int swapped;
		//pointer to another pointer to ccer
    Player *cu; 

		//bubble sort
		for (int i = 0; i <= 12; i++) { 
  
        cu = finalHead; 
        swapped = 0; 
  
        for (int j = 0; j < 12 - i - 1; j++) { 
						//pointers for moving and comparing
            Player *p1 = cu; 
            Player *p2 = p1->next; 
  
            if (p1->totalTime < p2->totalTime) { 
								//swaps data of nodes
								int tempNum = p1->number;
								int tempAge = p1->age;
								string tempStatus = p1->isOnCourt;
								int tempTotalTime = p1->totalTime;

								p1->number = p2->number;
								p1->age = p2->age;
								p1->isOnCourt = p2->isOnCourt;
								p1->totalTime = p2->totalTime;

								p2->number = tempNum;
								p2->age = tempAge;
								p2->isOnCourt = tempStatus;
								p2->totalTime = tempTotalTime;

                swapped = 1; 
            } 
						//moves to next node
            cu = cu->next; 
        } 
  
        //exits if the loop ended without any swap
        if (swapped == 0) 
            break; 
    } 
} 

//sorts by age (descending)
void sortAge(Player* finalHead) 
{
		//error checking for empty list
    if (finalHead == NULL) 
        return; 

		//holds value to keep loop running
		int swapped;
		//pointer to another pointer to ccer
    Player *cu; 

		//bubble sort
		for (int i = 0; i <= 12; i++) { 
  
        cu = finalHead; 
        swapped = 0; 
  
        for (int j = 0; j < 12 - i - 1; j++) { 
						//pointers for moving and comparing
            Player *p1 = cu; 
            Player *p2 = p1->next; 
  
            if (p1->age > p2->age) { 
								//swaps data of nodes
								int tempNum = p1->number;
								int tempAge = p1->age;
								string tempStatus = p1->isOnCourt;
								int tempTotalTime = p1->totalTime;

								p1->number = p2->number;
								p1->age = p2->age;
								p1->isOnCourt = p2->isOnCourt;
								p1->totalTime = p2->totalTime;

								p2->number = tempNum;
								p2->age = tempAge;
								p2->isOnCourt = tempStatus;
								p2->totalTime = tempTotalTime;

                swapped = 1; 
            } 
						//moves to next node
            cu = cu->next; 
        } 
  
        //exits if the loop ended without any swap
        if (swapped == 0) 
            break; 
    } 
}
	
// MAIN ///////////////////////////////////////////////////////////////////////////////
int main()
{
  	ofstream outFile;
    outFile.open("report3.txt");
    //init sequential arrays containing player numbers and ages
		int playerNumbersArr[12]; //holds player numbers from 1 - 12
		for (int i=0; i<12; i++) {
      	playerNumbersArr[i] = i+1;
    }
		int playerAgesArr[18]; //holds player ages from 20 - 37
		int initAge = 20;
		for (int i=0; i<18; i++) {
      	playerAgesArr[i] = initAge;
				initAge++;
    }

		//shuffles player number and age arrays to simulate random gen
		shuffleArray(playerNumbersArr, 12);
		shuffleArray(playerAgesArr, 18);

    //init dynamic array of Player classes
    Player *lockerRoom = new Player[12];
    for (int i=0; i<12; i++) {
        lockerRoom[i].number = playerNumbersArr[i];
        lockerRoom[i].age = playerAgesArr[i];
    }

		//shuffles locker room to simulate random gen
		shuffleArray(lockerRoom, 12);

		/*
		//DEBUG
		for (int i=0; i<12; i++){
				cout << lockerRoom[i].number << " " << lockerRoom[i].age << " " <<
								lockerRoom[i].isOnCourt << endl;
		}
		*/
    
    bool oldestOnCourt; //determines if we switch out oldest person

    //init court obj
    Court gameCourt;
		//assigns locker room player to court
    for (int i=0; i<5; i++) { //i is player number
        Player *baller = new Player(lockerRoom[i].number, lockerRoom[i].age);
				baller->isOnCourt = "C";
				gameCourt.addEnd(baller);
    }
		//sorts the court
    gameCourt.sort();

		// UNCOMMENT THIS TO SEE INITIAL COURT --------------------------------------------
		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
    //gameCourt.print(); //DEBUG
    
    //init bench obj
    Bench gameBench;
    for (int i=5; i<12; i++) { //i is player number
				Player *baller = new Player(lockerRoom[i].number, lockerRoom[i].age);
				baller->isOnCourt = "B";
				gameBench.addEnd(baller);
    }
    
		// UNCOMMENT THIS TO SEE INITIAL BENCH --------------------------------------------
		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
    //gameBench.print(); //DEBUG
    
    //The game itself
    outFile << "Report 3" << endl << endl;
    outFile << "Replacement Player\t Replacing\t Replacement time in the quarter" <<endl;
    int courtToBenchJersey = 0; //jersey number of court player getting benched
    int benchToCourtJersey = 0; //Jersey of court player getting benched
  
    for (int i = 1; i < 5; i++) { // four quarters
        for (int j = 1; j < 13; j++) { //12 minute quarters
            gameCourt.addCourtTime(); //adds time to each player;
            oldestOnCourt = gameCourt.ageCheck(); //checks oldest player's play time

						/*true means that the oldest person has currently played a tenth of his
						  age in minutes and must be taken off.*/
            if (oldestOnCourt == true){ //take off oldest person
							  Player *old = gameCourt.getOldest(); 

								/*
								//DEBUG							
								cout << endl;
								cout << j << " " << old->number << " " << old->age << " " << 
											  old->isOnCourt << " " << old->totalTime << " " <<
												old->courtTime << endl << endl;
								*/

								//prepares oldest player to be moved to bench
                old->isOnCourt = "B";
								old->totalTime = old->totalTime + old->courtTime;
								old->courtTime = 0;

								//holds oldest player's jersey number
								courtToBenchJersey = old->number;

								/*LINE 135: takes the oldest player's data and swaps to bench with 
								  total time played. Creates player obj to be swapped to court.*/
              	Player newPlayer = gameBench.swapToBench(old);
								
								//holds newest player's jersey number
								benchToCourtJersey = newPlayer.number;
                
								//replaces oldest player's info with new player's info.
                gameCourt.swapToCourt(old, newPlayer);

								//outputs to report 3
								outFile << setfill(' ') << left << setw(21) << benchToCourtJersey << 
								           setw(12) << courtToBenchJersey <<
													 "Q" << i << ": " << j << endl;
            }
        }
        gameCourt.tallyTime(); //Puts remaining court time in total time for the quarter. Players currently on court will stay on court
    }

		// UNCOMMENT THESE LINES TO SEE AFTER GAME COURT AND BENCH ------------------------
		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
		//DEBUG
    //gameCourt.sort();
		//cout << endl;
    //gameCourt.print();
		//gameBench.print(); 

		//MERGE COURT AND BENCH LISTS
		Player *finalhead = mergelists(gameCourt, gameBench);
		//finalprint(finalhead); //DEBUG

		//SORT BY TOTAL TIME PLAYED (ASCENDING)
		sortTime(finalhead);
		//finalprint(finalhead); //DEBUG

		outFile.close();
		outFile.open("report1.txt");
		outFile << "Report 1" << endl << endl;
    outFile << "Number\t Minutes played" <<endl;

		//outputs final merged list to report 1 (sorted by time played)
		Player *cuR1 = finalhead; 
    for (int i=0; i<12; i++) { 
        outFile << setfill(' ') << left << setw(9) << cuR1->number << 
								   cuR1->totalTime << endl;
        cuR1 = cuR1->next; 
    }     

		//SORT BY AGE (DESCENDING)
		sortAge(finalhead);
		//finalprint(finalhead); //DEBUG

		outFile.close();
		outFile.open("report2.txt");
		outFile << "Report 2" << endl << endl;
    outFile << "Age\t Number\t Minutes played" <<endl;
		//outputs final merged list to report 1 (sorted by time played)
		Player *cuR2 = finalhead; 
    for (int i=0; i<12; i++) { 
        outFile << setfill(' ') << left << setw(5) << cuR2->age << setw(8) <<
								   cuR2->number << cuR2->totalTime << endl;
        cuR2 = cuR2->next; 
    }     

    /* GROUP NOTES
     
     *merge court and bench at end of game [DONE]
     *sort merged linked list by time played for report 1 (ascending) [DONE]
		 *sort merged linked list by age for report 2 (descending) [DONE]
     *output report functions 
     
     1. Take Old guys info from court 
     2. Take new players info From Bench 
     3. Replace Node with old guys info 
     4. Replace old guys node with new player info 
     */
    
    delete [] lockerRoom;
    
    return 0;
}
