#include "Cpl.h"
#include "CplResult.h"

#include <cmath>
#include <string>
#include <limits>
// using namespace std;
#include <iostream>
using namespace std;

void Cpl :: runCpl() {
    // audit: log running cpl
    for (int i = 0; i< parties.size(); i++) {
        cout << endl;
        cout << parties[i].getName() << endl;
        
        //assign initial seats via quota
        int quota = determineQuota(parties[i]);

        //if the seats about to be allocated are less than the seats available, allocate them
        if((parties[i].getVoteCount() / quota) < (numSeats - getAllocatedSeats())){
            //initial used for testing purposes
            parties[i].setInitialSeatsWon((parties[i].getVoteCount() / quota));          // determine the seats for each party
            //final to be changed in algorithm
            parties[i].setFinalSeatsWon((parties[i].getVoteCount() / quota));          // determine the seats for each party
            cout << "initial seat selection = " << parties[i].getFinalSeatsWon() << endl;
        }
        // set variables to be used later in loop
        string name = parties[i].getName();
        int seats = parties[i].getInitialSeatsWon();
        int lengthList = parties[i].getCandidateList().size();

        //keep track of how many seats have been allocated / given away
        // int seatsAllocated += (seats - parties[i].getSeatsExtra());
        //setAllocatedSeats(getAllocatedSeats() + (seats - parties[i].getFinalSeatsExtra()));
        setAllocatedSeats(seats + getAllocatedSeats());
        // audit: log allocated seats

       // cout << "allocated seats before remainders = " << getAllocatedSeats() << endl;

        // cout << "seats = " << seats << endl;
        // cout << "lengthList = " << lengthList << endl;

        //auditfile.log(name + " won " + seats + " seats\n");

        if ((seats*quota) < lengthList) {

            parties[i].setRemainderVotes(parties[i].getVoteCount() - (parties[i].getFinalSeatsWon() * quota));
            cout << "remaining votes = " << parties[i].getRemainderVotes() << endl;
            // audit: log remaining votes
           
            // //initial used for testing purposes
            // parties[i].setInitialSeatsExtra(lengthList - seats);                                       // determine if the party has extra seats and set it
           
            // cout << "extra seats = " << parties[i].getInitialSeatsExtra() <<endl;

            // //final to be changed in algorithm           
            // parties[i].setFinalSeatsExtra(seats - lengthList);                                       // determine if the party has extra seats and set it

        }
       
    }

    if ((getNumSeats() - getAllocatedSeats()) != 0) {
        determineSeatAllocation();
    }

    // if there are extra seats, distribute them amongst the party -- i don't think this ever happens
    for (int i =0; i < parties.size(); i++) {
        if (parties[i].getFinalSeatsExtra() > 0) {
            distributeRemainderSeats(parties[i]);
            // audit: log distribute remainder seats
        }
    }
    cout << parties.size() << endl;

    CplResult r = CplResult();
    setResults(r);
    r.setWinners(parties);  
    // audit: log winners  

    cout << "size of winners = " << r.getWinners().size() <<endl;

    cout << "cpl done" << endl;        

    
}


float Cpl :: determineQuota(Party party) {        // either change to float(probably) or a percentage
    //quota = total number of votes / total number of seats available
    cout << getNumBallots() << " / " << numSeats << " = " << (getNumBallots()/numSeats) << endl;
    // audit: log quota
    return (getNumBallots()/numSeats);
   
    //previous code -- I think this is incorrect (not deleting until I am certain)
    //cout << (float)party.getVoteCount() << " / " << (float)getNumBallots() << " = " << ((float)party.getVoteCount() / (float)getNumBallots()) << endl;
    //return ((float)party.getVoteCount() / (float)getNumBallots());
}

