#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>  
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;


// TO DO: Turn this into a function called setUserName()
string setUserName(map<string, vector<bool>>& userList) {
    string userName;
    cout << "Welcome to QueueUp!" << endl;
    cout << "A matchmaking service for gamers!" << endl;
    cout << "\nPlease enter your name: ";
    getline(cin, userName);
    userList[userName]; // creates key but, doesn't have values yet
    return userName;
}

void loadUsers(map<string, vector<bool>>& userList, const string& filename){
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        return;
    }

    while (getline(file, line)) {

        stringstream ss(line);
        string userName;
        string playstyle;

        getline(ss, userName, ',');
        getline(ss, playstyle, ',');

        bool isCompetitive = (playstyle == "True" || playstyle == "1" || playstyle == "true");

        //store in map
        userList[userName].push_back(isCompetitive);

        }
    
}

// TO DO: userQuiz() function that asks user gaming preference questions
//  Layer 2: Store answers in a struct or class
//  Layer 3: Add more questions
//  Layer 4: Add more answer choices
//  Layer 5: Input validation
void quiz(const string& userName, map<string, vector<bool>>& userList) {
    int input; // to be used for input for question responses


    // ensure user exists in the map
    if (userList.find(userName) == userList.end()) {
        // If somehow missing, create entry
        userList[userName];
    }


    // first question: are you more competitive or casual?
    // IMPORTANT: When adding more questions keep track of index of each
    // this question is index 0 for example
    cout << "Are you looking for a more competitive or casual experience? (Enter 1 or 2)\n";


    while (true) { // loop in case of user error
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter 1 (competitive) or 2 (casual): ";
            continue;
        }
        if (input == 1) {
            userList[userName].push_back(true);
            break; // can break from loop once valid

        } else if (input == 2) {
            userList[userName].push_back(false);
            break; // break from loop once valid

        } else {
            cout << "Invalid choice. Enter 1 or 2: ";
        }
    }


    // consume trailing newline so a later getline works
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int compatibilityScore(const vector<bool>& a, const vector<bool>& b) {
        int score = 0;
        int len = min(a.size(), b.size());
        for (int i = 0; i < len; ++i) {
            if (a[i] == b[i]) score++;
        }
        return score;
}

// TO DO: matchmaking() function that matches user to other users based on quiz answers
//  Layer 2: Match based on number of matching answers
//  Layer 3: Add more questions and randomize top results
//  Layer 4: Add more users to match against (read from file?)
//  Layer 5: Output matches to a file
void matchMaker(const string& userName, const map<string, vector<bool>>& userList) {
    auto it = userList.find(userName);
    if (it == userList.end()) {
        cout << "No answers found for " << userName << ".\n";
        return;
    }


    const vector<bool>& myAnswers = it->second;
    vector<pair<string, int>> matches; // pair of username and score


    cout << "Matches for user " << userName << " : ";
    bool any = false;


    for (const auto& kv : userList) {
        const string& otherName = kv.first;
        const vector<bool>& answers = kv.second;

        // don't match with self
        if (otherName == userName){

         continue; 
        }

        int score = compatibilityScore(myAnswers, answers);
        matches.push_back({otherName, score});
    }

    // Sort top matches by score
    sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    //Output top 3 matches
    cout << "\nTop Matches:\n";
    int shown = 0;

    for (const auto& match : matches) {
        
        if (shown >= 3) break;
        cout << match.first << " (Score: " << match.second << ")\n";
        any = true;
        shown++;
    }

    if (!any) cout << "(no exact matches)";
    cout << "\nThose are all the matches!\n";
}


int main() {
    string userName; // for userNames
    map<string, vector<bool>> userList; // each user has true/false responses for series of questions
    

    //Load existing users from file
    loadUsers(userList, "users.csv");

    // 1) Get username and add entry
    userName = setUserName(userList);


    cout << "\nHello " << userName << "! Let's get you started!" << endl;


    // 2) Ask quiz questions and store answers
    quiz(userName, userList);


    // 3) Run matchmaker
    matchMaker(userName, userList);


    cout << "\nThank you for using QueueUp! Happy gaming!" << endl;
    return 0;
}