#ifndef CPL_H
#define CPL_H

#include "Election.h"
#include "Party.h"
#include <vector>

/**
 * @brief This class entends the abstract election class to hold any cpl specific
 * information. This includes party information, seat information, and
 * functionality to allocate and determine seats.
**/
class Cpl : public Election{

    private:
        int numParties;
        vector <Party> parties;
        int numSeats;
        int allocatedSeats = 0;

        /**
         * @brief This method is used to determine the quota that will be used
         * by the runCpl function.
         * @return a Float containing the quota for the party.
        **/
        float determineQuota(Party party);

        /**
         * @brief This method will be run after the initial seat allocation round
         * is done in runCil. This method will allocate any leftover seats
         * that have not been allocated to a party yet. It will use the
         * Largest Remainder Formula as the logic behind this method.
        **/
        void determineSeatAllocation();

        /**
         * @brief This method is used when a party has won more seats than the
         * number of candidates in the party. The remaining seats are 
         * distributed to parties with open seats by a lottery.
        **/
        void distributeRemainderSeats(Party party);

        /**
		 * @brief This function will realize displayResults.
		 * It will display the results of the CPL election to the terminal.
		*/
	    void displayResults();

    public:
        /**
         * @brief A constructor for the Cpl party / class.
        **/
        Cpl(int numParties, vector <Party> parties, int numSeats, int numBallots){
            this->numParties = numParties;
            this->parties = parties;
            this->numSeats = numSeats;
            for(int i = 0; i < numParties; i++){
                this->parties.at(i).setVoteCount(parties.at(i).getVotes().size());
            }
            setNumBallots(numBallots);
        }
        
        //  /**
        //  * This function will realize displayResults.
        //  * It will display the results of the CPL election to the terminal.
        //  * Parameters: None
        //  * Return Type: Void
        // */
        // void displayResults();


        /**
         * @brief This is a driver function that holds most of the logic for running
         * a cpl election. This function calls all other functions of Cpl in
         * order to calculate the election. Creates a Result object with
         * calculated election data.
        **/
        void runCpl();

        /**
         * @brief This method is a getter for numParties.
         * @return An integer containing the number of Parties.
        **/
        int getNumParties() {
            return this->numParties;
        }

        /**
         * @brief This method is a setter for numParties.
        **/
        void setNumParties(int numParties) {
            this->numParties = numParties;
        }

        /**
         * @brief This method is a getter for parties.
         * @return A vector<Party> of the parties.
        **/
        vector<Party> getParties() {
            return this->parties;
        }

        /**
         * @brief This method is a setter for parties.
        **/
        void setParties(vector <Party> parties) {
            this->parties = parties;
        }

        /**
         * @brief This method is a getter for numSeats.
         * @return An integer containing the number of seats.
        **/
        int getNumSeats() {
            return this->numSeats;
        }

        /**
         * @brief This method is a setter for numSeats.
        **/
        void setNumSeats(int numSeats) {
            this->numSeats = numSeats;
        }

        /**
         * @brief This method is a getter for allocatedSeats.
         * @return An integer containing the number of allocated seats.
        **/
        int getAllocatedSeats() {
		    return this->allocatedSeats;
	    }

        /**
         * @brief This method is a setter for allocatedSeats.
        **/
	    void setAllocatedSeats(int allocatedSeats) {
		    this->allocatedSeats = allocatedSeats;
	    }

};

#endif