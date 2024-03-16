#ifndef IRRESULT_H
#define IRRESULT_H

#include "Result.h"
#include "Candidate.h"

/**
 * @brief This class holds ir election specific result information, namely
 * a single winning candidate.
**/
class IrResult : public Result {

    private:
        Candidate winner;

    public:
	
		// IrResult();

		/**
		 * @brief This is a getter method for the winner attribute.
		 * @return A candidate type containing the winner of the election.
		**/
        Candidate getWinner() {
		    return this->winner;
	    };

		/**
		 * @brief This is a setter method for the winner attribute.
		**/
	    void setWinner(Candidate winner) {
		    this->winner = winner;
	    };

};

#endif