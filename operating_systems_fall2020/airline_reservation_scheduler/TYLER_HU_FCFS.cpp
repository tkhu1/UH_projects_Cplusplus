#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// FALL20 COSC3360 - HOMEWORK 2                                                      //
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
// PROFESSOR: Albert Cheng - University of Houston                                   //
///////////////////////////////////////////////////////////////////////////////////////

/*
To use the program, the following command lines are used:

command to compile:

g++ -std=c++11 TYLER_HU_SCHEDULE.cpp

command to see output in terminal:

./a.out "input_file_name.txt"


DISCLAIMER: Small portions of code have been inspired by examples from the internet,
            such as from Geeks4Geeks or Stack Overflow
*/

// 0. DATA STRUCTURES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 0.a Struct - Flight //
/*This struct represents a flight and contains all the data for a flight such as its
  flight number, number of rows, and number of seats per row.
*/
struct flight {
   string flightNum;
   int numRows;
   int numSeats;
};

// 0.b Struct - Flight Data//
/*This struct will be used as a shared memory database and represents a flight with its seats.
*/
struct flightData {
   string flightNum;
   vector<string> flightSeats;
};

// 0.c Struct - Agent //
/*This struct represents an agent and contains all the data for an agent such as its
  number and transaction times.
*/
struct agent {
   int agentNumber;
   int TimeForTicket;
   int TimeForReserve;
   int TimeForWait;
   int TimeForWaitany;
   int TimeForCancel;
   int TimeForCheckPassenger;
};

// 0.d Struct - Agent Transaction //
/*This struct represents an agent transaction and contains all the data for a transaction such as its
  agent, action, time to complete action, flight, seat, customer name, and deadline.
*/
struct agentTransaction {
   int agentNum;
   int deadline;
   int actionTime;
   int laxityTime;
   string action;
   string flightNum;
   string seat;
   string customerName;
   int customerID;
   int transactionID;
};

// 0.e Struct - Seat Data for Checked Passengers//
/*This struct contains the data for a reserved seat on a flight. This is used for the check passenger transaction.
*/
struct seatData {
   string flightNum;
   string seat;
};

// 0.f Struct - Shared Memory Wrapper for Transaction ID//
/*This struct is a wrapper for an agent transaction ID that is sent from the parent process to its children.
  This struct will be used in shared memory.
*/
struct PCSHM {
   int tID;
};

// 0.g Class - Agent Process //
/*This class represents an agent process and contains all the data for an agent such as its number,
  transaction times, and transactions command list. The function printTransactions is for troubleshooting.
*/
class Process
{
   public:
      //agent attributes
      int agentNumber;
      int TimeForTicket;
      int TimeForReserve;
      int TimeForWait;
      int TimeForWaitany;
      int TimeForCancel;
      int TimeForCheckPassenger;

      //contains transaction structs
      vector<agentTransaction> transactions;

      //default constructor
      Process()
      {
         agentNumber = 0;
         TimeForTicket = 0;
         TimeForReserve = 0;
         TimeForWait = 0;
         TimeForWaitany = 0;
         TimeForCancel = 0;
         TimeForCheckPassenger = 0;
		}
      //constructor
      Process(int num, int ticket, int reserve, int wait, int waitany, int cancel, int checkPassenger,
              vector<agentTransaction> &inTrans)
      {
         agentNumber = num;
         TimeForTicket = ticket;
         TimeForReserve = reserve;
         TimeForWait = wait;
         TimeForWaitany = waitany;
         TimeForCancel = cancel;
         TimeForCheckPassenger = checkPassenger;

         //copies input transactions matching particular agent
         for (int i = 0; i < inTrans.size(); i++) {
            if (inTrans[i].agentNum == agentNumber)
               transactions.push_back(inTrans[i]);
         }
      }

      //prints agent data for troubleshooting
      void print();
};

// 0.g-1 Class Process Functions//

//prints agent data for troubleshooting
void Process::print()
{
   cout << "agent num: " << agentNumber << " / ticket: " << TimeForTicket <<
           " / reserve: " << TimeForReserve << " / wait: " << TimeForWait <<
           " / waitany: " << TimeForWaitany << " / cancel: " << TimeForCancel <<
           " / checkP: " << TimeForCheckPassenger << endl << endl;

   for (int i = 0; i < transactions.size(); i++) {
      cout << "transID: " << transactions[i].transactionID << " / agent: " << transactions[i].agentNum <<
              " / action: " << transactions[i].action << " / flight: " << transactions[i].flightNum <<
              " / seat: " << transactions[i].seat << " / cN: " << transactions[i].customerName <<
              " / cID: " << transactions[i].customerID << " / et: " << transactions[i].actionTime <<
              " / dL: " << transactions[i].deadline << " / lt: " << transactions[i].laxityTime << endl;
   }
}

// 1. HELPER FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//comparator function for sorting by deadline
bool isEarlierDeadline (agentTransaction& x, agentTransaction& y)
{
   return x.deadline < y.deadline;
}

//comparator function for sorting by deadline
bool isEarlierLaxity (agentTransaction& x, agentTransaction& y)
{
   return x.laxityTime < y.laxityTime;
}

//fills the database 2d array in shared memory with 0s
void fillDatabaseinSHM(int *p, int cols, int rows)
{
   for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
         //accesses seat value via pointer arithmetic found on Stack Overflow website
         *(p + i*rows + j) = 0;
      }
   }
}

//tells the semaphore with semID to wait
int wait(int semID)
{
    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    return semop(semID, &sb, 1);
}

//tells the semaphore with semID to signal
int signal(int semID)
{
    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = 1;
    sb.sem_flg = SEM_UNDO;
    return semop(semID, &sb, 1);
}

//writes transactionID from an agentTransaction struct in the parent process into shared memory for use by child process
void dataCopierPSHM(struct PCSHM *p, int input)
{
   p->tID = input;
}

//reads shared memory struct to get the transaction ID in the child process
int dataCopierCSHM(struct PCSHM *p)
{
   int result = p->tID;

   return result;
}

