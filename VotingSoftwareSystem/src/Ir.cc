#include "Ir.h"
#include "IrResult.h"
#include "IrBallot.h"
#include "Candidate.h"
#include <limits>
#include <iostream>
#include <vector>
#include<bits/stdc++.h>

#include "Scanner.h"        // might cause issues

#include <string>
using namespace std;

// global candidates for display
IrResult r = IrResult();
vector<Candidate> OGcandidates;

// A helper function to split a string by "," character.
vector<string> IrSplitByComma(string str){
    vector<string> temp;
    string delimiter = ",";
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        temp.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    temp.push_back(str);
    return temp;
}

Ir :: Ir(int numCandidates, vector<Candidate> candidates, int numBallots){
    this->numCandidates = numCandidates;
    this->candidates = candidates;
    OGcandidates = candidates;
    setNumBallots(numBallots);
}

void Ir :: runIr(){
    cout << "Testing, made it to runIR" << endl;
    // audit: log running ir
    auditFile.log("Running IR Election.");

    while(checkForMajority().getCandidateName() == "bad"){
        eliminateCandidate();
    }
    cout << "eliminated candidates" << endl;
    
    setResults(r); //.setWinner(candidates.at(0))
    r.setWinner(candidates.at(0));
    displayResults();
    auditFile.log("IR Election complete.");
    cout << "ir done" << endl;
}

Candidate Ir :: checkForMajority(){
    auditFile.log("Checking for majority.");
    cout << "Inside checkMajority" << endl;
    //loop through all candidates
    for( int i = 0; i < candidates.size(); i++ ){
        //if the ammount of votes for a certain candidate is more than half of the ballots, set that candidate as winning the majority
        if( candidates.at(i).getVotes().size() / getNumBallots() > 0.5) { 
            candidates.at(i).setMajority(true);
            auditFile.log("Majority found: " + candidates.at(i).getCandidateName());
            return candidates.at(i);
        }  
    }
    //if no majority was found and there are two candidates remaining, run a popularity vote
    if(candidates.size() == 2){
        return runPopularityVote(candidates.at(0), candidates.at(1));
    }

    return Candidate("bad");
}

