#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;


int main() {

    string userName;
    //TO DO: Separate into classes for optimized main program flow
        //Layer 2: Create User class to store user profile and quiz answers
        //Layer 3: Create Match class to store match results
        //Layer 4: Create Quiz class to handle quiz questions and answers
        //Layer 5: Create a Database class to handle user profiles and match storage   

    //TO DO: Turn this into a function called getUserName()
    cout << "Welcome to QueueUp!" <<endl;
    cout << "A matchmaking service for gamers!" << endl;
    cout << "\nPlease enter your name: ";
    getline(cin, userName);

    //TO DO: User profile storage (map? vector?)
        //Layer 2: Store user profiles in a file
        //Layer 3: Load user profiles from file on startup
        //Layer 4: Allow users to update their profiles
        //Layer 5: Delete user profiles

    //ADD FEATURE: 
        //Layer 2: Compare against list of existing usernames for uniqueness
        //Layer 3: Banned user list comparison
        //Layer 4: User login (simple)
        //Layer 5: Username suggestions feature
        //Layer 6: Password protection/authentication


    cout << "\nHello " << userName << "! Let's get you started!" << endl;


    //TO DO: userQuiz() function that asks user gaming preference questions
        //Layer 2: Store answers in a struct or class
        //Layer 3: Add more questions
        //Layer 4: Add more answer choices
        //Layer 5: Input validation





    //TO DO: matchmaking() function that matches user to other users based on quiz answers
        //Layer 2: Match based on number of matching answers
        //Layer 3: Add more questions and randomize top results
        //Layer 4: Add more users to match against (read from file?)
        //Layer 5: Add user to user bans
   




    //TO DO: results() function that displays match results to user
        //Layer 2: Format results nicely
        //Layer 3: Add option to save results to file
        //Layer 4: Add option to email results (requires additional libraries)
        //Layer 5: Add option to share results on social media (requires additional libraries)


    cout << "\nThank you for using QueueUp! Happy gaming!" << endl;













    return 0;
}