/*
  This accesses the shared memory database to ticket/reserve/cancel a seat by altering its integer value with the customer ID if
  transaction is successful. A return value of 1 means transaction was successful, a 0 means unsuccessful, and a -1 means
  an error was encountered.
*/
int isSeatAvailableSHM(int *p, string flightMap[], vector<vector<string>>& seatMap, int numFlights, int numSeats,
                        struct agentTransaction input)
{
   //holds data
   int resultCol = 0;
   int resultRow = 0;

   bool found = false;

   string flight = input.flightNum;
   string seat = input.seat;
   int cusID = input.customerID;

   //copies starting position of shared memory pointer
   int *start;
   start = p;

   /* //troubleshooting
   cout << "\nflight DB in SHM before transaction: " << input.customerName << " with ID# " << input.customerID << " " <<
           input.action << " for " << flight << " " << seat << "\n------------------------------" << endl;
   for (int i = 0; i < numFlights; i ++) {
      cout << "flight# " << i << ": ";
      for (int j = 0; j < numSeats; j++) {
         cout << *(p + i*numFlights + j) << " ";
      }
      cout << endl;
   }
   */

   //if transaction is ticket or reserve, this block finds the seat in flight database and sets the seat value to the customer ID
   //of the transaction's customer if the seat is not already occupied.
   if (input.action[0] == 't' || input.action[0] == 'r') {
      //checks the array representing the flights by accessing getting the flight (col)
      for (int i = 0; i < numFlights; i++) {
         if (flight == flightMap[i]) {
             resultCol = i;
             found = true;
             //cout << "\n isSeat - flight found " << flightMap[i] << " at " << resultCol << endl;
         }
      }
      //if flight does not exist
      if (found == false) {
         return -1;
      }
      found = false;

      //checks the 2d array representing the flight database seat map by accessing the col (flight), then the row (seat)
      for (int j = 0; j < numSeats; j++) {
         //checks for array position of seat (row)
         if (seat == seatMap[resultCol][j]) {
            resultRow = j;
            found = true;
            //cout << "\n isSeat - seat found " << seatMap[resultCol][j] << " at (" << resultCol << ", " << resultRow << ")" << endl;
         }
      }
      //if seat does not exist
      if (found == false) {
         return -1;
      }

      //accesses the share memory flight database and changes its value to the customer ID if the value is 0 (empty seat)
      if (*(p + resultCol*numFlights + resultRow) == 0) {
         //resets pointer position
         p = start;
         //accesses seat value via pointer arithmetic found on Stack Overflow website
         *(p + resultCol*numSeats + resultRow) = cusID;

         /*
         //troubleshooting
         p = start;
         cout << "\nflight DB in SHM after transaction: " << input.customerName << " with ID# " << input.customerID << " " <<
                 input.action << " for " << flight << " " << seat << "\n------------------------------" << endl;
         for (int i = 0; i < numFlights; i ++) {
            cout << "flight# " << i << ": ";
            for (int j = 0; j < numSeats; j++) {
               cout << *(p + i*numSeats + j) << " ";
            }
            cout << endl;
         }
         cout << endl;
         */

         return 1; //seat successfully bought
      }
      else {
         return 0; //seat already occupied
      }
   }

   //if transaction is cancel, this block finds the seat in flight database and sets the seat value to back 0 if the correct
   //seat reserved by the correct customer needs to be canceled.
   if (input.action[0] == 'c' && input.action[1] == 'a') {
      //checks the array representing the flights by accessing getting the flight (col)
      for (int i = 0; i < numFlights; i++) {
         if (flight == flightMap[i]) {
             resultCol = i;
             found = true;
             //cout << "\n isSeat - flight found " << flightMap[i] << " at " << resultCol << endl;
         }
      }
      //if flight does not exist
      if (found == false) {
         return -1;
      }
      found = false;

      //checks the 2D array representing the flight database seat map by accessing the col (flight), then the row (seat)
      for (int j = 0; j < numSeats; j++) {
         //checks for array position of seat (row)
         if (seat == seatMap[resultCol][j]) {
            resultRow = j;
            found = true;
            //cout << "\n isSeat - seat found " << seatMap[resultCol][j] << " at (" << resultCol << ", " << resultRow << ")" << endl;
         }
      }
      //if seat does not exist
      if (found == false) {
         return -1;
      }

      //accesses the share memory flight database and changes its value to 0 if the value is the correct customer ID
      if (*(p + resultCol*numFlights + resultRow) == cusID) {
         //resets pointer position
         p = start;
         //accesses seat value via pointer arithmetic found on Stack Overflow website
         *(p + resultCol*numSeats + resultRow) = 0;

         /*
         //troubleshooting
         p = start;
         cout << "\nflight DB in SHM after transaction: " << input.customerName << " with ID# " << input.customerID << " " <<
                 input.action << " for " << flight << " " << seat << "\n------------------------------" << endl;
         for (int i = 0; i < numFlights; i ++) {
            cout << "flight# " << i << ": ";
            for (int j = 0; j < numSeats; j++) {
               cout << *(p + i*numSeats + j) << " ";
            }
            cout << endl;
         }
         cout << endl;
         */

         return 1; //seat successfully cancelled
      }
      else {
         return 0; //seat already occupied
      }
   }

   return -1; //default value
}

/*
This function is for check passenger transaction and finds all the reserved seats in flight database with the correct customer ID
and pushes back into the vector of seatData structs.
*/
void checkPassengerSHM (int *p, vector<struct seatData> &results, string flightMap[], vector<vector<string>>& seatMap,
                        int numFlights, int numSeats, struct agentTransaction input)
{
   int resultRow = 0;
   int resultCol = 0;
   string foundFlight;
   string foundSeat;
   int cusID = input.customerID;

   //checks the shared memory flight database by accessing the col (flight), then the row (seat)
   for (int i = 0; i < numFlights; i++) {
      for (int j = 0; j < numSeats; j++) {
         //accesses seat value via pointer arithmetic found on Stack Overflow website
         if (*(p + i*numSeats + j) == cusID) {
            resultCol = i;
            resultRow = j;
            //maps from integer flight database(col,row) to string flight&seat(flight,seat)
            foundFlight = flightMap[resultCol];
            foundSeat = seatMap[resultCol][resultRow];
            //pushes into the vector
            results.push_back({foundFlight,foundSeat});
         }
      }
   }
}



