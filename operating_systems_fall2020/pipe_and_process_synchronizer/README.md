Implemented a program to synchronize, with Unix/Linux pipes, concurrent processes which perform arithmetic operations.

This program is divided into five parts:
0. DATA STRUCTURES
1. HELPER FUNCTIONS
2. MAIN - INPUT HANDLING
3. MAIN - PIPE HANDLING
4. MAIN - PROCESS HANDLING

0. DATA STRUCTURES
This section contains the process class, which represents a process and contains all the 
data for a process such as its value, name, process type (variable or vertex), and commands. 
Commands such as "a -> v0 " are put into the corresponding process in its command vector. 
The function addCommand populates the command vector, and the functionprintCommands is for 
troubleshooting.

1. HELPER FUNCTIONS
This section contains two functions, lineParser and calculator. lineParses parses each line 
of the input file into four paired vectors in main: 1) input_var names and values, 2) vertex 
names and operation types (i.e., PLUS, MINUS...), 3) process names to be written out 
(i.e., a, v0, b, v1...), 4) commands (i.e., a -> v0...). 
The calculator function does the mathematical operation given two values and a operation 
(e.g., PLUS, MINUS...). Every vertex that needs a calculation will pass those parameters to 
this function, and gets one calculated value as return.

2. MAIN - INPUT HANDLING
This section opens the input file and feeds each line into the lineParser helper function.

3. MAIN - PIPE HANDLING
This section creates pipes according to the number of processes needed. so if 20 processes 
are needed, then 20 pipes are created.

4. MAIN - PROCESS HANDLING
This section contains the main logic of the program. First a master list that holds all of the 
process classes is created (e.g., processes a,b,c,v0,v1,...). Then a paired vector that connects
process names to their respective pipes is created.
Next comes a for loop that forks and creates the necessary processes. Each of these processes 
then either writes to a pipe or reads from a pipe/does a calculation depending on the process 
and its related commands. In general, input_vars write to their respective pipe while vertices will
read and calculate and/or write to a pipe for further operations. 
Finally, the correct output is sent to the console. 

To use the program, the following command lines are used:

command to compile:                  

g++ -std=c++11 hw1.cpp

command to see output in terminal:   

./a.out "input_file_name.txt"