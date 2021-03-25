#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// FALL20 COSC3360 - HOMEWORK 1                                                      //
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
// PROFESSOR: Albert Cheng - University of Houston                                   //
///////////////////////////////////////////////////////////////////////////////////////

/*
DISCLAIMER: Small portions of code have been inspired by examples from the internet,
            such as from Geeks4Geeks
*/

// 0. DATA STRUCTURES ///////////////////////////////////////////////////////////////////////////////

// 0.a Class - Process//
/*This class represents a process and contains all the data for a process such as its value, name,
  process type (variable or vertex), and commands. The function addCommands populates the command
	vector, and the function printCommands is for troubleshooting. */
class Process
{
   private:
      int value;
      string name;
      string processType;
   public:
      //contains paired command names (e.g., a->v0 is stored as <write, v0> )
      vector<pair<string,string>> commands;

      //default constructor
      Process()
      {
         value = 0;
         name = "default";
         processType = "default process";
		}
      //constructor
      Process(string inName, int inValue, string inProcessType,
              vector<pair<string,string>> &inComms)
      {
         name = inName;
         value = inValue;
         processType = inProcessType;
         addCommands(inComms);
      }

      //gets private value in process
      int getValue();
      //gets private name in process
      string getName();
		//gets private process type
      string getProcessType();

      //pushes commands vector from main into the process's commands vector
      void addCommands(vector<pair<string,string>> &inputComms);
      //prints commands for troubleshooting
      void printCommands();
};

// 0.a-1 Class Process Functions//
//returns current value of variable / vertex
int Process::getValue()
{
   int returnVal = 0;
   returnVal = value;
   return returnVal;
}
//returns current name of variable / vertex
string Process::getName()
{
   string returnName = "null name";
   returnName = name;
   return returnName;
}
//returns current process type of variable / vertex
string Process::getProcessType()
{
   string returnPT = "null process type";
   returnPT = processType;
   return returnPT;
}

/*This function pushes new commands from the parsed vector in main into this process's commands
  vector. It takes the memory address of the main commands vector as a parameter. Commands are
  in the paired form of <"read" or "write", "r/w target">. For example, b -> v0 would be broken up
  <"write", v0> in process b and <"read", b> in process v0.
	The vector pairs structure is inspired by an example on G4G website:
	https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
*/
void Process::addCommands(vector<pair<string,string>> &inputComms)
{
   //iterates through every command in the input parameter (parsed commands vector)
   for (int i = 0; i < inputComms.size(); i++) {
      //adds commands for input variables
      if (processType == "variable") {
         //this statement ensures only relevant commands are assigned to each process
         if (name == inputComms[i].first) {
            commands.push_back(make_pair("write", inputComms[i].second));
         }
      }
      //adds commands for vertices
      else {
         //if a vector is writing to another target, such as v0 -> v1
         if (name == inputComms[i].first) {
            commands.push_back(make_pair("write", inputComms[i].second));
         }
         //if a vector is reading from another target, such as b -> v0
         else if (name == inputComms[i].second) {
            commands.push_back(make_pair("read", inputComms[i].first));
         }
         //does nothing
         else {

         }
      }
   }
}

//prints commands for troubleshooting. Function is inspired by G4G website above.
void Process::printCommands()
{
	 for (int i = 0; i < commands.size(); i++)
    {
         //"first" and "second" are used to access 1st and 2nd element of pair respectively
         cout << "             " << commands[i].first << " -> " << commands[i].second << endl;
    }
}

// 1. HELPER FUNCTIONS //////////////////////////////////////////////////////////////////////////////

