#ifndef ELECTION_H
#define ELECTION_H

#include "Ballot.h"
#include "Result.h"
#include "AuditFile.h"

#include <string>
using namespace std;

#include <vector>

/**
 * @brief This class holds all election data for easier allocation to other classes.
 * This includes any data read from the input file, and any data to be
 * saved to the audit file, and results information. This class is 
 * extended by the Cpl and Ir calsses.
*/
class Election {
    private:
        string electionType, csvFileName, date;
        Result *results;
        int numBallots;
        vector<Ballot> ballots;

    

    public:
		AuditFile auditFile; // = AuditFile();
		~Election();

		/**
		 * @brief This method is used to prompt the user for date of the election.
		 * @return String with the date
		**/
        string promptForDate();

		/**
		 * @brief This method is used to level ties by picking a random number out from a chosen range of numbers.
		 * @return Int with result of tie
		**/
        int levelTie(int n);

		/**
		* @brief This method is used as a getter for the electionType:String field.
		* @return A string with the election type	
		**/
    	string getElectionType() {
			return this->electionType;
		}

		/**
		 * @brief This method is used as a setter for the electionType:String field.
		**/
		void setElectionType(string electionType) {
			this->electionType = electionType;
		}

		/**
		 * @brief This method is used as a getter for the csvFileName.
		 * @return A string with the csvFileName
		**/
		string getCsvFileName() {
			return this->csvFileName;
		}

		/**
		 * @brief This method is used as a setter for the csvFileName.
		**/
		void setCsvFileName(string csvFileName) {
			this->csvFileName = csvFileName;
		}

		/**
		 * @brief This method is used as a getter for the date.
		 * @return A string of the date.
		**/
		string getDate() {
			return this->date;
		}

		/**
		 * @brief This method is used as a setter for the date.
		**/
		void setDate(string date) {
			this->date = date;
		}

		/**
		 * @brief This method is used as a getter for the results:&Results field.
		 * @return A Result object containing the results.
		**/
		Result getResults() {
			return *results;
		}

		/**
		 * @brief This method is used as a setter for the results:&Results field.
		*/
		void setResults(Result r) {
			*results = r;
		}

		/**
		 * @brief This method is a getter for numBallots.
		 * @return An integer containing the numBallots.
		**/
		int getNumBallots() {
			return this->numBallots;
		}

		/**
		 * @brief This method is a setter for numBallots.
		**/
		void setNumBallots(int numBallots) {
			this->numBallots = numBallots;
		}

		/**
		 * This method is a getter for the auditfile.
		*/
		// AuditFile getAuditfile() {
		// 	return this->auditFile;
		// }

		// /** This method is a setter for the auditfile.*/
		// void setAuditfile(AuditFile auditfile) {
		// 	this->auditFile = auditfile;
		// }

		/**
		 * @brief This method is a getter for Ballot.
		 * @return A vector Ballot
		*/
		vector<Ballot> getBallot() {
			return this->ballots;
		}

		/**
		 * @brief This method is a setter for Ballot.
		*/
		void setBallot(vector<Ballot> ballots) {
			this->ballots = ballots;
		}

		virtual void runIr(){}
		virtual void runCpl(){}

};

#endif 