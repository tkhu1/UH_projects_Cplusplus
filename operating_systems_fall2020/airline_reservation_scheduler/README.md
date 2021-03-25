Implemented several programs with Unix/Linux semaphores and shared memory to handle airline reservations taken by different agents connected to the “Fall-OS” airline’s central computer. Each program handles a different scheduling algorithm.

This program is divided into five parts:
0. DATA STRUCTURES
1. HELPER FUNCTIONS
2. MAIN - INPUT HANDLING
3. MAIN - PIPE HANDLING
4. MAIN - PROCESS HANDLING

0. DATA STRUCTURES
This section contains three initial structs for holding parsed data (0.a, 0.b, 0.c).
Struct 0.d holds the data of a transaction, including new variable such as customerID and
transactionID to assign numerical identifiers to the transaction and the passenger.
This program handles process scheduling by having a forked parent process with a master schedule 
use semaphores to control which agent child processes complete their corresponding transactions. 
Struct 0.e holds the data for a single reserved seat that will be brought frm the flight database into
an agent process for the check passenger transaction.
Struct 0.f is a wrapper struct for the parent scheduling process to use when passing the transaction
identifier via shared memory to a child agent process. 
Class 0.g represents an agent process and 
contains all the data for an agent such as his or hers number, execution delay times and corresponding
transactions.

1. HELPER FUNCTIONS
This section first contains two comparator functions to handle schedule sorting, either by deadline 
for EDF or laxity for LLF. 
The fillDatabaseinSHM function fills a 2D array with int 0s. This 2D array is used in shared memory and 
represents the current status of seats for every flight, i.e., the flight database. Though the flight 
database is initially filled with 0s that represent unbought seats, the isSeatAvailableSHM function takes
transactions and changes the 0s to the customer ID of a passenger if he or she tickets/reserves a seat.

A non-zero integer represents the customer ID who paid for the seat.

To make sure the right flight / seat is selected for each transaction, a 2D string array of the flights with 
their named seats is created as a map for the flight database.

Other helpers include wait and signal functions for semaphores and two more functions to facilitate the parent 
process sending transactions to child agent processes via shared memory.

2. MAIN - INPUT HANDLING
This section opens the input file and divides each line into individual data to be stored in vectors. The program
also creates and assigns customer IDs and transactions for easy use.

3. MAIN - FLIGHT HANDLING
This section creates the dynamic flight database, populates each flight with the correct seating arrangement, and
then the arrays. A shared memory segment for the flight database is also initialized and attached to a pointer here.

4. MAIN - PROCESS HANDLING
This section contains the main logic of the program. First a master list that holds all of the 
agent process classes is created (e.g., agents 1,2,3,...). 
Then three schedules are made that order the tranactions by either FCFS, EDF, or LLF scheduling schemes.
Next, n+1 semaphores are created, one for each agent n, plus 1 for the parent process. The parent process handles
the scheduling by signaling to each agent when to do a transaction. After an agent process does the transaction,
it signals the parent process to continue on to the next transaction until all are completed. 

To use the program, the following command lines are used:

command to compile:                  

g++ -std=c++11 hw1.cpp

command to see output in terminal:   

./a.out "input_file_name.txt"