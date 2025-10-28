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

    }
        
    
};



#endif