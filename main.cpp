#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;


int main() {

    string userName;

    //TO DO: Turn this into a function called getUserName()
    cout << "Welcome to QueueUp!" <<endl;
    cout << "A matchmaking service for gamers!" << endl;
    cout << "\nPlease enter your name: ";
    getline(cin, userName);

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
        //Layer 3: Match based on specific answers (i.e. if user wants to play FPS, match with other FPS players)
        //Layer 4: Add more users to match against (read from file?)
        //Layer 5: Output matches to a file


    cout << "\nThank you for using QueueUp! Happy gaming!" << endl;













    return 0;
}