/*This function parses input file lines into paired vectors in main. Parameters are:
  1. a line from the input file (e.g., input_var a,b;)
  2. a counter address that counts the number of commands
  3. a vector in main() that contains input_var names and values (e.g., <a,0>)
  4. a vector in main() that contains vertex names and operation types (e.g., <v0,PLUS>)
  5. a vector in main() that contains process names to be written out (i.e., a, v0, b, v1...)
  6. a vector in main() that contains commands (i.e., a -> v0...)

  The populated vectors are the output.
*/
void lineParser(string input, int &counter, vector<pair<string,int>> &vars,
                                            vector<pair<string,string>> &vertices,
                                            vector<string> &writes,
                                            vector<pair<string,string>> &ops)
{
   //creates stream from input string
   istringstream stream(input);

   //checks what kind of line the input is. find function is from the internet
   bool isVar = input.find("input_var") != string::npos;
   bool isVertex = input.find("vertex") != string::npos;
   bool isOperation = input.find("->") != string::npos;
   bool isOutput = input.find("write") != string::npos;

   string temp; //working variable

   //this else if block pushes variable names into "inputVars"
   if (isVar) {
      stream >> temp; //bypasses first garbage word
      while(getline(stream, temp, ',')) {
         temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end()); /*space remover
         //removes comma from input                                                code from internet*/
         if (temp[0] == ',')
            temp = temp.substr(2,temp.size());
         //removes semicolon from input
         if (temp[temp.size()-1] == ';')
            temp = temp.substr(0,(temp.size()-1));
         //pushes variable name (i.e., a) into vars vector
         vars.push_back(make_pair(temp, 0));
      }
   }
   else if (isVertex) {
   /* this else if block pushes vertex names and their types into a paired vector "inputVertices"
      in main() */
      int i = 0; //working variable

      stream >> temp; //bypasses first garbage word
      //gets vertex name and vertex type
      while(getline(stream, temp, '=')) {
         temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end()); //removes spaces
         if (temp[0] == ',')
            temp = temp.substr(2,temp.size());
         //pushes vertex name (i.e., v0) into vertices vector
         vertices.push_back(make_pair(temp, ""));

         getline(stream, temp, ',');
         temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end()); //removes spaces
         //removes semicolon from input
         if (temp[temp.size()-1] == ';')
            temp = temp.substr(0,(temp.size()-1));
         //pushes operation string (i.e., TIMES) into vertices vector
         vertices[i].second = temp;
         i++;
      }
   }
   else if (isOperation) {
   /* this else if block pushes a single line of vertex operations (i.e., a -> v0) into
      a paired vector for main processing */
      string op1 = "";
      string op2 = "";

      //gets vertex names (i.e., v0) for the vector
      while(getline(stream, op1, '>')) {
         op1.erase(remove_if(op1.begin(), op1.end(), ::isspace), op1.end()); //removes spaces
         if (op1[op1.size()-1] == '-')
            op1 = op1.substr(0,(op1.size()-1));

         stream >> op2;
         //removes spaces
         op2.erase(remove_if(op2.begin(), op2.end(), ::isspace), op2.end());
         if (op2[op2.size()-1] == ';')
            op2 = op2.substr(0,(op2.size()-1));
         /*links secondary read commands to previous write commands (e.g., v0 -> v1
                                                                     in c -> v0 -> v1 */
         if (op1 == "")
            op1 = ops[counter-1].second;

         //pushes into the paired vector "inputOps" in main()
         ops.push_back(make_pair(op1, op2));
         counter++;
      }
   }
   //this else if block pushes write names into "inputWrites"
   else if (isOutput) {
      string writesLine; //temp holder

      getline(stream, temp, '(');        //bypasses first garbage chars
      getline(stream, writesLine, ')');  //bypasses ending garbage chars

      //creates stream from input string
      istringstream writeStream(writesLine);

      while(getline(writeStream, temp, ',')) {
         temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end()); //removes spaces
         //removes comma from input
         if (temp[0] == ',')
            temp = temp.substr(2,temp.size());
         //pushes the variable/vertex name (i.e., a or v0) into "inputWrites" vector
         writes.push_back(temp);
      }
   }
   //this else block pushes var values into "inputValues"
   else {
      int val;
      int i = 0;
      while(getline(stream, temp, ' ')) {
         val = stoi(temp);
         //pushes the variable value into "inputValues" vector
         vars[i].second = val;
         i++;
      }
   }
}

/*This function calculates the mathematical operation with input parameters:
  1. input value 1
  2. input value 2
  3. type of operation as a string (i.e., PLUS, MINUS...)

  Every vertex will pass those parameters to this function, and gets one calculated value as return
*/
int Calculator(int inputValue1, int inputValue2, string operationType)
{
   /* //troubleshooting
   cout << "\ncalculator is doing: " << " int1: " << inputValue1 << " / int2: " << inputValue2 <<
           " / op: " << operationType << endl << endl;*/

   if (operationType == "PLUS") {
      return inputValue1 + inputValue2;
   }
	if (operationType == "MINUS") {
	   if (inputValue1 == inputValue2) {
         return 0;
      }
      else if (inputValue1 > inputValue2) {
         return inputValue1 - inputValue2;
      }
      else {
         return inputValue2 - inputValue1;
      }
   }
   if (operationType == "TIMES") {
      return inputValue1 * inputValue2;
   }
	if (operationType == "DIVIDE") {
      if (inputValue1 == inputValue2) {
         return 1;
      }
		else if (inputValue1 > inputValue2) {
		   return inputValue1 / inputValue2;
		}
		else {
         return inputValue2 / inputValue1;
		}
   }
	return 999;
}

