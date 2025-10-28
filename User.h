// class creation for user (for later implementation)
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class User {

public:
    string username, gender, favoriteGenre, schedule;
    bool isCompetitive;

    vector<bool> quizAnswers;
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

        if (gender == other.gender) score++;
        if (favoriteGenre == other.favoriteGenre) score++;
        if (schedule == other.schedule) score++;
        if (isCompetitive == other.isCompetitive) score++;
        return score;

        // note: still same as match, will need to implement questions after
    }
        
    
};



#endif