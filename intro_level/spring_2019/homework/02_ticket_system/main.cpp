#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int iterations, numAttempted, seed;
	double accSuccessRate;
	
	const int theaterSeats = 30; //parameter for number of seats in theater
	int tempSeatVal = 0; //holds seat number
	int numSuccess; //counter for transaction successes in an iteration
	int totalSuccess = 0; //counter for total successes
	int seatArray[theaterSeats]; //array representing seats
		
	cin >> iterations; //number of iterations to be evaluated
	cin >> numAttempted; //number of attempted sales
	cin >> accSuccessRate; //accepted success rate
	cin >> seed; //seed for random number generation
	
	//checks for valid input
	if (iterations > 0 && numAttempted >= 0 && (accSuccessRate >= 0 && accSuccessRate <= 1) && seed >= 0) {
		//sets seed and starts iterations
		srand(seed);
      	
		for (int i = 0; i < iterations; i++) {
			//every iteration of the simulation starts by setting all seats to empty
			for (int seat = 0; seat < theaterSeats; seat++) {
				seatArray[seat] = 0;
			}
			//simulates customer transaction attempts   
			for (int j = 0; j < numAttempted; j++) {
				numSuccess = 0; //resets counter for successful transactions
				tempSeatVal = rand() % theaterSeats;
				if (seatArray[tempSeatVal] == 0) { //0 represents bool value (empty seat)
					numSuccess += 1; //increments successful transactions
					totalSuccess += 1; //stores total amount of successful transactions
					seatArray[tempSeatVal] = 1; //1 represents bool value (filled seat)
				}
			}
		}
   	
		//final output
		cout << setprecision(2) << fixed; //sets outputs to two decimal places
		cout << "Acceptable success rate: " << accSuccessRate << endl;
		cout << "Average attempted sales: " << (float) numAttempted << endl;
		cout << "Average completed sales: " << ((float) totalSuccess / iterations) << endl;
		cout << "Observed success rate: " << ((float) totalSuccess / (numAttempted * iterations)) << endl;

		//if statement to test success rate
		if ((float) totalSuccess / (numAttempted * iterations) < accSuccessRate)
		   cout << "Observed success rate not in acceptable range." << endl;
		else
		   cout << "Observed success rate is acceptable." << endl;
   	}
   	//output for invalid input
	else {
		cout << "Error. Invalid parameters." << endl;
	}
		
	return 0;
}
