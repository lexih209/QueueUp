#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>  
#include <algorithm>
#include <fstream>
#include <sstream>
#include "User.h"

using namespace std;


//Function that sets the user name and adds them to the user list
//Currently unused
string setUserName(map<string, vector<bool>>& userList) {
    string userName;

    cout << "\nPlease enter your name: ";
    getline(cin, userName);
    userList[userName]; // creates key but, doesn't have values yet
    return userName;
}


// Function to load users from a CSV file
void loadUsers(vector<User>& users, const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        return;
    }

    while (getline(file, line)) {

        stringstream ss(line);
        string userName, gender, genre, schedule, playstyle;

        getline(ss, userName, ',');
        getline(ss, gender, ',');
        getline(ss, genre, ',');
        getline(ss, schedule, ',');
        getline(ss, playstyle, ',');

        bool isCompetitive = (playstyle == "True" || playstyle == "1" || playstyle == "true");

        //store in user var
        users.push_back(User(userName, gender, genre, schedule, isCompetitive));

        }
    
}

// TO DO: userQuiz() 
//  Layer 4: Add more answer choices
//  Layer 5: Input validation


User quiz(){

    
    int input; // to be used for input for question responses
    string name, gender, favoriteGenre, schedule;

    // Debug: ensure user exists in the map
    //if (userList.find(userName) == userList.end()) {
    //    // If somehow missing, create entry
    //    userList[userName];
   // }

    //Get quiz answers, Layer 2 expansion to more questions
    cout << "Enter your name: ";
    getline(cin, name);

    cout << "\nHello " << name << "! Let's get you started!" << endl;

    cout << "What gender would you prefer to game with? (Male, Female, Other): ";
    getline(cin, gender);

    cout << "What is your favorite game genre? (Cozy / Survival / Action / Horror / Simulation / Strategy): ";
    getline(cin, favoriteGenre);

    cout << "When are you us
    ually available to game? (Mornings / Afternoons / Evenings / Weekends): ";
    getline(cin, schedule);

    // Final Question in original format
    // IMPORTANT: When adding more questions keep track of index of each
    // this question is index 0 for example

    cout << "Are you looking for a more competitive or casual experience? (Enter 1 or 2)\n";

    while (!(cin >> input) || (input != 1 && input != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter 1 (competitive) or 2 (casual): ";
    }

    bool isCompetitive = (input == 1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer


    return User(name, gender, favoriteGenre, schedule, isCompetitive);
}


// TO DO: matchmaking() function that matches user to other users based on quiz answers
//  Layer 2: Match based on number of matching answers
//  Layer 3: Add more questions and randomize top results
//  Layer 4: Add more users to match against (read from file?)
//  Layer 5: Output matches to a file
void matchMaker(const User& currentUser, const vector<User>& users) {
    vector<pair<string, int>> matches;

    for (const auto& other : users) {
        if (other.username == currentUser.username) continue;
        if (!currentUser.isCompatibleWith(other)) continue;

        int score = currentUser.similarityScore(other);
        matches.push_back({other.username, score});
    }

    if (matches.empty()) {
        cout << "\nNo matches found.\n";
        return;
    }

    sort(matches.begin(), matches.end(),
         [](auto& a, auto& b) { return a.second > b.second; });

    cout << "\nTop Matches:\n";
    for (int i = 0; i < min(3, (int)matches.size()); ++i) {
        cout << matches[i].first << " (Score: " << matches[i].second << ")\n";
    }
}

int 

main() {

    vector<User> users; // each user has true/false responses for series of questions
    
    /* Would creating a custom database class or something like that be beneficial?
    storing users in a vector is simpilier, but costly for time with a lot of users. 
    Maybe assigning each user an ID number(that will never change), 
    then using a that ID as a key might be more efficient. 
    Then if a user say wants to even change their username or schedules, 
    we can just search up their username instead of searching the entire database.
    */

    //Load existing users from file
    loadUsers(users, "users.csv");
    
    cout << "Welcome to QueueUp!" << endl;
    cout << "A matchmaking service for gamers!" << endl;

    //Calls Quiz function to get user info and store quiz answers
    User currentUser = quiz();
    users.push_back(currentUser);
    
    //Run matchmaker function
    matchMaker(currentUser, users);


    // Exit message
    cout << "\nThank you for using QueueUp! Happy gaming!" << endl;
    return 0;
}