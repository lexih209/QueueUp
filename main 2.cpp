#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>  


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


    cout << "Matches for user " << userName << " : ";
    bool any = false;


    for (const auto& kv : userList) {
        const string& otherName = kv.first;
        const vector<bool>& answers = kv.second;


        if (otherName == userName) continue; // don't match with self


        if (answers == myAnswers) {
            cout << otherName << " ";
            any = true;
        }
    }


    if (!any) cout << "(no exact matches)";
    cout << "\nThose are all the matches!\n";
}


int main() {
    string userName; // for userNames
    map<string, vector<bool>> userList; // each user has true/false responses for series of questions


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