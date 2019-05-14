#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//function encrypts a word
string encryptor(string user_word, unsigned long long int shift) 
{ 
    string result = ""; //holds encrypted string

    //loops through every letter 
    for (int letter = 0; letter < user_word.length(); letter++) 
    { 
        //encrypts uppercase letters 
        if (isupper(user_word[letter])) 
        {
          result += (((user_word[letter] - 'A') + shift) % 26 + 'A'); 
        }
        //encrypts lowercase letters 
        else if (islower(user_word[letter]))
        {
           result += (((user_word[letter] - 'a') + shift) % 26 + 'a'); 
        }
        //does not encrypt non-alpha chars
        else
        {
           result += user_word[letter];
        }
    }
    //returns the resulting string 
    return result; 
} 

int main()
{
    int num_words; //stores number of words
    int user_choice; //stores user choice
    unsigned long long int user_shift; //stores user shift number
    bool cont1 = true; //checks if number of user words is a positive integer
    bool cont2 = true; //checks if user wishes to quit program 

   //implements a loop so that it will continue asking until the user provides a positive integer
   while(cont1) 
   {  
       cout <<"How many words are in your message? \n";
       cout <<"Enter value: ";
         
       // get user input integer here
       cin >> num_words;
      
       if (num_words <= 0) 
           cout <<"\nInvalid value. Please Re-enter a number of positive value\n";
       else //leaves loop
         cont1 = false;
   }

   //declares a dynamic array of string type with the specified number of elements
   string* encrypt_arr; 
   encrypt_arr = new string[num_words];
   string* enc_ptr = encrypt_arr; //pointer to array
    
   while(cont2) 
   {
       cout <<"\nSelect one of these options: (1) Get Message (2) Encrypt (3) Print (4) Quit";
       cout <<"\nSelection: ";
       
       // obtain user input option (an integer)
       cin >> user_choice;
       // based on the input the program will perform one of the following operations using switch statement
       switch(user_choice)
       {
           case 1: //Get Message
               //gets the specified number of words from the user
               cout << "\nEnter Message to Encrypt: ";
 
               //loop outputs from string buffer into array
               for (int i = 0; i < num_words; i++)
               {
                   cin >> encrypt_arr[i];
                   //cout << encrypt_arr[i]; //DEBUG
               }

               //gets shifts from the user
               cout << "\nEnter number of letters to shift: ";
               cin >> user_shift;
               break;
           
           case 2: //Encrypt
               enc_ptr = encrypt_arr; //resets pointer position
               //loop calls encryptor function with pointer parameter
               for (int j = 0; j < num_words; j++)
               {
                  *enc_ptr = encryptor(*enc_ptr, user_shift);
                  enc_ptr++; //increments pointer
                  
                  //cout << encrypt_arr[j]; //DEBUG
               }                
               break;

           case 3: //Print
               enc_ptr = encrypt_arr; //resets pointer position
               
               cout << "\n" << "The message is: "; //for formatting
               
               //loop prints every word via pointer in dynamic array
               for (int k = 0; k < num_words; k++) 
               {
                  cout << *enc_ptr << " ";
                  enc_ptr++; //increments
               }
               
               cout << "\n"; //for formatting
               break;

           case 4: 
               cont2 = false;
               break;
   
           default:
               break;
        }
    }
    
    //releases the memory allocated above
    delete [] encrypt_arr;
    
    return 0;
}
