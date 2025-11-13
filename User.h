// class creation for user (for later implementation)
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class User {

public:
    string username, gender, favoriteGenre, schedule;
    bool isCompetitive;

    // array for questions
    vector<string> qList[5]; // vector index corresponds to points
    // ex: ?array[1]["Do you like mansplaining?"] That question is one point

    // need a corresponding array for the users answers to each question
    vector<bool> responses[5]; 
    // *NOTE* Need to always alter both whenever removing a question


    // adds questions to make it easier for programming
    // shouldn't be actually used once running, would have to ask all users 
    void addQuestion(int points, string question){ 
        if(points > 5 || points <= 0){ // just error checking
            cerr << "Error: Questions are only 1 to 5 points.";
        }

        // add question to list 
        qList[points - 1].pushback(question); //(points -1) because array index
        responses[points - 1].pushback(false); // just default to false
    }

    void answerQuestions(){
        // need to go through each index of the array and each question
        int response;
        // tell the user how to answer
        cout << "For the following questions enter 0 for false and 1 for true.\n";

        for(int i = p; p < 5; p++){ // outer loop(points)
            // tell user how much these points are worth
            cout << "\nThese questions are worth " << i + 1 << "points:\n";
            for(int q = 0; i < qList[i].size(); q++){ 
            // go through all questions at this point value(inner loop)
            // print out question for user
                cout << qList[i][q] << endl;
                // ask user for their response
                cin >> response; 
                // update user response
                responses[p][q] = response; 
            }
        }
    }

    /* questions for future:
     If were were to make a scale for the user to answer for each question,
     how would we implement that? 
     Would maybe have to change from boolean to int for the answers if, that's
     the direction we want to go?
    */
    User(string name = "", string gen = "", string favGenre = "", string sched = "", bool competitive = false)
        : username(name), gender(gen), favoriteGenre(favGenre), schedule(sched), isCompetitive(competitive) {}


    //Comparison logic

    bool isCompatibleWith(const User& other) const {
        if (gender != other.gender){
            return false; // different gender
        }
        if (favoriteGenre != other.favoriteGenre){
            return false; // different game
        }
        if (schedule != other.schedule){
            return false; // different schedule
        }
        if (isCompetitive != other.isCompetitive) return false;
        return true; // compatible

    }

    int similarityScore(const User& other ) const {
        int score = 0;
        // check if the non-negotioables match 
        if(!isCompatiblewith(other)){
            return 0; // return 0 since they're noncompatible
        }
        // now go through each question and add up score
        for(int p = 0; p < 5; p++){ //outter loop(point value of each question)
            for(int r = 0; r < responses[p].size(); r++){ // r is response #
                if(this.responses[p][r] == other.responses[p][r]){
                    score += p; // add by point value
                    /// can change to .at() for a more safe access, [] is faster
                }
            }
        }

        return score;
    }
};

#endif