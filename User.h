// class creation for user (for later implementation)
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;


class User {

public:
    string username;
    vector<bool> quizAnswers;

    User(string name = "") {
        username = name;
    }

    //Add answer function to append vector
    void addAnswers(bool answer){
        quizAnswers.push_back(answer);
    }


    bool operator==(const User& other) const{
        return (quizAnswers == other.quizAnswers);
    }

    int getTotalResponses() const {
        return quizAnswers.size();
    }

}



#endif