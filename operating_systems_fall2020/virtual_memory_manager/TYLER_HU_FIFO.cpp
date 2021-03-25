#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// FALL20 COSC3360 - HOMEWORK 3                                                      //
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
// PROFESSOR: Albert Cheng - University of Houston                                   //
///////////////////////////////////////////////////////////////////////////////////////

/*
To use the program, the following command lines are used:

command to compile:

g++ -std=c++11 TYLER_HU_ALGORITHM.cpp

command to see output in terminal:

./a.out "input_file_name.txt"


DISCLAIMER: Small portions of code have been inspired by examples from the internet,
            such as from Geeks4Geeks or Stack Overflow
*/

// 0. DATA STRUCTURES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 0.a Struct - Address //
/*This struct represents a logical address and contains its segment, page, and displacement.
*/
struct Address {
	int segment;
	int page;
	int displacement;
};
// 0.b Struct - Frame //
/*This struct represents a physical frame and contains its allocation status and process, segment, page, and frame IDs.
*/
struct Frame {
	bool isAllocated;
	int processID;
	int pageID;
	int segmentID;
	int frameID;
	Frame(int id) {
		frameID = id;
	}
};
// 0.c Struct - Page //
/*This struct represents a page and contains its allocation status, page, and frame IDs.
*/
struct Page {
	bool isAllocated;
	int frameID;
	int pageID;
	Page(int id) {
		pageID = id;
		frameID = 0;
		isAllocated = false;
	}
};
// 0.d Struct - Page Table //
/*This struct represents a page table and contains a vector of pages.
*/
struct PageTable {
	vector<Page> pages;
};
// 0.e Struct - Segment //
/*This struct represents a segment and contains its segment ID and page table.
*/
struct Segment {
	int segmentID;
	PageTable pageTable;
	Segment(int id) {
		segmentID = id;
	}
};
// 0.f Struct - Segment Table //
/*This struct represents a segment table and contains a vector of segments.
*/
struct SegmentTable {
	vector<Segment> segments;
};
// 0.g Struct - Address Space //
/*This struct represents an address space of a process and contains a vector of segment tables and pages used.
*/
struct AddressSpace {
	vector<SegmentTable> segmentTables;		//contains all the segment tables in this address space
	vector<Page> LastPagesUsed;
};
// 0.h Struct - Process //
/*This struct represents a process and contains its ID, total page frames on disk, and address space.
*/
struct Process {
	int processID;
	int totalPageFramesOnDisk;
	AddressSpace addrSpace;		//address space that contains all of the addresses
};
// 0.i Struct - Instruction //
/*This struct represents an instruction and contains its ID, process ID, and process addr.
*/
struct Instruction {
	int instructionID;
	int instructionPID;
	string instructionAddr;
};

// 1. MAIN FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//converts decimal to the number of bits needed to read a binary address string. Input parameter is a decimal length
int getBitLength(int length)
{
   int result = 0;
   while (length > 1) {
      length /= 2;
      result++;
   }
   return result;
}