//global var for counting time
static int globalTimer = 0;

// MAIN PROGRAM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
   //initial variable declarations
   vector<agent> agents;                           //holds the input agent attributes
   vector<flight> flights;                         //holds the input flight attributes
   vector<agentTransaction> agentTransactions;     //holds the input agent transactions from input file

   // 2. INPUT HANDLING ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	string fileName = argv[1]; //stores input file name

	//working vars to parse input
	string line;
	string temp;
   string agentTrans;
   string flightNum;
   string transAction;
   string transFlight;
   string transSeat;
   string transCustomer;
   int transActionTime = 0;
   int transDeadline = 0;
   int transActionLaxity = 0;
   int flightRows = 0;
   int flightSeats = 0;
   int agentNum = 0;
   int agentTicketTime = 0;
   int agentReserveTime = 0;
   int agentWaitTime = 0;
   int agentWaitanyTime = 0;
   int agentCancelTime = 0;
   int agentCheckPassengerTime = 0;
   int numOfFlights = 0;
   int numOfAgents = 0;

	ifstream fileIn;           //input stream here
	fileIn.open(fileName);

	//error checking
	if (!fileIn) {
      cout << "ERROR: Input file does not exist. Exiting program." << endl;
      return 1;
   }
   else if (fileIn.peek() == ifstream::traits_type::eof()) {
      cout << "ERROR: Input file is empty. Exiting program." << endl;
      return 1;
   }
   else {
      //reads input file until end of file
      while (getline(fileIn, line)) {
         //checks if following lines are flights or agents
         if (line[0] == 'a' && line[1] == 'g' && line[2] == 'e' && line[3] == 'n' && line[4] == 't' ) {
            //isolates agent number
            line = line.substr(6,(line.size()-1));
            agentNum = stoi(line);
            //gets the execution time for an action
            fileIn >> agentTrans;
            fileIn >> agentTicketTime;
            fileIn >> agentTrans;
            fileIn >> agentReserveTime;
            fileIn >> agentTrans;
            fileIn >> agentWaitTime;
            fileIn >> agentTrans;
            fileIn >> agentWaitanyTime;
            fileIn >> agentTrans;
            fileIn >> agentCancelTime;
            fileIn >> agentTrans;
            fileIn >> agentCheckPassengerTime;
            //pushes agent transaction data to agents vector
            agents.push_back({agentNum, agentTicketTime, agentReserveTime, agentWaitTime, agentWaitanyTime,
                              agentCancelTime, agentCheckPassengerTime});

            //sends transactions to transaction parser
            while (getline(fileIn, line)) {
               //parses transaction line
               fileIn >> transAction;
               //stops parsing block at 'end.'
               if (transAction[0] == 'e' && transAction[1] == 'n' && transAction[2] == 'd') {
                  break;
               }
               //handles check passenger transaction
               else if (transAction[0] == 'c' && transAction[1] == 'h') {
                  transFlight = "";
                  transSeat = "";
                  fileIn >> transCustomer;
                  fileIn >> temp;
                  fileIn >> transDeadline;
               }
               //handles other transactions
               else {
                  fileIn >> transFlight;
                  fileIn >> transSeat;
                  fileIn >> transCustomer;
                  fileIn >> temp;
                  fileIn >> transDeadline;
               }
               //gets the execution time for the corresponding action
               if (transAction == "ticket")
                  transActionTime = agentTicketTime;
               if (transAction == "reserve")
                  transActionTime = agentReserveTime;
               if (transAction == "wait")
                  transActionTime = agentWaitTime;
               if (transAction == "waitany")
                  transActionTime = agentWaitanyTime;
               if (transAction == "cancel")
                  transActionTime = agentCancelTime;
               if (transAction == "check_passenger")
                  transActionTime = agentCheckPassengerTime;
               //calculates laxity time for action
               transActionLaxity = transDeadline - transActionTime;
               //pushes struct obj to agentTransactions vector
               agentTransactions.push_back({agentNum, transDeadline, transActionTime, transActionLaxity,
                                            transAction, transFlight, transSeat, transCustomer, 0});
            }
            numOfAgents++;
         }
         else {
            //flight found
            if (!isdigit(line[0]) && isupper(line[0])) {
               // turns line into stream for breaking input into words
    				stringstream flightStream(line);
               //parses flight line
               flightStream >> flightNum;
               flightStream >> flightRows;
               flightStream >> flightSeats;
               //pushes struct obj to flights vector
               flights.push_back({flightNum, flightRows, flightSeats});
               numOfFlights++;
            }
         }
      }
   }

   fileIn.close();

   vector<string> customerNames; //contains customer names
   vector<int> customerIDs; //contains customer IDs for use in shared memory

   int id = 1; //initial ID number

   //gets an integer ID for a customer
   for (int i = 0; i < agentTransactions.size(); i++) {
      if (find(customerNames.begin(), customerNames.end(), agentTransactions[i].customerName) != customerNames.end()) {
      }
      else {
         //assigns customer ID
         customerNames.push_back(agentTransactions[i].customerName);
         customerIDs.push_back(id);
         id++;
      }
   }

   //assigns customer IDs to customers in transactions
   for (int i = 0; i < agentTransactions.size(); i++) {
      for (int j = 0; j < customerNames.size(); j++) {
         if (agentTransactions[i].customerName == customerNames[j])
            agentTransactions[i].customerID = customerIDs[j];
      }
   }

   //assigns transaction IDs to transactions
   for (int i = 0; i < agentTransactions.size(); i++) {
      agentTransactions[i].transactionID = i;
   }

   /* //vector checking and troubleshooting
   cout << "\nagents vector" << endl;
   for (int i = 0; i < agents.size(); i++) {
   cout << "agent num: " << agents[i].agentNumber << " / ticket: " << agents[i].TimeForTicket <<
           " / reserve: " << agents[i]. TimeForReserve << " / wait: " << agents[i].TimeForWait <<
           " / waitany: " << agents[i].TimeForWaitany << " / cancel: " << agents[i].TimeForCancel <<
           " / checkP: " << agents[i].TimeForCheckPassenger << endl;
   }
   cout << "\n\nflights vector" << endl;
   for (int i = 0; i < flights.size(); i++) {
      cout << "flight: " << flights[i].flightNum << " / rows: " << flights[i].numRows <<
              " / seats: " << flights[i].numSeats << endl;
   }
   cout << "\n\ntransactions vector" << endl;
   for (int i = 0; i < agentTransactions.size(); i++) {
      cout << "tID: " << agentTransactions[i].transactionID << " / agent: " << agentTransactions[i].agentNum <<
              " / action: " << agentTransactions[i].action << " / flight: " << agentTransactions[i].flightNum <<
              " / seat: " << agentTransactions[i].seat << " / cN: " << agentTransactions[i].customerName <<
              " / cID: " << agentTransactions[i].customerID << " / dL: " << agentTransactions[i].deadline << endl;
   }
   cout << "\nnum of flights: " << numOfFlights;
   cout << "\nnum of agents: " << numOfAgents << endl;
   */

   // 3. FLIGHT HANDLING //////////////////////////////////////////////////////////////////////////////////////////////////////////////

   vector<flightData> flightDatabase; //holds flights and their data, such as flight number and seats
   vector<string> seats;              //holds the seats of a flight
   int maxSeats = 0;                  //holds the max number of seats in a flight

   string seatAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //holds seat letters

   //creates flight seats
   for (int i = 0; i < flights.size(); i++) {
      string seat = "";
      //populates the seats vector with all available seats
      for (int j = 1; j <= flights[i].numRows; j++) {
         for (int k = 0; k < flights[i].numSeats; k++) {
            string seatLetter = "";
            seatLetter.push_back(seatAlphabet[k]);
            string seat = to_string(j);
            seat = seat + seatLetter;
            seats.push_back(seat);
         }
      }
      //pushes flight data into flightDatabase vector
      flightDatabase.push_back({flights[i].flightNum, seats});
      //clears elements in vectors to prepare for next flight
      seats.clear();
   }

   /*
   //troubleshooting
   for (int i = 0; i < flightDatabase.size(); i++) {
      cout << "flight: " << flightDatabase[i].flightNum << "\nseats: ";
      for (int j = 0; j < flightDatabase[i].flightSeats.size(); j++) {
         cout << flightDatabase[i].flightSeats[j] << " ";
      }
      cout << endl << endl;
   }
   */

   //builds 1d array holding flight name strings
   string flightMapArr[numOfFlights];
   for (int i = 0; i < flightDatabase.size(); i++) {
      flightMapArr[i] = flightDatabase[i].flightNum;
   }

   //gets the maximum number of seats needed to build seat status array
   for (int i = 0; i < flightDatabase.size(); i++) {
      if (maxSeats < flightDatabase[i].flightSeats.size())
      maxSeats = flightDatabase[i].flightSeats.size();
   }
   //cout << numOfFlights << " / " << maxSeats << endl;

   //builds 2d arrays - 1): seatMap vector as a map for seats, 2) seatStatusArray to get its size for use in shared memory segments
   vector<vector<string>> seatMap(numOfFlights, vector<string>(maxSeats));
   int seatStatusArray[numOfFlights][maxSeats];
   for (int i = 0; i < numOfFlights; i++) {
      for (int j = 0; j < maxSeats; j++) {
         seatMap[i][j] = "Null";
         seatStatusArray[i][j] = 0;
      }
   }

   /*populates seatMap 2d array to represent all flights and its seats like so
            flight1 flight2 flight 3
            ------------------------
     row 0: 1A      1A      1A
     row 1: 1B      1B      1B
     row 2: 1C      1C      2A
     row 3: 1D      2A      2B
     row 4: 2A      2B      (No seat)

     Note that the shared memory array flightSHMptr will look like:
            flight1 flight2 flight 3
            ------------------------
     row 0: 0       1       0
     row 1: 0       0       0
     row 2: 2       0       0
     row 3: 3       4       0
     row 4: 0       0       0

     A non-zero integer represents the customer ID who paid for the seat.
   */
   for (int i = 0; i < numOfFlights; i++) {
      for (int j = 0; j < flightDatabase[i].flightSeats.size(); j++) {
         seatMap[i][j] = flightDatabase[i].flightSeats[j];
      }
   }

    //troubleshooting
   cout << endl;
   for (int i = 0; i < numOfFlights; i++) {
      cout << "flightmap - flight " << flightMapArr[i] << " is col# " << i << endl;
   }
   cout << endl;
   /*
   for (int i = 0; i < numOfFlights; i++) {
      cout << "seatmap - flight " << i << " with seats\n";
      for (int j = 0; j < maxSeats; j++) {
         cout << seatMap[i][j] << " ";
      }
      cout << endl << endl;
   }
   cout << endl;
   */
   for (int i = 0; i < numOfFlights; i++) {
      cout << "flightDB - flight " << flightDatabase[i].flightNum << " is col# " << i << " with seats\n";
      for (int j = 0; j < maxSeats; j++) {
         cout << seatMap[i][j] << " ";
      }
      cout << endl << endl;
   }


   //prepares shared memory segment
   int flightDatabaseSHMid;
   int key = 276538;
   int *flightSHMptr;
   int size = sizeof(seatStatusArray);
   //cout << "sizeof: " << size << endl;

   flightDatabaseSHMid = shmget(key, size, 0666 | IPC_CREAT);
   //error checking
   if (flightDatabaseSHMid == -1) {
      perror("Shared memory (shmget)");
      return 1;
   }
   //attaches to the shared memory segment to get a pointer to it.
   flightSHMptr = (int *)shmat(flightDatabaseSHMid,0,0);
   //error checking
   if (flightSHMptr == (void *) -1) {
      perror("Shared memory attach (shmat)");
      return 1;
   }

   //initially fills the 2d array in shared memory with integer zeroes. A zero represents an empty seat, while a
   //non-zero represents a customerID
   fillDatabaseinSHM(flightSHMptr, numOfFlights, maxSeats);

   // 4. PIPE HANDLING ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   int numPipes = numOfAgents; //gets the total number of processes

   //cout << "\nnum processes: " << numProcesses << endl; //troubleshooting

   //creates initial file descriptor for pipe
   int fd[numPipes-1][2];

   //creates pipes for each process
   for (int i = 0; i < numPipes; i++) {
      pipe(fd[i]);
      if (pipe(fd[i])==-1) {
         cout << "Pipe Failed. Exiting program." << endl;
         return 1;
      }
   }

	// 5. PROCESS HANDLING /////////////////////////////////////////////////////////////////////////////////////////////////////////////

   vector<Process> agentProcesses; //master list that holds the agents from input file

   //populates master list of agentProcesses with input variables
   for (int i = 0; i < agents.size(); i++) {
      agentProcesses.push_back(Process(agents[i].agentNumber, agents[i].TimeForTicket, agents[i].TimeForReserve,
                                       agents[i].TimeForWait, agents[i].TimeForWaitany, agents[i].TimeForCancel,
                                       agents[i].TimeForCheckPassenger, agentTransactions));
   }
   int numProcesses = agentProcesses.size();
   //cout << "\nnum of processes: " << numProcesses << endl;

   /* //troubleshooting
   cout << "\nmaster process list:" << endl;
   cout << "number of processes: " << numProcesses << endl << endl;
   for (int i = 0; i < agentProcesses.size(); i++) {
      agentProcesses[i].print();
      cout << endl;
   }*/

   //vectors holding the compiled schedules
   vector<agentTransaction> transactionsFCFS;
   vector<agentTransaction> transactionsEDF;
   vector<agentTransaction> transactionsLLF;

   //populates initial schedule vectors from agentTransactions vector
   for (int i = 0; i < agentTransactions.size(); i++) {
      for (int j = 0; j < numProcesses; j++) {
         if (i < agentProcesses[j].transactions.size()) {
            transactionsFCFS.push_back(agentProcesses[j].transactions[i]);
            transactionsEDF.push_back(agentProcesses[j].transactions[i]);
            transactionsLLF.push_back(agentProcesses[j].transactions[i]);
         }
      }
   }

   //EDF: sorts by deadline
   for (int i = 0; i < transactionsEDF.size(); i++) {
      sort(transactionsEDF.begin(), transactionsEDF.end(), isEarlierDeadline);
   }

   //LLF: sorts by laxity
   for (int i = 0; i < transactionsLLF.size(); i++) {
      sort(transactionsLLF.begin(), transactionsLLF.end(), isEarlierLaxity);
   }

   //holds wait queue for each scheduling
   vector<struct agentTransaction> waitQueueFCFS;
   vector<struct agentTransaction> waitQueueEDF;
   vector<struct agentTransaction> waitQueueLLF;

   //handles wait transactions for FCFS by creating new transaction
   for (int i = 0; i < transactionsFCFS.size(); i++) {
      string action = transactionsFCFS[i].action;
      if (action[0] == 'w' && action.size() <= 5) {
         cout << "wait found at: " << i << endl;
         waitQueueFCFS.push_back(transactionsFCFS[i]);
      }
   }
   for (int i = 0; i < waitQueueFCFS.size(); i++) {
      string waitFlight = waitQueueFCFS[i].flightNum;
      string waitSeat = waitQueueFCFS[i].seat;
      for (int j = 0; j < transactionsFCFS.size(); j++) {
         if (transactionsFCFS[j].action == "cancel" &&
             waitFlight == transactionsFCFS[j].flightNum && waitSeat == transactionsFCFS[j].seat) {
            cout << "wait changed to ticket and found at: " << j << endl;
            struct agentTransaction newTicket = waitQueueFCFS[i];
            newTicket.action = "ticket";
            transactionsFCFS.push_back(newTicket);
         }
      }
   }

   //handles wait transactions for EDF by creating new transaction
   for (int i = 0; i < transactionsEDF.size(); i++) {
      string action = transactionsEDF[i].action;
      if (action[0] == 'w' && action.size() <= 5) {
         cout << "wait found at: " << i << endl;
         waitQueueEDF.push_back(transactionsEDF[i]);
      }
   }
   for (int i = 0; i < waitQueueEDF.size(); i++) {
      string waitFlight = waitQueueEDF[i].flightNum;
      string waitSeat = waitQueueEDF[i].seat;
      for (int j = 0; j < transactionsEDF.size(); j++) {
         if (transactionsEDF[j].action == "cancel" &&
             waitFlight == transactionsEDF[j].flightNum && waitSeat == transactionsEDF[j].seat) {
            cout << "wait changed to ticket and found at: " << j << endl;
            struct agentTransaction newTicket = waitQueueEDF[i];
            newTicket.action = "ticket";
            transactionsEDF.push_back(newTicket);
         }
      }
   }

   //handles wait transactions for LLF by creating new transaction
   for (int i = 0; i < transactionsLLF.size(); i++) {
      string action = transactionsLLF[i].action;
      if (action[0] == 'w' && action.size() <= 5) {
         cout << "wait found at: " << i << endl;
         waitQueueLLF.push_back(transactionsLLF[i]);
      }
   }
   for (int i = 0; i < waitQueueLLF.size(); i++) {
      string waitFlight = waitQueueLLF[i].flightNum;
      string waitSeat = waitQueueLLF[i].seat;
      for (int j = 0; j < transactionsLLF.size(); j++) {
         if (transactionsLLF[j].action == "cancel" &&
             waitFlight == transactionsLLF[j].flightNum && waitSeat == transactionsLLF[j].seat) {
            cout << "wait changed to ticket and found at: " << j << endl;
            struct agentTransaction newTicket = waitQueueLLF[i];
            newTicket.action = "ticket";
            transactionsLLF.push_back(newTicket);
         }
      }
   }


    //schedule vector troubleshooting
   cout << "\nFCFS schedule\n";
   for (int i = 0; i < transactionsFCFS.size(); i++) {
      cout << "tID: " << transactionsFCFS[i].transactionID << " / agent: " << transactionsFCFS[i].agentNum << " / action: " <<
              transactionsFCFS[i].action << " / flight: " << transactionsFCFS[i].flightNum << " / seat: " <<
              transactionsFCFS[i].seat << " / cN: " << transactionsFCFS[i].customerName << " / cID: " <<
              transactionsFCFS[i].customerID << " / et: " << transactionsFCFS[i].actionTime << " / dL: " <<
              transactionsFCFS[i].deadline << " / lt: " << transactionsFCFS[i].laxityTime << endl;
   }
   cout << "\nEDF schedule\n";
   for (int i = 0; i < transactionsEDF.size(); i++) {
      cout << "tID: " << transactionsEDF[i].transactionID << " / agent: " << transactionsEDF[i].agentNum << " / action: " <<
              transactionsEDF[i].action << " / flight: " << transactionsEDF[i].flightNum << " / seat: " <<
              transactionsEDF[i].seat << " / cN: " << transactionsEDF[i].customerName << " / cID: " <<
              transactionsEDF[i].customerID << " / et: " << transactionsEDF[i].actionTime << " / dL: " <<
              transactionsEDF[i].deadline << " / lt: " << transactionsEDF[i].laxityTime << endl;
   }
   cout << "\nLLS schedule\n";
   for (int i = 0; i < transactionsLLF.size(); i++) {
      cout << "tID: " << transactionsLLF[i].transactionID << " / agent: " << transactionsLLF[i].agentNum << " / action: " <<
              transactionsLLF[i].action << " / flight: " << transactionsLLF[i].flightNum << " / seat: " <<
              transactionsLLF[i].seat << " / cN: " << transactionsLLF[i].customerName << " / cID: " <<
              transactionsLLF[i].customerID << " / et: " << transactionsLLF[i].actionTime << " / dL: " <<
              transactionsLLF[i].deadline << " / lt: " << transactionsLLF[i].laxityTime << endl;
   }


   vector<int> semKeys; //holds keys for processes
   //generates keys for each process
   for (int i = 0; i < numProcesses+1; i++) {
      key++;
      semKeys.push_back(key);
      //cout << "key: " << semKeys[i] << endl;
   }
   //creates a shared memory space for the parent to send transaction ID to its child processes
   int shmidPC;
   int keyPC = semKeys[0];
   struct PCSHM *PCSHMptr;

   shmidPC = shmget(keyPC, sizeof(struct PCSHM), 0666 | IPC_CREAT);

   PCSHMptr = (struct PCSHM *) shmat(shmidPC, 0 , 0);

   //creates a parent semaphore to handle the shmidPC segment
   int parentSem;
   parentSem = semget(keyPC, 1, 0666 | IPC_CREAT);
   //initiates parent semaphore with value = 1
   semctl(parentSem, 0, SETVAL, 1);

   int semValue = semctl(parentSem, 0, GETVAL);
   cout << "\ninit parent with semID " << parentSem << " has init Semctl val: " << semValue << endl;


   vector<int> semIDs; //holds child semaphore identifiers
   //creates child semaphores to handle the shmidPC segment
   for (int i = 1; i < numProcesses+1; i++) {
      int childSem;
      int keyC = semKeys[i];
      childSem = semget(keyC, 1, 0666 | IPC_CREAT);
      //initiates child (agent) semaphores with value = 0
      semctl(childSem, 0, SETVAL, 0);
      semValue = semctl(childSem, 0, GETVAL);
      cout << "agent " << i << " with semID " << childSem << " has init Semctl val: " << semValue << endl;
      semIDs.push_back(childSem);
   }

   /* //troubleshooting
   for (int i = 0; i < semIDs.size(); i++) {
      cout << "Agent sem id: " << semIDs[i] << endl;
   }*/

   //the following does FCFS scheduling////////////////////////////////////////////////////////////////////////////////////////////////
   cout << "\n=========================" << endl;
   cout << "     FCFS Scheduling"      << endl;
   cout << "=========================" << endl;
   for (int i = 0; i < numProcesses; i++) {
      //creates a number of child processes via fork
      pid_t id = fork();

      int pipeID;
      int temp;

      if (id < 0) {
         //error checking
         cout << "ERROR: Process fork failed. Exiting program." << endl;
         return 1;
      }
      //this is the parent process that schedules the transactions
      else if (id > 0) {
         //writes transaction to shared memory
         for (int j = 0; j < transactionsFCFS.size(); j++) {
            //makes the parent semaphore wait
            wait(parentSem);

            /* //troubleshooting
            semValue = semctl(parentSem, 0, GETVAL);
            cout << "\nPARENT start - parent (semID " << parentSem << ", trans# " << j << ", value: " << semValue << ")" << endl;
            */

            //gets agent number of transaction to send it to the right agent
            int transAgentNum = transactionsFCFS[j].agentNum;
            //gets transaction ID to send to agent
            int transAgentTransID = transactionsFCFS[j].transactionID;

            pipeID = transAgentNum-1;

            //sends write value to write end of pipe
            write(fd[pipeID][1], &transAgentTransID, sizeof(int));

            //gets corresponding semaphore ID
            int agentSemIDP = semIDs[transAgentNum-1];
            //signals the corresponding agent semaphore
            signal(agentSemIDP);

            /* //troubleshooting
            semValue = semctl(agentSemIDP, 0, GETVAL);
            cout << "PARENT end - signal agent " << transAgentNum << " (semID " << agentSemIDP << ", trans# " << j <<
                    ", value: " << semValue << ")" << endl << endl;
            */
         }
      }
      //this is a child agent process that does the transaction
      else {
         int thisAgentNum = i+1;

         for (int j = 0; j < agentProcesses[i].transactions.size(); j++) {
            //gets the semaphore ID controlling this process
            int agentSemIDC = semIDs[i];

            //makes the agent semaphore wait
            wait(agentSemIDC);

            int thisAgentNum = i+1;

            /* //troubleshooting
            semValue = semctl(agentSemIDC, 0, GETVAL);
            cout << "CHILD start - agent " << thisAgentNum << " (semID " << agentSemIDC << ", value: " << semValue << ")" << endl;

            //semValue = semctl(parentSem, 0, GETVAL);
            //cout << "CHILD start - parent with semID " << parentSem << " / Semctl val: " << semValue << endl;
            */

            //gets read value from read end of pipe
            read(fd[i][0], &temp, sizeof(int));

            int toDoID = temp;

            //stores the rest of the transaction data
            struct agentTransaction toDoData;

            //fetches corresponding transaction data
            for (int k = 0; k < agentProcesses[i].transactions.size(); k++) {
               if (toDoID == agentProcesses[i].transactions[k].transactionID) {
                  toDoData.agentNum = agentProcesses[i].transactions[k].agentNum;
                  toDoData.deadline = agentProcesses[i].transactions[k].deadline;
                  toDoData.actionTime = agentProcesses[i].transactions[k].actionTime;
                  toDoData.laxityTime = agentProcesses[i].transactions[k].laxityTime;
                  toDoData.action = agentProcesses[i].transactions[k].action;
                  toDoData.flightNum = agentProcesses[i].transactions[k].flightNum;
                  toDoData.seat = agentProcesses[i].transactions[k].seat;
                  toDoData.customerName = agentProcesses[i].transactions[k].customerName;
                  toDoData.customerID = agentProcesses[i].transactions[k].customerID;
                  toDoData.transactionID = agentProcesses[i].transactions[k].transactionID;
               }
            }

            /* //troubleshooting
            cout << "CHILD mid - agent " << thisAgentNum << " is doing - ";
            cout << "transID: " << toDoData.transactionID << " / agent: " << toDoData.agentNum <<
                     " / action: " << toDoData.action << " / flight: " << toDoData.flightNum <<
                     " / seat: " << toDoData.seat << " / cN: " << toDoData.customerName <<
                     " / cID: " << toDoData.customerID << " / et: " << toDoData.actionTime <<
                     " / dL: " << toDoData.deadline << " / lt: " << toDoData.laxityTime << endl;
            */

            //if transaction is ticket
            if (toDoData.action[0] == 't') {
               int isSuccess = 0;
               //calls function to check if ticketing transaction succeeds
               isSuccess = isSeatAvailableSHM(flightSHMptr, flightMapArr, seatMap, numOfFlights, maxSeats, toDoData);
               //seat was successfully bought
               if (isSuccess == 1) {
                  // pointer variable to get global timer value
                  int *currGlobalTime;
                  currGlobalTime = &globalTimer;
                  int currTime = toDoData.actionTime + *currGlobalTime;
                  //sets global timer value to add on this transaction time
                  *currGlobalTime = currTime;

                  //prints out if deadline met
                  if (currTime <= toDoData.deadline) {
                     cout << toDoData.customerName << " tickets " << toDoData.flightNum << " " <<
                             toDoData.seat << " successfully at time " << currTime << ", deadline met." << endl;
                  }
                  //prints out if deadline missed
                  else {
                     cout << toDoData.customerName << " tickets " << toDoData.flightNum << " " <<
                             toDoData.seat << " at time " << currTime << ", deadline missed." << endl;
                  }
               }
               //seat was not bought as it was already occupied
               else if (isSuccess == 0) {
                  cout << toDoData.customerName << " fails to buy a ticket for " << toDoData.flightNum << " " <<
                          toDoData.seat << " because it is occupied." << endl;
               }
               //error returned
               else {
                  cout << "ERROR: requested flight / seat does not exist for transaction : " <<
                          toDoData.customerName << " tickets " << toDoData.flightNum << " " << toDoData.seat << endl;
               }
            }

            //if transaction is reserve
            if (toDoData.action[0] == 'r') {
               int isSuccess = 0;
               //calls function to check if ticketing transaction succeeds
               isSuccess = isSeatAvailableSHM(flightSHMptr, flightMapArr, seatMap, numOfFlights, maxSeats, toDoData);
               //seat was successfully bought
               if (isSuccess == 1) {
                  // pointer variable to get global timer value
                  int *currGlobalTime;
                  currGlobalTime = &globalTimer;
                  int currTime = toDoData.actionTime + *currGlobalTime;
                  //sets global timer value to add on this transaction time
                  *currGlobalTime = currTime;

                  //prints out if deadline met
                  if (currTime <= toDoData.deadline) {
                     cout << toDoData.customerName << " reserves " << toDoData.flightNum << " " <<
                             toDoData.seat << " successfully at time " << currTime << ", deadline met." << endl;
                  }
                  //prints out if deadline missed
                  else {
                     cout << toDoData.customerName << " reserves " << toDoData.flightNum << " " <<
                             toDoData.seat << " at time " << currTime << ", deadline missed." << endl;
                  }
               }
               //seat was not bought as it was already occupied
               else if (isSuccess == 0) {
                  cout << toDoData.customerName << " fails to reserve " << toDoData.flightNum << " " <<
                          toDoData.seat << " because it is occupied." << endl;
               }
               //error returned
               else {
                  cout << "ERROR: requested flight / seat does not exist for transaction : " <<
                          toDoData.customerName << " reserves " << toDoData.flightNum << " " << toDoData.seat << endl;
               }
            }

            //if transaction is wait
            if (toDoData.action[0] == 'w' && toDoData.action.size() <= 5) {
               // pointer variable to get global timer value
               int *currGlobalTime;
               currGlobalTime = &globalTimer;
               int currTime = toDoData.actionTime + *currGlobalTime;
               //sets global timer value to add on this transaction time
               *currGlobalTime = currTime;

               //prints out if deadline met
               if (currTime <= toDoData.deadline) {
                  cout << toDoData.customerName << " waits on " << toDoData.flightNum << " " <<
                          toDoData.seat << " successfully at time " << currTime << ", deadline met." << endl;
               }
               //prints out if deadline missed
               else {
                  cout << toDoData.customerName << " waitany on " << toDoData.flightNum << " " <<
                          toDoData.seat << " at time " << currTime << ", deadline missed." << endl;
               }
            }

            //if transaction is waitany
            if (toDoData.action[0] == 'w' && toDoData.action[5] == 'a') {
               // pointer variable to get global timer value
               int *currGlobalTime;
               currGlobalTime = &globalTimer;
               int currTime = toDoData.actionTime + *currGlobalTime;
               //sets global timer value to add on this transaction time
               *currGlobalTime = currTime;

               //prints out if deadline met
               if (currTime <= toDoData.deadline) {
                  cout << toDoData.customerName << " waitany on " << toDoData.flightNum << " " <<
                          toDoData.seat << " at time " << currTime << ", deadline met." << endl;
               }
               //prints out if deadline missed
               else {
                  cout << toDoData.customerName << " waitany on " << toDoData.flightNum << " " <<
                          toDoData.seat << " at time " << currTime << ", deadline missed." << endl;
               }
            }

            //if transaction is cancel
            if (toDoData.action[0] == 'c' && toDoData.action[1] == 'a') {
               int isSuccess = 0;
               //calls function to check if ticketing transaction succeeds
               isSuccess = isSeatAvailableSHM(flightSHMptr, flightMapArr, seatMap, numOfFlights, maxSeats, toDoData);
               //seat was successfully canceled
               if (isSuccess == 1) {
                  // pointer variable to get global timer value
                  int *currGlobalTime;
                  currGlobalTime = &globalTimer;
                  int currTime = toDoData.actionTime + *currGlobalTime;
                  //sets global timer value to add on this transaction time
                  *currGlobalTime = currTime;

                  //prints out if deadline met
                  if (currTime <= toDoData.deadline) {
                     cout << toDoData.customerName << " cancels " << toDoData.flightNum << " " <<
                             toDoData.seat << " successfully at time " << currTime << ", deadline met." << endl;
                  }
                  //prints out if deadline missed
                  else {
                     cout << toDoData.customerName << " cancels " << toDoData.flightNum << " " <<
                             toDoData.seat << " at time " << currTime << ", deadline missed." << endl;
                  }
               }
               //seat was not bought as it was already occupied
               else if (isSuccess == 0) {
                  cout << toDoData.customerName << " fails to cancel " << toDoData.flightNum << " " <<
                          toDoData.seat << " because it is not occupied by " << toDoData.customerName << "." << endl;
               }
               //error returned
               else {
                  cout << "ERROR: requested flight / seat does not exist for transaction : " <<
                          toDoData.customerName << " cancels " << toDoData.flightNum << " " << toDoData.seat << endl;
               }
            }

            //if transaction is check passenger
            if (toDoData.action[0] == 'c' && toDoData.action[1] == 'h') {
               vector<struct seatData> reservations;
               //calls function to check passenger's reservations
               checkPassengerSHM(flightSHMptr, reservations, flightMapArr, seatMap, numOfFlights, maxSeats, toDoData);
               // pointer variable to get global timer value
               int *currGlobalTime;
               currGlobalTime = &globalTimer;
               int currTime = toDoData.actionTime + *currGlobalTime;
               //sets global timer value to add on this transaction time
               *currGlobalTime = currTime;
               int numOfReservations = reservations.size();

               //prints out if deadline met and customer has reservations
               if (currTime <= toDoData.deadline && numOfReservations > 0) {
                  cout << toDoData.customerName << " has " << numOfReservations << " reservation(s) at time " << currTime <<
                          ", deadline met." << endl;
                  //prints reservations if any
                  for (int i = 0; i < numOfReservations; i++) {
                     cout << "--> " << toDoData.customerName << " has a reservation for " << reservations[i].flightNum << " " <<
                             reservations[i].seat << endl;
                  }
               }
               //prints out if deadline met and customer has no reservations
               if (currTime <= toDoData.deadline && numOfReservations == 0) {
                  cout << toDoData.customerName << " has no reservations at time " << currTime << ", deadline met." << endl;
               }
               //prints out if deadline missed
               if (!(currTime <= toDoData.deadline) && numOfReservations > 0) {
                  cout << toDoData.customerName << " has " << numOfReservations << " reservation(s) at time " << currTime <<
                          ", deadline missed." << endl;
                  //prints reservations if any
                  for (int i = 0; i < numOfReservations; i++) {
                     cout << "--> " << toDoData.customerName << " has a reservation for " << reservations[i].flightNum << " " <<
                             reservations[i].seat << endl;
                  }
               }
               //prints out if deadline missed and customer has no reservations
               if (!(currTime <= toDoData.deadline) && numOfReservations == 0) {
                  cout << toDoData.customerName << " has no reservations at time " << currTime << ", deadline missed." << endl;
               }
            }

            //signals the parent semaphore
            signal(parentSem);

            /*
            semValue = semctl(parentSem, 0, GETVAL);
            cout << "\nCHILD end - signaled the parent (semID " << parentSem << ", value: " << semValue << ")" << endl;


            semValue = semctl(agentSemIDC, 0, GETVAL);
            cout << "CHILD end - agent " << thisAgentNum << " with semID " << agentSemIDC << " and Semctl val: " << semValue <<
                    " completed task " << agentProcesses[i].transactions[j].action << " for flight " <<
                    agentProcesses[i].transactions[j].flightNum << endl << endl;
            */
         }
         cout << "Agent " << thisAgentNum << " exits." << endl;
         exit(0); //stops child processes from creating more child processes
      }
   }

   //destroys used semaphores
   semctl(parentSem, 0, IPC_RMID, 0);
   for (int i = 0; i < numProcesses; i++) {
      int idC = semIDs[i];
      semctl(idC, 0, IPC_RMID, 0);
   }

	return 0;
}
