// class creation for user (for later implementation)
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

random_device rd; // too add the random answers for users
mt19937 gen(rd()); // twister engine
bernoulli_distribution dist(0.5); // 50% for true or false


class User {

public:
    string username, gender, favoriteGenre, schedule;
    bool isCompetitive, isDummy;

    // array for questions
    vector<string> qList[5]; // vector index corresponds to points
    // ex: ?array[1]["Do you like mansplaining?"] That question is one point

    // need a corresponding array for the users answers to each question
    vector<bool> responses[5]; 
    // *NOTE* Need to always alter both whenever removing a question

    // for debugging purposes will make a print list function
    void printQlist(){
        cout << "Printing question list:\n";
        for(int i = 0; i < 5; i++){
            cout << "For " << i + 1 << "points: " << endl;
            for(string question : qList[i]){
                cout << question << endl;
            }
        }
    }



    // adds questions to make it easier for programming
    // shouldn't be actually used once running, would have to ask all users!!! 
    void addQuestion(int points, string question){ 
        if(points > 5 || points <= 0){ // just error checking
            cerr << "Error: Questions are only 1 to 5 points.";
        }

        // add question to list 
        qList[points - 1].push_back(question); //(points -1) because array index
        responses[points - 1].push_back(false); // just default to false
        //printQlist();
    }

    // need to create a default constructor adds randoms answers for questions
    User(string name, string sex, string genre, string date, bool comp, bool human){
        if(human){ // means called for a user not a dummy profile
            username = name;
            gender = sex;
            favoriteGenre = genre; 
            schedule = date;
            isCompetitive = comp;
            isDummy = false;
            return; 
        }
        cerr << "Error with creating this user profile.";
    } 


    void answerQuestions(){
        // need to go through each index of the array and each question
        int response;
        // tell the user how to answer
        cout << "For the following questions enter 0 for false and 1 for true.\n";

        for (size_t p = 0; p < 5; ++p){ // outer loop(points)
            // tell user how much these points are worth
            cout << "\nThese questions are worth " << p + 1 << " point(s):\n";
            for (size_t q = 0; q < qList[p].size(); ++q){ 
            // go through all questions at this point value(inner loop)
            // print out question for user
                cout << qList[p][q] << endl;
                // ask user for their response
                cin >> response; 
                // update user response
                responses[p][q] = response; 
            }
        }
    }

    // fill in the questions for the dummy profiles
    void fillQuestions(){
        for (size_t p = 0; p < 5; ++p){ // outer loop(points)
            for (size_t q = 0; q < qList[p].size(); ++q){ 
            // go through all questions at this point value(inner loop)
            bool randomBool = dist(gen); // generates true or false
                responses[p][q] = randomBool; // puts random value for current
            }
        }
    }

    /* questions for future:
     If were were to make a scale for the user to answer for each question,
     how would we implement that? 
     Would maybe have to change from boolean to int for the answers if, that's
     the direction we want to go?
    */
    User(string name = "", string gen = "", string favGenre = "", string sched = "", bool competitive = false){
        username = name;
        gender = gen;
        favoriteGenre = favGenre; 
        schedule = sched;
        isCompetitive = false;
        isDummy = true;
    }



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

    // calculates simularity score between users
    // changed from "int" to "size_t" because apparently it's used for vectors
    int similarityScore(const User& other ) const {
        int score = 0;
        // check if the non-negotioables match 
        if(!isCompatibleWith(other)){
            return 0; // return 0 since they're noncompatible
        }
        // now go through each question and add up score
        for (size_t p = 0; p < 5; ++p){ //outter loop(point value of each question)
            for (size_t r = 0; r < responses[p].size(); ++r){ // r is response #
                if(responses[p][r] == other.responses[p][r]){
                    score += static_cast<int>(p + 1); // add by point value plus 1(array things)
                    /// can change to .at() for a more safe access, [] is faster
                }
            }
        }
        return score;
    }
};

#endif