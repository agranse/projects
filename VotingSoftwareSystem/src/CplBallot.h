#ifndef CPLBALLOT_H
#define CPLBALLOT_H
#include "Ballot.h"


/**
 * @brief This class holds cpl elecction specific ballot information,
 * mainly the party voted for in the ballot.
**/
class CplBallot : public Ballot{

    public:
        /**
         * @brief This is a constructor for the Cpl class
         * @return A CplBallot.
        **/
        CplBallot(string vote);
        CplBallot(){}

    void setCurrentRank(int currentRank){}
    int getCurrentRank(){}
    vector<string> getRanks(){}
};

#endif