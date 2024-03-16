#ifndef VOTEABLEITEM_H
#define VOTEABLEITEM_H

#include "Ballot.h"
#include <vector>

#include <string>
using namespace std;

/**
 * @brief This class holds data about the items that can be voted for like
 * name, type, and a list of associated ballots. This class is extended by
 * the Candidate and Party classes.
**/
class VoteableItem{

    private:
        string name;
        vector<Ballot*> votes;
        int voteCount = 0;

    public:
        /**
         * @brief This is a getter method for the name attribute.
         * @return A string containing the name.
        **/
        string getName() {
            return this->name;
        }

        /**
         * @brief This is a setter method for the name attribute.
        **/
        void setName(string name) {
            this->name = name;
        }

        /**
         * @brief This is a getter method for the votes attribute.
         * @return A vector<Ballot> object containing the votes.
        **/
        vector<Ballot*> getVotes() {
            return this->votes;
        }

        /**
         * @brief This is a setter method for the votes attribute.
        **/
        void setVotes(vector<Ballot*> votes) {
            this->votes = votes;
        }

        /**
         * @brief This is a getter method for the voteCount attribute.
         * @return An integer containing the voteCount.
        **/
        int getVoteCount() {
            return this->voteCount;
        }

        /**
         * @brief This is a setter method for the voteCount attribute.
        **/
        void setVoteCount(int voteCount) {
            this->voteCount = voteCount;
        }

};

#endif