//converts binary string to decimal integer
int binaryToDecimal(string input)
{
   int result = stoull(input, 0, 2);
   return result;
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

// MAIN PROGRAM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
   //initial variable declarations
   vector<Frame> framesInMainMemory;		   //frames currently in main memory
   vector<Frame> framesInDiskTable;			   //frames stored in the disk table
   vector<Process> processes;                //processes
   vector<Instruction> instructions;	      //input instructions
   vector<pair<int,int>> totalPageFaults;    //collates total number of page faults for each process

   // 2. INPUT HANDLING ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	string fileName = argv[1]; //stores input file name

	//working vars
	string line;
	string temp;
	int inputPID;
	int inputPFonDisk;
	int inputInstructionID = 0;

	//input file vars
   int totalPageFramesInMemory;	//total number of page frames
   int segmentLength;				//maximum segment length (in number of pages)
   int pageSize;						//page size (in number of bytes)
   int pageFramePerProcess;	   //number of page frames per process for page replacement algorithms
   int lookAheadwindow = 0;		//lookahead window size for OPT-X and LRU-X, 0 for others (which do not use this value)
   int poolMin;                //min free pool size
   int poolMax;                //max free pool size
   int totalProcesses;				//total number of processes

	ifstream fileIn;              //input stream here
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
      //parses input file line & gets total page frames
		getline(fileIn, line);
		totalPageFramesInMemory = stoi(line); //converts string to int
		//parses input file line & gets maximum segment length
		getline(fileIn, line);
		segmentLength = stoi(line);
      //parses input file line & gets maximum page size
		getline(fileIn, line);
		pageSize = stoi(line);
      //parses input file line & gets page frames per process
		getline(fileIn, line);
		pageFramePerProcess = stoi(line);
      //parses input file line & gets lookahead window
		getline(fileIn, line);
		lookAheadwindow = stoi(line);
      //parses input file line & gets min free pool size
		getline(fileIn, line);
		poolMin = stoi(line);
      //parses input file line & gets max free pool size
		getline(fileIn, line);
		poolMax = stoi(line);
      //parses input file line & gets total number of processes
		getline(fileIn, line);
		totalProcesses = stoi(line);

      //parses input file lines for processes and pushes to processes vector
		for (int i = 0; i < totalProcesses; i++) {
         Process inputProcess;

         getline(fileIn, line);
         istringstream parser1(line); //converts string line into stream

         parser1 >> temp;
         inputPID = stoi(temp); //gets process ID
         parser1 >> temp;
         inputPFonDisk = stoi(temp); //gets page frames on disk
         inputProcess.processID = inputPID;
         inputProcess.totalPageFramesOnDisk = inputPFonDisk;

         processes.push_back(inputProcess);
		}

		//parses input file lines for instructions and pushes to instructions vector
		while (getline(fileIn, line)) {
         Instruction inputInstruction;

		   istringstream parser2(line); //converts string line into stream

         parser2 >> temp;
         inputPID = stoi(temp); //gets process ID
         parser2 >> temp;

         if (temp[0] != '-') { //if address not equal to -1
            temp.pop_back(); //removes B in address
            inputInstruction.instructionID = inputInstructionID; //assigns instruction ID to instruction
            inputInstruction.instructionPID = inputPID;
            inputInstruction.instructionAddr = temp;

            instructions.push_back(inputInstruction);

            inputInstructionID++;
         }
		}
	}

   fileIn.close();

   //exits program if no instructions found in input file
   if (instructions.size() < 1) {
      cout << "\nERROR: No instructions found in input file. Exiting program...";
      return 1;
   }

   //gets the bit lengths of the segment, page, and displacement parts of the address instructions
   int segmentBitLength;
   segmentBitLength = getBitLength(segmentLength);
   int pageBitLength;
   pageBitLength = getBitLength(pageSize);
   int displacementBitLength;
   displacementBitLength = instructions[0].instructionAddr.size() - pageBitLength;

   //troubleshooting
   cout << " total number of page frames: " << totalPageFramesInMemory << endl;
   cout << " maximum segment length: " << segmentLength << endl;
   cout << " page size (in number of bytes): " << pageSize << endl;
   cout << " number of page frames per process: " << pageFramePerProcess << endl;
   cout << " segment bit length: " << segmentBitLength << endl;
   cout << " page bit length: " << pageBitLength << endl;
   cout << " displacement bit length: " << displacementBitLength << endl;
   cout << " lookahead window size: " << lookAheadwindow << endl;
   cout << " min free pool size: " << poolMin << endl;
   cout << " max free pool size: " << poolMax << endl;
   cout << " total number of processes: " << totalProcesses << endl;
   cout << "\n processes vector:" << endl;
   for (int i = 0; i < processes.size(); i++) {
      cout << "\tprocessID: " << processes[i].processID << " / page frames in disk: " << processes[i].totalPageFramesOnDisk << endl;
   }
   cout << "\n instructions vector:" << endl;
   for (int i = 0; i < instructions.size(); i++) {
      cout << "\tinstructionID: " << instructions[i].instructionID << " / processID: " << instructions[i].instructionPID <<
              " / addr: " << instructions[i].instructionAddr << endl;
   }

   // 3. MEMORY HANDLING //////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //builds the main memory with an input number of frames
   for (int i = 0; i < totalPageFramesInMemory; i++) {
		framesInMainMemory.push_back(*(new Frame(i)));
	}

   //builds the segment and page tables for each process
	for (int i = 0; i < totalProcesses; i++) {
      //pointer to a process
	   Process *ptrForProcess;
      ptrForProcess = &processes[i];
		//pushes a new segment table into the process if it does not already exist
      if (ptrForProcess->addrSpace.segmentTables.size() == 0) {
         ptrForProcess->addrSpace.segmentTables.push_back(*(new SegmentTable()));
      }

      //gets the maximum process address space size in pages (process max frames on disk * segment length)
      int maxSegmentAndPageSize = ptrForProcess->totalPageFramesOnDisk * segmentLength;

      //pushes new segments and pages into the respective tables in a process
      for (int j = 0; j < maxSegmentAndPageSize; j++) {
         //gets page and segment number
         int page = j % segmentLength;
         int segment = j / segmentLength;

         //pushes a new segment into the segment table if it does not already exist
         if (segment >= ptrForProcess->addrSpace.segmentTables[0].segments.size()) {
            ptrForProcess->addrSpace.segmentTables[0].segments.push_back(*(new Segment(segment)));
         }
         //pushes a new page into the page table if it does not already exist
         if (page >= ptrForProcess->addrSpace.segmentTables[0].segments[segment].pageTable.pages.size()) {
            ptrForProcess->addrSpace.segmentTables[0].segments[segment].pageTable.pages.push_back(*(new Page(page)));
         }

         //troubleshooting
         //cout << "process: " << ptrForProcess->processID << " / building page: " << page << " / with segment: " << segment << endl;

         //sets the frame information
         Frame *ptrForFrame = new Frame(j + framesInDiskTable.size());
         ptrForFrame->isAllocated = true;
         ptrForFrame->pageID = page;
         ptrForFrame->segmentID = segment;
         ptrForFrame->processID = ptrForProcess->processID;
         //pushes frame into the disk table
         framesInDiskTable.push_back(*ptrForFrame);
      }
	}

   // 4. PIPE HANDLING ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /*
     creates pipes for the page fault handler -> disk driver
                           disk driver -> page fault handler
   */
   int numPipes = 6;

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
   //initializes total page fault vector
   for (int i = 0; i < totalProcesses; i++) {
      totalPageFaults.push_back(make_pair(processes[i].processID, 0));
   }

   int keyPH = 276538;  //key to create semaphore for page fault handler process
   int keyDD = 276539;  //key to create semaphore for disk driver process
   int keyPR = 276540;  //key to create semaphore for page replacement process

   //creates a semaphore for the page handler
   int semPH;
   semPH = semget(keyPH, 1, 0666 | IPC_CREAT);
   //initiates page handler semaphore with value = 1
   semctl(semPH, 0, SETVAL, 1);

   //creates a semaphore for the disk driver
   int semDD;
   semDD = semget(keyDD, 1, 0666 | IPC_CREAT);
   //initiates disk driver semaphore with value = 0
   semctl(semDD, 0, SETVAL, 0);

   //creates a semaphore for the page replacer
   int semPR;
   semPR = semget(keyPR, 1, 0666 | IPC_CREAT);
   //initiates page replacer semaphore with value = 0
   semctl(semPR, 0, SETVAL, 0);

   /* //troubleshooting
   int semValuePH = semctl(semPH, 0, GETVAL);
   cout << "\ninit semPH with semID " << semPH << " has init Semctl val: " << semValuePH << endl;
   int semValueDD = semctl(semDD, 0, GETVAL);
   cout << "\ninit semDD with semID " << semDD << " has init Semctl val: " << semValueDD << endl;
   int semValuePR = semctl(semPR, 0, GETVAL);
   cout << "\ninit semPR with semID " << semPR << " has init Semctl val: " << semValuePR << endl;
   */

   //keeps track of the pages in chronological order from oldest begin to newest end
	vector<Page*> LRU_Array;

   /*Creates 3 child processes: page fault handler, disk driver, and page replacement algorithm process.
     page fault handler has i value = 0;
     disk driver has i value = 1;
     page replacement algorithm has i value = 2;
   */
   for (int i = 0; i < 3; i++) {
      //creates a number of child processes via fork
      pid_t id = fork();

      int temp;
      int isRunning;

      if (id < 0) {
         //error checkings
         cout << "ERROR: Process fork failed. Exiting program." << endl;
         return 1;
      }
      //this is the parent process that is not used in this program
      else if (id > 0) {
      }
      //this is a child process
      else {
            //page fault handler process
            if (i == 0) {
               //makes the page handler wait. Note that the page handler process runs first due to initial semaphore value = 1.
               //wait(semPH);
               //loops through and completes each instruction
               for (int j = 0; j < instructions.size(); j++) {
                  wait(semPH);
                  //copies struct from instructions
                  struct Instruction ins;
                  ins = instructions[j];
                  int insPID = ins.instructionPID;
                  string insAddr = ins.instructionAddr;

                  for (int k = 0; k < totalProcesses; k++) {
                     //compares process IDs
                     string processIDtoString = to_string(processes[k].processID);
                     string instructionProcessIDtoString = to_string(insPID);
                     if (instructionProcessIDtoString.find(processIDtoString) != string::npos) {
                        //parses address to get segment bits
                        string tempSID = "";
                        for (int l = 0; l < segmentBitLength; l++) {
                           tempSID = tempSID + insAddr[l];
                        }
                        //converts binary string to decimal integer
                        int segmentID;
                        segmentID = binaryToDecimal(tempSID);

                        //parses address to get page bits
                        string tempPID = "";
                        for (int l = segmentBitLength; l < pageBitLength; l++) {
                           tempPID = tempPID + insAddr[l];
                        }
                        //converts binary string to decimal integer
                        int pageID;
                        pageID = binaryToDecimal(tempPID);

                        //parses address to get displacement bits
                        string tempDisplace = "";
                        for (int l = pageBitLength; l < insAddr.size(); l++) {
                           tempDisplace = tempDisplace + insAddr[l];
                        }
                        //converts binary string to decimal integer
                        int displacement;
                        displacement = binaryToDecimal(tempDisplace);

                        //attempts to page access
                        cout << "\nDoing page access with Process " << ins.instructionPID << " / Segment " << segmentID <<
                                " / Page " << pageID << " / Segment Length " << processes[k].addrSpace.segmentTables[0].segments.size() <<
                                " / Displacement: " << displacement << endl;

                        //gets pointer to the current page in the process
                        Page *ptrForPage = &processes[k].addrSpace.segmentTables[0].segments[segmentID].pageTable.pages[pageID];

                        bool PageFault = false;
                        //if the accessing page is allocated, then page fault
                        if (ptrForPage->isAllocated == false) {
                           PageFault = true;
                           //increments page fault counter in total page faults vector
                           for (int l = 0; l < totalPageFaults.size(); l++) {
                              if (ins.instructionPID == totalPageFaults[l].first) {
                                 int temp = totalPageFaults[l].second;
                                 temp++;
                                 totalPageFaults[l].second = temp;
                              }
                           }
                           cout << "\tPage fault" << endl;
                        }
                        //if the page accessed matches, then replace it
                        else if (!(framesInMainMemory[ptrForPage->frameID].processID == processes[k].processID &&
                                   framesInMainMemory[ptrForPage->frameID].pageID == pageID &&
                                   framesInMainMemory[ptrForPage->frameID].segmentID == segmentID)) {
                           PageFault = true;
                           //increments page fault counter in total page faults vector
                           for (int l = 0; l < totalPageFaults.size(); l++) {
                              if (ins.instructionPID == totalPageFaults[l].first) {
                                 int temp = totalPageFaults[l].second;
                                 temp++;
                                 totalPageFaults[l].second = temp;
                              }
                           }
                           cout << "\tPage fault (replacement)" << endl;
                        }
                        //init pointer to a frame
                        Frame *ptrForFrame = NULL;

                        if (PageFault) {
                           if (processes[k].addrSpace.LastPagesUsed.size() < pageFramePerProcess) {
                              //look for empty space in the main memory
                              for (int m = 0; m < framesInMainMemory.size(); m++) {
                                 if (framesInMainMemory[m].isAllocated == false) {
                                    //gets empty frame
                                    ptrForFrame = &framesInMainMemory[m];
                                    cout << "\tFound free frame in main memory." << endl;
                                    break;
                                 }
                              }
                              //error checking
                              if (ptrForFrame == NULL) {
                                 cout << "\tERROR: Frame == NULL" << endl;
                                 break;
                              }
                           }
                           //replaces page
                           else {
                              //writes to page replacer pipe
                              int pipeProcessValuePR = k;
                              //sends process value to disk driver write end of pipe
                              write(fd[5][1], &pipeProcessValuePR, sizeof(int));
                              //calls page replacement process
                              signal(semPR);
                           }
                           //pushes page
                           processes[k].addrSpace.LastPagesUsed.push_back(*ptrForPage);

                           //writes to disk driver pipe
                           int pipeProcessValue = k;
                           int pipeSegID = segmentID;
                           int pipePageID = pageID;
                           //sends process value to disk driver write end of pipe
                           write(fd[0][1], &pipeProcessValue, sizeof(int));
                           //sends segment ID to disk driver write end of pipe
                           write(fd[1][1], &pipeSegID, sizeof(int));
                           //sends page ID to disk driver write end of pipe
                           write(fd[2][1], &pipePageID, sizeof(int));
                           //tells the disk driver process to keep running
                           isRunning = 1;
                           //sends write value to disk driver write end of pipe
                           write(fd[3][1], &isRunning, sizeof(int));
                           //calls disk driver process
                           signal(semDD);

                           //k--;
                           //continue;
                        }
                        else {
                           cout << "\tPage found." << endl;
                        }
                        break;
                     }
                  }
               }
               isRunning = 0;
               //tells the disk driver process to stop running
               write(fd[3][1], &isRunning, sizeof(int));
               //tells the page replacer process to stop running
               write(fd[4][1], &isRunning, sizeof(int));

               cout << "Number of page faults for each process:" << endl;
               for (int z = 0; z < totalPageFaults.size(); z++) {
                  cout << "Process " << totalPageFaults[z].first << ": " << totalPageFaults[z].second << ";" << endl;
               }
               //cout << "Working set: min size: " << endl;

               //destroys used semaphores
               semctl(semPH, 0, IPC_RMID, 0);
               semctl(semDD, 0, IPC_RMID, 0);
               semctl(semPR, 0, IPC_RMID, 0);
            }
            //disk driver process
            if (i == 1) {
               //wait(semDD);
               int running = 1;

               while (running == 1) {
                  wait(semDD);
                  //gets running value from read end of pipe
                  read(fd[3][0], &temp, sizeof(int));
                  //exits process
                  running = temp;
                  if (running == 0)
                     break;

                  //variables to receive piped values
                  int ddProcessValue;
                  int ddSegmentID;
                  int ddPageID;

                  //gets process value from read end of pipe
                  read(fd[0][0], &ddProcessValue, sizeof(int));
                  //gets segmentID from read end of pipe
                  read(fd[1][0], &ddSegmentID, sizeof(int));
                  //gets pageID from read end of pipe
                  read(fd[2][0], &ddPageID, sizeof(int));

                  /* //troubleshooting
                  cout << "dd process is running instruction with processV " << ddProcessValue << "/ segID " << ddSegmentID <<
                          " / pageID " << ddPageID << endl;
                  */

                  //gets pointer to the current page in the process
                  Page *ptrForPage = &processes[ddProcessValue].addrSpace.segmentTables[0].segments[ddSegmentID].pageTable.pages[ddPageID];

                  Frame *ptrForFrame = NULL;
                  if (LRU_Array.size() < pageFramePerProcess) {
                     //look for empty space in the main memory
                     for (int m = 0; m < framesInMainMemory.size(); m++) {
                        if (framesInMainMemory[m].isAllocated == false) {
                           //gets empty frame
                           ptrForFrame = &framesInMainMemory[m];
                           break;
                        }
                     }
                     //error checking
                     if (ptrForFrame == NULL) {
                        break;
                     }
                  }

                  //sets frame information
                  ptrForFrame->isAllocated = true;
                  ptrForFrame->processID = processes[ddProcessValue].processID;
                  ptrForFrame->pageID = ddPageID;
                  ptrForFrame->segmentID = ddSegmentID;

                  //sets page to frame
                  ptrForPage->frameID = ptrForFrame->frameID;
                  ptrForPage->isAllocated = true;

                  //signals page handler
                  signal(semPH);
               }
            }
            //page replacement process
            if (i == 2) {
               //wait(semPR);
               int running = 1;

               while (running == 1) {
                  wait(semPR);
                  //gets running value from read end of pipe
                  read(fd[4][0], &temp, sizeof(int));

                  //exits process
                  running = temp;
                  if (running == 0)
                     break;

                  //variables to receive piped values
                  int prProcessValue;

                  //gets process value from read end of pipe
                  read(fd[5][0], &prProcessValue, sizeof(int));

                  //cout << "pr process is running instruction " << endl;

                  Frame *ptrForFrame = NULL;
                  ptrForFrame = &framesInMainMemory[processes[prProcessValue].addrSpace.LastPagesUsed[0].frameID];
						processes[prProcessValue].addrSpace.LastPagesUsed.pop_back();

                  cout << "\tReplaced frame " << ptrForFrame->frameID << endl;

                  //signals page handler
                  signal(semPH);
               }
            }
         exit(0); //stops child processes from creating more child processes
      }
   }

	return 0;
}
