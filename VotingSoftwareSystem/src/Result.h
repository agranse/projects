#ifndef RESULT_H
#define RESULT_H
#include "Candidate.h"
#include "Party.h"

/**
 * @brief This class holds information about the result of the election. This
 * holds the functionality to display the results, and is extended by the
 * CplResult and IrResult election specific classes.
**/
class Result {
    
    public:
        /**
         * @brief This is a function that will be overrode by Result's
         * children classes. It will allow for displaying results to the
         * terminal.
        */
        void displayResults(){}
        Candidate getWinner(){}
        vector<Party> getWinners(){}

};



#endif