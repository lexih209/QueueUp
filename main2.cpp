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

static inline string toLowerTrim(string s){
    // trim
    auto l = s.find_first_not_of(" \t\r\n");
    if(l==string::npos) return string();
    auto r = s.find_last_not_of(" \t\r\n");
    s = s.substr(l, r-l+1);
    // to lower
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(c); });
    return s;
}


// array for questions
vector<string> qList[5]; // vector index corresponds to points
// ex: ?array[1]["Do you like mansplaining?"] That question is one point



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

    bool firstLine = true;
    while (getline(file, line)) {
        if(firstLine){
            firstLine = false;
            // skip header if it contains 'username' (case-insensitive)
            string lower = line;
            transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return tolower(c); });
            if(lower.find("username") != string::npos) continue;
            // otherwise fall through and parse as data
        }

        stringstream ss(line);
        string userName, gender, genre, schedule, playstyle;

        getline(ss, userName, ',');
        getline(ss, gender, ',');
        getline(ss, genre, ',');
        getline(ss, schedule, ',');
        getline(ss, playstyle, ',');

        // normalize fields to lowercase/trim so comparisons are consistent
        gender = toLowerTrim(gender);
        genre = toLowerTrim(genre);
        schedule = toLowerTrim(schedule);
        playstyle = toLowerTrim(playstyle);

        bool isCompetitive = (playstyle == "true" || playstyle == "1");

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
    gender = toLowerTrim(gender);

    cout << "What is your favorite game genre? (Cozy / Survival / Action / Horror / Simulation / Strategy): ";
    getline(cin, favoriteGenre);
    favoriteGenre = toLowerTrim(favoriteGenre);

    cout << "When are you usually available to game? (Mornings / Afternoons / Evenings / Weekends): ";
    getline(cin, schedule);
    schedule = toLowerTrim(schedule);

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

    return User(name, gender, favoriteGenre, schedule, isCompetitive, true); 
}


// TO DO: matchmaking() function that matches user to other users based on quiz answers
//  Layer 2: Match based on number of matching answers
//  Layer 3: Add more questions and randomize top results
//  Layer 4: Add more users to match against (read from file?)
//  Layer 5: Output matches to a file
void matchMaker(const User& currentUser, const vector<User>& users) {
    vector<pair<string, int>> matches;

    cout << "\nCurrent User: " << currentUser.username 
         << " | G:" << currentUser.gender << " Gr:" << currentUser.favoriteGenre 
         << " S:" << currentUser.schedule << " C:" << (currentUser.isCompetitive ? "1" : "0") << "\n\n";

    for (const auto& other : users) {
        if (other.username == currentUser.username) continue;

        //bool compatible = currentUser.isCompatibleWith(other);
        int score = currentUser.similarityScore(other);
        matches.push_back({other.username, score});
        
        /*Debug: show all candidates with score 50+
        if (score >= 50) {
            cout << "  " << other.username << " | Score: " << score 
                 << " | Compatible: " << (compatible ? "YES" : "NO")
                 << " | G:" << other.gender << " Gr:" << other.favoriteGenre 
                 << " S:" << other.schedule << " C:" << (other.isCompetitive ? "1" : "0") << "\n";
        }*/ 
    }

    if (matches.empty()) {
        cout << "\nNo matches found.\n";
        return;
    }

    sort(matches.begin(), matches.end(),
         [](auto& a, auto& b) { return a.second > b.second; });

    cout << "\nTop Matches:\n";
    size_t limit = matches.size() < 3 ? matches.size() : 3;
    for (size_t i = 0; i < limit; ++i) {
        cout << matches[i].first << " (Score: " << matches[i].second << ")\n";
    }
}

// questions update for every user
void addQuestion(vector<User>& list, int points, string question){
    for(User& current : list){
        current.addQuestion(points, question);
    }
}

// separated it from the addQuestions because I don't want it to answer after
// each question. 
void scoreCalc(vector<User>& list ){
    for(User& current : list){
        if(current.isDummy){
            current.fillQuestions(); // fill questions for dummies
        }
        else if(!current.isDummy){
            current.answerQuestions(); 
        }
        else{
            cerr << "Error: This isn't a dummy or person?";
        }
    }
}

// make a function to answer all questions for user and dummies

void fillQs(vector<User>& list){
    for(User& current : list){
        if(current.isDummy == true){
            current.fillQuestions();
        }
        else if(current.isDummy == false){
            current.answerQuestions();
        }
        else{
            cerr << "Something went wrong...";
        }
    }
}


int main() {
    vector<User> users; // each user has true/false responses for series of questions

    
    //Load existing users from file
    //loadUsers(users, "users.csv");
    
    cout << "Welcome to QueueUp!" << endl;
    cout << "A matchmaking service for gamers!" << endl;

    //Calls Quiz function to get user info and store quiz answers
    User currentUser = quiz();
    users.push_back(currentUser);

    // load the dummy users
    loadUsers(users, "users.csv");
    
    // add questions before running matchmaker 
    // HAS TO BE AFTER ALL USERS ARE LOADED IN
    addQuestion(users, 5, "Are you a variety gamer?");
    addQuestion(users, 4, "Do you play on console?");
    addQuestion(users, 3, "Do you have a quality headset?");
    addQuestion(users, 2, "Do you have kids?");
    addQuestion(users, 3, "Do you listen to music while you play?");
    addQuestion(users, 5, "Can you tolerate toxicity?");
    addQuestion(users, 2, "Do you have a loud dog?");
    addQuestion(users, 4, "Are you brainrot?");
    addQuestion(users, 1, "Do you play outside of your listed hours?");


    // answer questions for whole list
    // HAS TO BE AFTER QUESTIONS ARE ADDED
    fillQs(users);
    
    //Run matchmaker function
    matchMaker(users[0], users);

    // Exit message
    cout << "\nThank you for using QueueUp! Happy gaming!" << endl;
    return 0;
}
