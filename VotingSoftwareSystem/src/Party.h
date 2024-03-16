#ifndef PARTY_H
#define PARTY_H

#include "VoteableItem.h"
#include <string>
#include <vector>

/**
 * @brief This class holds party specific information for cpl elections. This
 * includes their votes, candidates, seats won, and seats left over.
**/
class Party : public VoteableItem{
    
    private:
        vector<string> candidateList;
        int initialSeatsWon = 0;
        int finalSeatsWon = 0;
        int initialSeatsExtra = 0;
        int finalSeatsExtra = 0;
        int remainderVotes = 0;

    public:
        /**
<<<<<<< HEAD
         * @brief This is a constructor for the Party class
         * @return A party.
         **/
        Party(){};
        Party(string name, vector<string> candidateList);
        // ~Party();

        vector<string> getCandidateList() {
		    return this->candidateList;
	    }

	    void setCandidateList(vector<string> candidateList) {
		    this->candidateList = candidateList;
	    }

        /**
         * @brief This method is a getter for the initialSeatsWon attribute.
         * @return An integer containing intital seats Won
        **/
        int getInitialSeatsWon() {
            return this->initialSeatsWon;
        };

        /**
         * @brief This method is a setter for the initialSeatsWon attribute.
        **/
        void setInitialSeatsWon(int seatsWon) {
            this->initialSeatsWon = seatsWon;
        };


        // /**
        //  * @brief This method is a getter for the seatsWon attribute.
        //  * @return An integer containing the seats won.
        // **/
        // int getSeatsWon() {
        //     return this->seatsWon;
        // };

        // /**
        //  * @brief This method is a setter for the seatsWon attribute.
        // **/
        // void setSeatsWon(int seatsWon) {
        //     this->seatsWon = seatsWon;
        // };

        // /**
        //  * @brief This method is a getter for the seatsExtra attribute.
        //  * @return An integer containing the number of extra seats.
        // **/
        // int getSeatsExtra() {
        //     return this->seatsExtra;
        // };

        // /**
        //  * @brief This method is a setter for the seatsExtra attribute.
        // **/
        // void setSeatsExtra(int seatsExtra) {
        //     this->seatsExtra = seatsExtra;
        // };
        // /**
        //  * @brief This method is a getter for the finalSeatsWon attribute.
        //  * @return An integer for finalSeatsWon
        // **/
        int getFinalSeatsWon() {
		    return this->finalSeatsWon;
	    };

        /**
         * @brief This method is a setter for the finalSeatsWon attribute.
        **/
        void setFinalSeatsWon(int finalSeatsWon) {
            this->finalSeatsWon = finalSeatsWon;
        };

        /**
         * @brief This method is a getter for the InitialSeatsExtra attribute.
         * @return An integer containing intitalSeatsExtra
        **/
        int getInitialSeatsExtra() {
            return this->initialSeatsExtra;
        };

        /**
         * @brief This method is a setter for the InitialSeatsExtra attribute.
        **/
        void setInitialSeatsExtra(int seatsExtra) {
            this->initialSeatsExtra = seatsExtra;
        };

         /**
         * @brief This method is a getter for the FinalSeatsExtra attribute.
         * @return An integer containing the final seats extra.
        **/
        int getFinalSeatsExtra() {
            return this->finalSeatsExtra;
        };

        /**
         * @brief This method is a setter for the FinalSeatsExtra attribute.
        **/
        void setFinalSeatsExtra(int seatsExtra) {
            this->finalSeatsExtra = seatsExtra;
        };

        /**
         * @brief This method is a getter for the remainderVotes attribute.
         * @return An integer containing the number of remaining votes.
        **/
        int getRemainderVotes() {
            return this->remainderVotes;
        };

        /**
         * @brief This method is a setter for the remainderVotes attribute.
        **/
        void setRemainderVotes(int remainderVotes) {
            this->remainderVotes = remainderVotes;
        };

};

#endif