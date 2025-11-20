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



// setUserName()
// - Prompts the player for their name.
// - Adds them to the userList map (as a key) with an empty vector<bool>.
// - This is currently not used yet

string setUserName(map<string, vector<bool>>& userList) {
    string userName;


    cout << "\nPlease enter your name: ";
    getline(cin, userName);


    // Creates a map entry for this username with an empty answer vector
    userList[userName];


    return userName;
}



//loadUsers()
//- Loads pre-existing users from a CSV file.
//- Each line is expected in this format:
//     username,gender,genre,schedule,playstyleFlag
//- playstyleFlag may be "True/False" or "1/0".
//- Each parsed line is stored as a User object inside the users vector.

void loadUsers(vector<User>& users, const string& filename) {
    ifstream file(filename);
    string line;


    if (!file.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        return;
    }


    // Read each line and parse CSV fields
    while (getline(file, line)) {
        stringstream ss(line);
        string userName, gender, genre, schedule, playstyle;


        getline(ss, userName, ',');
        getline(ss, gender, ',');
        getline(ss, genre, ',');
        getline(ss, schedule, ',');
        getline(ss, playstyle, ',');


        // Determine whether playstyle is competitive or casual
        bool isCompetitive =
            (playstyle == "True" || playstyle == "1" || playstyle == "true");


        // Store parsed user in vector
        users.push_back(User(userName, gender, genre, schedule, isCompetitive));
    }
}

// TO DO: userQuiz() 
//  Layer 4: Add more answer choices
//  Layer 5: Input validation


//quiz()
//- Collects user information via multiple questions.
//- Expands on the original single-question quiz.
//- Includes:
//    Name
//    Gender preference
//    Favorite game genre
//    Gaming schedule
//    Competitive vs casual preference
//- Returns a fully constructed User object.

User quiz() {


    int input;
    string name, gender, favoriteGenre, schedule;
    // Debug: ensure user exists in the map
    //if (userList.find(userName) == userList.end()) {
    //    // If somehow missing, create entry
    //    userList[userName];
   // }

    // Name
    cout << "Enter your name: ";
    getline(cin, name);


    cout << "\nHello " << name << "! Let's get you started!" << endl;


    // Gender preference
    cout << "What gender would you prefer to game with? (Male, Female, Other): ";
    getline(cin, gender);


    // Favorite game genre
    cout << "What is your favorite game genre? (Cozy / Survival / Action / Horror / Simulation / Strategy): ";
    getline(cin, favoriteGenre);


    // Schedule
    cout << "When are you usually available to game? (Mornings / Afternoons / Evenings / Weekends): ";
    getline(cin, schedule);

    // Final Question in original format
    // IMPORTANT: When adding more questions keep track of index of each
    // this question is index 0 for example

    // Competitive or casual?
    cout << "Are you looking for a more competitive or casual experience? (Enter 1 or 2)\n";


    // Validate numeric input
    while (!(cin >> input) || (input != 1 && input != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter 1 (competitive) or 2 (casual): ";
    }


    bool isCompetitive = (input == 1);


    // Clear buffer for future getline() calls
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    // Return newly created user
    return User(name, gender, favoriteGenre, schedule, isCompetitive);
}


//matchMaker()
//- Compares the currentUser to all stored users.
//- Uses:
//    - isCompatibleWith()   → checks if user preferences align
//    - similarityScore()    → determines strength of the match
//- Creates a sorted list of top matches.
//- Displays the top 3 best matches based on score.

void matchMaker(const User& currentUser, const vector<User>& users) {
    vector<pair<string, int>> matches;


    // Evaluate compatibility with each other user
    for (const auto& other : users) {


        // Skip comparing with self
        if (other.username == currentUser.username) continue;


        // Skip incompatible matches
        if (!currentUser.isCompatibleWith(other)) continue;


        // Similarity score
        int score = currentUser.similarityScore(other);


        matches.push_back({other.username, score});
    }


    // If no matches were found
    if (matches.empty()) {
        cout << "\nNo matches found.\n";
        return;
    }


    // Sort matches by highest similarity score
    sort(matches.begin(), matches.end(),
         [](auto& a, auto& b) { return a.second > b.second; });


    // Display top 3 matches
    cout << "\nTop Matches:\n";
    for (int i = 0; i < min(3, (int)matches.size()); ++i) {
        cout << matches[i].first << " (Score: " << matches[i].second << ")\n";
    }
}



//main()
//- Loads users from file
//- Runs quiz for the current user
//- Adds new user to the user list
//- Runs matchmaking
//- Displays exit message

int main() {


    vector<User> users;  // Stores all user accounts loaded from file or created


    // Load stored user data
    loadUsers(users, "users.csv");


    cout << "Welcome to QueueUp!" << endl;
    cout << "A matchmaking service for gamers!" << endl;


    // Run the quiz and create the current user
    User currentUser = quiz();
    users.push_back(currentUser);


    // Find top matches for the current user
    matchMaker(currentUser, users);


    // Farewell message
    cout << "\nThank you for using QueueUp! Happy gaming!" << endl;


    return 0;
}