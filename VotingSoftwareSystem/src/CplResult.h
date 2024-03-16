#ifndef CPLRESULT_H
#define CPLRESULT_H

#include "Result.h"
#include "Party.h"
#include <vector>


/**
 * @brief This class holds cpl election specific reult information. This
 * includes a list of the winning parties, and the Party class can be 
 * used for the seat allocation for each group.
**/
class CplResult : public Result {

    private:
        vector<Party> winners;


    public:

       /**
        * @brief This is a getter method for the winners attribute
        * @return The winners within the party
       */
        vector<Party> getWinners() {
		    return this->winners;
	    };

        /**
        * @brief This is a setter for the winners attribute
        */
	    void setWinners(vector<Party> winners) {
		    this->winners = winners;
	    };

};
#endif