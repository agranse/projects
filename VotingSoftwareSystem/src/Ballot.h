#ifndef BALLOT_H
#define BALLOT_H

#include <vector>
#include <string>
using namespace std;

/**
 * @brief This class holds all data for each individual ballot.
 * It is extended by the cplBallot and irBallot classes.
*/
class Ballot{

    private:
        string vote;

    public:
        /**
         * @brief This is a getter for the vote attribute.
         * @return A string of vote.
        */
        string getVote() {
            return this->vote;
        }

        /**
         * @brief This is a setter for the vote attribute.
        */
        void setVote(string vote) {
            this->vote = vote;
        }

        virtual void setCurrentRank(int currentRank){}
        virtual int getCurrentRank(){}
        virtual vector<string> getRanks(){}



};

#endif