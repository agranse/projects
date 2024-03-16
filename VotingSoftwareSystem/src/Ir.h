#ifndef IR_H
#define IR_H

#include "Election.h"
#include "Candidate.h"


/**
 * @brief This class extends the abstract election class to hold any ir specific
 * information. This includes candidate information, ballot ranking
 * information, and functionality to remove candidates and determine
 * majority.
**/
class Ir : public Election{

    private:
        int numCandidates;
        vector<Candidate> candidates;

        /**
         * @brief This method iterated through candidates and checks whether
         * a candidate has a majority yet.
         * @return Candidate type that represents the candidate with the majority.
        **/
        Candidate checkForMajority();

        /**
         * @brief This method is used by runIr when no clear majority has been
         * found. It iterates through the candidates and eliminates the
         * candidate with the least number of votes.
        **/
        void eliminateCandidate();

        /**
         * @brief This method takes two candidates and calculates who has the 
         * most votes.
         * @return Winner: Candidate that represents the winner of the popular vote.
        **/
        Candidate runPopularityVote(Candidate x, Candidate y);

        /**
		 * @brief This function will realize displayResults.
		 * It will display the results of the IR election to the terminal.
		*/
	    void displayResults();

    public:
        /**
         * @brief A constructor for the Ir election.
        **/
        Ir(int numCandidates, vector<Candidate> candidateList, int numBallots);
        
        /**
         * @brief This is a driver funtion that holds most of the logic for 
         * running an Ir election. This function calls all other 
         * functions of Ir in order to calculate the election.
        **/
        void runIr();

        /**
         * @brief This is a getter method for the numCandidates attribute.
         * @return An integer containing the number of candidates.
        **/
        int getNumCandidates() {
		    return this->numCandidates;
	    };

        /**
         * @brief This is a setter method for the candidates attribute.
        **/
        vector<Candidate> getCandidates() {
		    return this->candidates;
	    };
};
#endif