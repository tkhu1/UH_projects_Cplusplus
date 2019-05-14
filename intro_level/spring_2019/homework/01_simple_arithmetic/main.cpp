#include <iostream>
#include <iomanip>
using namespace std;

int main() {

   int players;
   double expected_time;
   char team;
   
   double actual_time;
   
   // user inputs
   cin >> players;
   cin >> expected_time;
   cin >> team;
   
   // main loop checking for correct input
   if ( (players > 0) && (expected_time > 0) ) { 
      // first layer of nested loop checking for correct number of players
      if (players <= 18) {
         // second layer of nested loops differentiating into player counts (first category)
         if (players <= 6) {
            // third layer of nested loops differentiating into teams
            if ( (team == 'R') || (team == 'r') ) {
               actual_time = expected_time - ( expected_time * ( 10.0 / 100 ) );
            }
            else if ( (team == 'B') || (team == 'b') ) {
               actual_time = expected_time - ( expected_time * ( 15.0 / 100 ) );
            }
            else if ( (team == 'Y') || (team == 'y') ) {
               actual_time = expected_time - ( expected_time * ( 20.0 / 100 ) );
            }
            // any other team
            else {
               actual_time = expected_time;
            }   
         }
         // second layer of nested loops differentiating into player counts (second category)
         if ( (players > 6) && (players <= 12) ) {
            // third layer of nested loops differentiating into teams
            if ( (team == 'R') || (team == 'r') ) {
               actual_time = expected_time - ( expected_time * ( 20.0 / 100 ) );
            }
            else if ( (team == 'B') || (team == 'b') ) {
               actual_time = expected_time - ( expected_time * ( 25.0 / 100 ) );
            }
            else if ( (team == 'Y') || (team == 'y') ) {
               actual_time = expected_time - ( expected_time * ( 30.0 / 100 ) );
            }
            // any other team
            else {
               actual_time = expected_time;
            }
         }
         // second layer of nested loops differentiating into player counts (third category)
         if (players > 12) {
            // third layer of nested loops differentiating into teams
            if ( (team == 'R') || (team == 'r') ) {
               actual_time = expected_time - ( expected_time * ( 30.0 / 100 ) );
            }
            else if ( (team == 'B') || (team == 'b') ) {
               actual_time = expected_time - ( expected_time * ( 35.0 / 100 ) );
            }
            else if ( (team == 'Y') || (team == 'y') ) {
               actual_time = expected_time - ( expected_time * ( 40.0 / 100 ) );
            }
            // any other team
            else {
               actual_time = expected_time;
            }
         }
         // output
         cout << fixed;
         cout << setprecision(2) << actual_time;
         cout << " minutes";
      }
      // first layer nested loop failure output
      else {
         cout << "Too many players";
      }
   }
   // main loop failure output
   else {
      cout << "Wrong input";
   }
   
   return 0;
}