void Cpl :: determineSeatAllocation() {                         // this is a struggle
    
    //the number of parties which are tied in that highest vote (se)
    int maxCount;

    //auditfile.log("Allocating remaining seats with Largest Remainder Formula\n");
    
    int max = (numeric_limits<int> :: infinity()) * (-1);       // assign -infinity
    int i = getNumSeats() - getAllocatedSeats();    // i = the number of seats remaining to be allocated
    cout << "i = " << i <<endl;
    while (i != 0) {
        int maxIndex = -1;
        for (int j =0; j< parties.size(); j++) {
            if ((parties[j].getRemainderVotes()) > max) {

                //the highest number of votes
                max = parties[j].getRemainderVotes();

                //now no tie in highest votes -- new high was found
                maxCount = 0;
            }
        }

        //parties with the same number of remaining votes (tie)
        vector<Party> maxDuplicates;
        for (int k = 0; k < parties.size(); k++) {
            if (parties[k].getRemainderVotes() == max) {    //find the parties with the highest vote count
                maxCount ++;    //# of parties tied at max votes
                cout << "max count = " << maxCount <<endl;
                maxDuplicates.push_back(parties[k]);    
            }
        }

        // if the # of parties with max votes is less than or equal to the # of seats left to be allocated
        if( maxCount <= i ){
            for( int k = 0; k < parties.size(); k++ ){
                if( parties.at(k).getRemainderVotes() == max ){
                    parties.at(k).setFinalSeatsWon(parties.at(k).getFinalSeatsWon() + 1);
                    parties.at(k).setRemainderVotes(0);
                    setAllocatedSeats(1 + getAllocatedSeats());
                   
                }
            }
            i = i - maxCount; // i updated to have the number of seats left to be allocated
            maxCount = 0;
            max = (numeric_limits<int> :: infinity()) * (-1);       // assign -infinity

        }
        else if (maxCount > i) {    //if there are more parties tied than there are seats available
            cout << "tie breaker" << endl;
            cout << "max count = " << maxCount;
            int tb = levelTie(maxCount);
            cout << " tb = " << tb << endl;

            maxCount = 0;
            cout << "won tie -- " << tb << " : " << maxDuplicates[tb-1].getName() << endl;

            for( int k = 0; k < parties.size(); k++ ){
                if( parties.at(k).getName() == maxDuplicates.at(tb-1).getName() ){
                    parties[k].setFinalSeatsWon(maxDuplicates[tb-1].getFinalSeatsWon() + 1);
                    setAllocatedSeats(getAllocatedSeats() + 1);
                }
            }
            i--;
            // audit: log ?
            //maxDuplicates[tb].setFinalSeatsWon(maxDuplicates[tb].getFinalSeatsWon() + 1);

            //auditfile.log(maxDuplicates[tb].name + " won +1 seat\n");
        }
        // else {
        //     // auditfile.log(parties[maxIndex].name + " +1 seat\n");
        //     parties[maxIndex].setFinalSeatsWon(parties[maxIndex].getFinalSeatsWon() + 1);
        // }
        //i--;
    }
            cout << "allocated seats after remainders = " << getAllocatedSeats() << endl;
    displayResults();

}

//what is this function doing? -- I am not sure this is ever hit / used
void Cpl :: distributeRemainderSeats(Party party) {
   // audit: log("distributing "+ party.getFinalExtraSeats() + " extra seats from " + party.getName() + " to eligible parties.\n");
    //cout << "here" << endl;
    while (party.getFinalSeatsExtra() > 0) {
        vector<Party> eligibleParties;
        for (int i = 0; i< parties.size(); i++) {
            if ((parties[i].getName() != party.getName()) && (parties[i].getFinalSeatsWon() > 0) && ((parties[i].getFinalSeatsExtra()) - parties[i].getFinalSeatsWon()) > 0) {
                eligibleParties.push_back(parties[i]);
            }                                                               // does length(parties[i].candidateList) work?? pseudocode says
                                                                            // do length(parties[i].candidates) but candidates does not exist
        }
        int n = levelTie(eligibleParties.size()) ;
        eligibleParties[n].setFinalSeatsWon(eligibleParties[n].getFinalSeatsWon()+1);
        // audit: log(eligibleParties[n].name + " +1 seat\n");
        party.setFinalSeatsExtra(party.getFinalSeatsExtra() - 1);
        // audit: log final extra seats
    }
}

void Cpl :: displayResults() {
    // audit: log this?
    cout << "----------------------" << endl;
        cout << "Election results:\n";
        cout << "Type of Election: Closed Party List\n";
        cout << "Number of ballots cast: " << getNumBallots()<< endl;
        cout << "Number of seats: " << getNumSeats() << endl;
        cout << endl;
        cout << "Election Results: " << endl;
        for (int i =0; i< parties.size(); i++) {
            cout << parties.at(i).getName() + ": ";
            for (int k = 0; k<parties.at(i).getCandidateList().size(); k++) {
                cout << parties.at(i).getCandidateList().at(k) << ", ";
            }
            cout << endl;
            cout << "---------" << endl;
            cout << "Number of seats awarded party: " << parties.at(i).getFinalSeatsWon() << endl;
            //cout << "Number of allocated seats: " << this->getAllocatedSeats() << endl;
            cout << "Elected candidates of each party: ";
            for (int l = 0; l< parties.at(i).getFinalSeatsWon(); l++) {
                cout << parties.at(i).getCandidateList().at(l) << ", ";
            }
            cout << endl;
            cout << endl;
        }
        cout << "----------------------" << endl;
    }