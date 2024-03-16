#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "VoteableItem.h"


/**
 * @brief This class holds candidate specific information for elections,
 * like the votes for the individual candidate.
 * It is extended from the VoteableItem class.
**/
class Candidate : public VoteableItem {

    private:
        string candidateName;
        string party;
        bool majority = false;
        int candidateID = 0;

    public:
        /**
         * This is a constructor for the Candidate class
         * Parameters: string candidateName
         * Return type: Candidate
        */
        Candidate(){}
        Candidate(string candidateName);
        // ~Candidate();

        /**
         * @brief his is a getter method for CandidateID.
         * @return A string containing the candidateName.
        **/
        string getCandidateName() {
            return this->candidateName;
        }

        /**
         * @brief This is a getter method for the party attribute.
         * @return A string containing the party.
        **/
        string getParty() {
            return this->party;
        }

        /**
         * @brief This is a setter method for the party attribute.
        **/
        void setParty(string party) {
            this->party = party;
        }

        /**
         * @brief This is a getter method for the majority attribute.
         * @return A bool containing the majority.
        **/
        bool isMajority() {
            return this->majority;
        }

        /**
         * @brief This is a setter method for the majority attribute.
        **/
        void setMajority(bool majority) {
            this->majority = majority;
        }

         /**
         * @brief This is a setter method for the candidateID attribute.
        **/
        void setCandidateID(int id){
            candidateID = id;
        }

        /**
         * @brief This is a getter method for the candidateID attribute.
         * @return A string containing the party.
        **/
        int getCandidateID(){
            return candidateID;
        }

};


#endif