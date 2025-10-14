#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;


int main() {

    string userName; // for userNames
    map<string, vector<bool>> userList; // each user has true or false responses for series of questions

    //TO DO: Turn this into a function called getUserName()
    string setUserName(){
        cout << "Welcome to QueueUp!" <<endl;
        cout << "A matchmaking service for gamers!" << endl;
        cout << "\nPlease enter your name: ";
        getline(cin, userName);
        userList[userName]; // creates key but, doesn't have values yet
        return userName;
    }



    
    //TO DO: userQuiz() function that asks user gaming preference questions
        //Layer 2: Store answers in a struct or class
        //Layer 3: Add more questions
        //Layer 4: Add more answer choices
        //Layer 5: Input validation
    // now to ask questions and their responses
    void quiz(string userName){
        int input; // to be used for input for question responses

        // need to check if username exists already, call setName if not
        if(userList.find(userName) == userList.end()){
            setUserName(userName); // must call set name function before quiz
        }
        
        // begin the quiz and storing answers in boolean vector
        
        // first question: are you more competitve or casual?
        // IMPORTANT: When adding more questions keep track of index of each
        // this question is index 0 for example

        cout << "Are you looking for a more competitve or casual experience?"; 
        cout << " (Enter 1 or 2)\n";
        while(true){ // loop in case of user error
            cin >> input; 
            if(input == 1){
                userList[userName].push_back(true);
                break; // can break from loop once valid
            }else if(input == 2){
                userList[userName].push_back(false);
                break; // break from loop once valid
            } else {
                cout << "Invalid. Enter again:"; 
                continue; // continue with the loop
            }
        }
    }



    //ADD FEATURE: 
        //Layer 2: Compare against list of existing usernames for uniqueness
        //Layer 3: Banned user list comparison
        //Layer 4: User login (simple)
        //Layer 5: Username suggestions feature
        //Layer 6: Password protection/authentication


    cout << "\nHello " << userName << "! Let's get you started!" << endl;





    //TO DO: matchmaking() function that matches user to other users based on quiz answers
        //Layer 2: Match based on number of matching answers
        //Layer 3: Add more questions and randomize top results
        //Layer 4: Add more users to match against (read from file?)
        //Layer 5: Output matches to a file

    void matchMaker(string userName){
        // for phase 1, focusing on matching exactly based on answers
        // later phases we will attempt to create compatability scores
        // knowing that users most often will not exactly match

        cout << "Matches for user " << userName << " :"; 
        for(auto user = userList.begin(); user != userList.end(); user ++){
            if(userName == user.first){ // don't matchmake user with themself
                continue; 
            } else{ 
                if(userList[userName] == user.second){ // checks if responses to questions are same
                    cout << user.first << " "; // print the name of the user matched
                }
            }
        }

        cout << "\nThose are all the matches!"; 
    }


    cout << "\nThank you for using QueueUp! Happy gaming!" << endl;













    return 0;
}