// MAIN PROGRAM /////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
   //initial variable declarations
   vector<pair<string,int>> inputVars;        //holds the input variables and values from input file
   vector<pair<string,string>> inputVertices; //holds the input vertices from input file
   vector<string> inputWrites;                //holds the output names from input file
   vector<pair<string,string>> inputOps;      //holds the operations from input file

   // 2. INPUT HANDLING /////////////////////////////////////////////////////////////////////////////

	int commCounter = 0;       //used to count number of commands in input file
	string fileName = argv[1]; //stores input file name
	string line;               //stores every line from input file stream

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
         //parses input line by line
         lineParser(line, commCounter, inputVars, inputVertices, inputWrites, inputOps);
      }
   }

   fileIn.close();

   /* //vector checking and troubleshooting
   cout << "\nvar vector" << endl;
   for (int i = 0; i < inputVars.size(); i++) {
      cout << inputVars[i].first << " " << inputVars[i].second << " / ";
   }
   cout << "\n\nvertices vector" << endl;
   for (int i = 0; i < inputVertices.size(); i++) {
      cout << inputVertices[i].first << " " << inputVertices[i].second << " / ";
   }
   cout << "\n\nwrites vector" << endl;
   for (int i = 0; i < inputWrites.size(); i++) {
      cout << inputWrites[i] << " ";
   }
   cout << "\n\nops vector" << endl;
   for (int i = 0; i < inputOps.size(); i++) {
      cout << inputOps[i].first << " " << inputOps[i].second << " / ";
   }*/

   // 3. PIPE HANDLING //////////////////////////////////////////////////////////////////////////////
   int numProcesses = inputVars.size() + inputVertices.size(); //gets the total number of processes

   //cout << "\nnum processes: " << numProcesses << endl; //troubleshooting

   //creates initial file descriptor for pipe
   int fd[numProcesses-1][2];

   //creates pipes for each process
   for (int i = 0; i < numProcesses; i++) {
      pipe(fd[i]);
      if (pipe(fd[i])==-1) {
         cout << "Pipe Failed. Exiting program." << endl;
         return 1;
      }
   }

   // 4. PROCESS HANDLING ///////////////////////////////////////////////////////////////////////////

   vector<Process> inputProcesses; //master list that holds the input processes from input file

   int numInputVars = inputVars.size(); 			//gets the number of input var processes
   int numInputVertices = inputVertices.size(); //gets the number of input vertex processes

   //populates master list of inputProcesses with input variables
   for (int i = 0; i < numInputVars; i++) {
      inputProcesses.push_back(Process(inputVars[i].first, inputVars[i].second, "variable", inputOps));
   }

	//populates master list of inputProcesses with input vertices
   for (int i = 0; i < numInputVertices; i++) {
      inputProcesses.push_back(Process(inputVertices[i].first, 0, inputVertices[i].second, inputOps));
   }

   //contains pairs of pipes to processes (e.g., a as process 0 is stored as <a,0>)
   vector<pair<string,int>> pipeConnector;
   //populates the above vector
   for (int i = 0; i < inputProcesses.size(); i++) {
      pipeConnector.push_back(make_pair(inputProcesses[i].getName(), i));
   }

   /* //troubleshooting
   for (int i = 0; i < pipeConnector.size(); i++) {
      cout << "\n\n" << pipeConnector[i].first << " pipes to " << pipeConnector[i].second << endl;
   }
   cout << "\nmaster process list:" << endl;
   for (int i = 0; i < inputProcesses.size(); i++) {
      cout << i << ". name: " << inputProcesses[i].getName() <<
              " / value: " << inputProcesses[i].getValue() <<
              " / type: " << inputProcesses[i].getProcessType() << endl <<
              "   commands below:" << endl;
      inputProcesses[i].printCommands();
      cout << endl;
   }*/

   for (int i = 0; i < numProcesses; i++) {
      //creates a number of child processes via fork
      pid_t id = fork();

      int initValue = inputProcesses[i].getValue(); //gets initial value of process
      int pipeID;    //working variable
      int temp;      //working variable
      string opType; //working variable
      if (id < 0) {
         //error checking
         cout << "ERROR: Process fork failed. Exiting program." << endl;
         return 1;
      }
      //this is a parent process that is not used in this program
      else if (id > 0) {
      }
      //this is a child process
      else {
         /* cout << "1st process " << inputProcesses[i].getName() << " has value of " <<
                   inputProcesses[i].getValue() << endl; */    //troubleshooting

         //loops every command vector in every process
         for (int j = 0; j < (inputProcesses[i].commands).size(); j++) {
            //if the command is a write operation
            if (inputProcesses[i].commands[j].first == "write") {
               pipeID = pipeConnector[i].second;

               /* //troubleshooting
               cout << inputProcesses[i].getName() << " writing " << initValue <<
                       " to pipe (" << pipeID << "," << pipeConnector[pipeID].first << ")" << endl; */

               //sends write value to write end of pipe
               write(fd[pipeID][1], &initValue, sizeof(int));
            }
            //if the command is a read operation
            if (inputProcesses[i].commands[j].first == "read") {
               for (int k = 0; k < pipeConnector.size(); k++) {
                  //gets the connecting pipe to read from and the vertex's operation type
                  if (inputProcesses[i].commands[j].second == pipeConnector[k].first) {
                     pipeID = pipeConnector[k].second;
                     opType = inputProcesses[i].getProcessType();
                  }
               }
               //gets read value from read end of pipe
               read(fd[pipeID][0], &temp, sizeof(int));
               //if vector is initially empty, sets the vector value to read value
               if (initValue == 0)
                  initValue = temp;
               //calculates the new value
               else
                  initValue = Calculator(initValue, temp, opType);

               //troubleshooting
               //cout << inputProcesses[i].getName() << "'s calculated value: " << initValue << endl;
            }
         }
         for (int l = 0; l < inputWrites.size(); l++) {
            if (inputProcesses[i].getName() == inputWrites[l]) {
               //outputs to console the process name and their value after operations
               cout << inputProcesses[i].getName() << "=" << initValue << endl;
            }
         }
         exit(0); //stops child processes from creating more child processes
      }
   }

	return 0;
}
