#ifndef IRBALLOT_H
#define IRBALLOT_H

#include <iostream>
#include <vector>
#include "Ballot.h"

#include <string>
using namespace std;

/**
 * @brief This class holds ir election specific ballot information. This includes
 * the rankings for the ballot, the current rank, as well as the current
 * voted candidate.
**/
class IrBallot : public Ballot{

    private:
        vector<string> ranks;
        int currentRank = 0;

    public:

        /**
         * @brief This is a constructor for the IrBallot class.
         * @return The IrBallot.
        */
        IrBallot(string vote);
        IrBallot(){
            currentRank = 0;
        }


        /**
         * @brief This is a setter method for the ranks attribute.
        */
        void setRanks(vector<string> ranks) {
            this->ranks = ranks;
        }

        /**
         * @brief This is a getter method for the ranks attribute.
         * @return An integer containing the ranks of candidates.
        */
        vector<string> getRanks() {
            return this->ranks;
        }

        /**
         * @brief This is a getter for the currentRank attribute.
         * @return An integer containing the current rank.
        **/
        int getCurrentRank() {
            return this->currentRank;
        };

        /**
         * @brief This is a setter method for the currentRank attribute.
        **/
        void setCurrentRank(int currentRank) {
            // cout << "inside setCurrentRank, rank = " << currentRank << endl;
            this->currentRank = currentRank;
        };
};

#endif