//this function is a mess
//are loops correct? or are they nested?
void Ir :: eliminateCandidate(){
    // audit: log eliminating candidate
    cout << "Inside eliminateCandidate() " << endl;
    int min = 0x7FFFFFFF;       // assign infinity
    int minIndex = 0;
    Candidate targetCandidate;
    int length = 0;        //used to hold the length of the votes for a certain candidate.
    int targetCandidateIndex;
    for(int i = 0; i< candidates.size(); i++){  
        cout << "eliminateCandidate() forloop 1" << endl;   //iterate through the candidate vector
        length = candidates[i].getVotes().size();
        //if the number of votes for a certain candidate is less than the minimum
        if ( length < min){ 
            cout << "eliminateCandidate() if 1" << endl;
		    //then set the minumum to that number of votes, and the minIndex to the index of that candidate
            min = length; //<< correct logic
		    minIndex = i;
            // audit: log eliminated candidate
        }
    }
    int minCount = 0;

    vector<Candidate> minDuplicates; //array to hold candidates in a tie
    for( int j = 0; j< candidates.size(); j++){
        cout << "eliminateCandidate() forloop 2" << endl; 
        //if the number of votes for a certain candidate equals the minumum
        if(candidates[j].getVotes().size() == min){
            cout << "eliminateCandidate() if 2" << endl;
            //then add that candidate to minDuplicates
            minDuplicates.push_back(candidates.at(j));
            minCount++;
            // audit: log eliminated candidate
        }
    }
    if(minCount > 1){ //if there is a tie, level it, the winner becoming the targetCandidate
        cout << "eliminateCandidate() if 3" << endl;
        targetCandidateIndex = levelTie(minCount);
        targetCandidate = minDuplicates[targetCandidateIndex];
        // audit: log tie
        // audit: log eliminated candidate
    }
    else{
        cout << "eliminateCandidate() else 1 - 3" << endl;
        targetCandidateIndex = minIndex;
        targetCandidate = candidates[minIndex];
    }
    vector<Ballot*> targetVotes = targetCandidate.getVotes();


    if (targetVotes.size() != 0){
        cout << "eliminateCandidate() if 4" << endl;
        while( targetVotes.size() != 0 ){ //while there are still votes
            for( int k = 0; k < targetVotes.size(); k++){ //moving through the targetVotes vector
            cout << "eliminateCandidate() forloop 3" << endl; 
                //increase the rank of each vote
                targetVotes.at(k)->setCurrentRank((targetVotes.at(k)->getCurrentRank())+1);
                string currentRank = to_string((targetVotes.at(k)->getCurrentRank())+1); 
                vector<string> targetRanks = targetVotes.at(k)->getRanks(); 
                // find index of current rank. -1 if not found
                int index = -1;
                for (int i= 0; i < targetRanks.size();i++){
                    cout << "eliminateCandidate() forloop 4" << endl; 
                    // audit: log eliminated candidate ?
                    if (targetRanks[i] == currentRank){
                        cout << "eliminateCandidate() if 5" << endl;
                        // audit: log eliminated candidate ?
                        index = i;
                    }
                }
                if (index != -1){
                    cout << "eliminateCandidate() if 6" << endl;
                    // audit: log eliminated candidate ?
                    //if new rank exist, iterate through remaining candidates to determine if ballot
                    //is still alive. 
                    for (int j = 0; j < candidates.size(); j++){
                        cout << "eliminateCandidate() forloop 5" << endl; 
                        // audit: log eliminated candidate ?
                        if (candidates[j].getCandidateID() == index){
                            cout << "eliminateCandidate() if 7" << endl;
                            // audit: log eliminated candidate ?

                            //Candidate is still in the election and the ballot is still alive.
                            //Add ballot to Candidate[j].
                            vector<Ballot*> tempBallots = candidates[j].getVotes();
                            tempBallots.push_back(targetVotes.at(k));
                            candidates[j].setVotes(tempBallots);
                            //Delete ballot from targetCandidate
                            targetVotes.erase(targetVotes.begin()+k);
                        }
                    }
                } else {
                    cout << "eliminateCandidate() else 2 - 6" << endl;
                    // Ballot is dead
                    // WE MAY NEED TO MOVE THIS BALLOTS TO A "DEAD-BALLOT" ARRAY TO LOG RESULTS
                    targetVotes.erase(targetVotes.begin()+k);
                }
            }
        }
    }

    candidates.erase(candidates.begin()+targetCandidateIndex);
    //     //audit log
    //     candidates.at(0).setVoteCount(candidates.at(0).getVoteCount() - 1);
    // }

}



Candidate Ir :: runPopularityVote(Candidate candidate1, Candidate candidate2){
    // audit: log running popularity vote

    //if the number of votes in candidate 1 is equal to that of candidate 2 (dead tie)
    if(candidate1.getVotes().size() == candidate2.getVotes().size()){ 
	    //then level the tie
        if(levelTie(2) == 1){ 
		    // audit: log winner of tie
            return candidate1;
        }
	    else{
		    // audit: log winner of tie
            return candidate2;
        }
    }
    //if candidate 1 had more votes than candidate 2
    else if(candidate1.getVotes().size() > candidate2.getVotes().size()){
	    //then candidate 1 wins

        // audit: log winner of tie
	    return candidate1;
    }
    else{ //if candidate 2 has more votes than candidate 1
        //then candidate 2 wins
        
	    // audit: log winner of tie
        return candidate2;
    }
}

void Ir :: displayResults() {
    cout << "Election results:" << endl;
    cout << "Type of Election: Instant Runoff" << endl;
    cout << "Number of ballots cast: ";
    cout << getNumBallots() << endl;
    cout << "Candidates:" << endl;
    for (int i  = 0; i < getNumCandidates(); i++) {
        cout << OGcandidates[i].getCandidateName() << endl;
        // audit: log display
        cout << "Votes: ";         // how to get the initial list here
        cout << OGcandidates[i].getVotes().size() << endl;
        // audit: log display votes
        cout << "Percentage: ";
        float percentage = 100 * (float(OGcandidates[i].getVotes().size()) / float(getNumBallots()));
        cout << percentage;
        // audit: log display percentage
        cout << "%" << endl;
    }
    cout << "Winner: "; // how to get the winner? It's set in runIR but only there
    cout << r.getWinner().getCandidateName() << endl;
    // audit: log winner ?
}


