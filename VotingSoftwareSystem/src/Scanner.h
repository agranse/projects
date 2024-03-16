#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include "Election.h"
#include "AuditFile.h"
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief This class holds the functionality to read the input file with the 
 * election information that is provided when the program is run.
**/
class Scanner{
    public:
    Scanner() {};
    Scanner(string filename);
    //AuditFile auditFile = AuditFile();

    /**
    * @brief This function prompts the user for a filename that will be used by
    * openFile to open the inputfile.
    * @return A string of the filename.
    **/
    string promptForFile();

    /**
    * @brief This function prompts the user for the election type that will be
    * used by getElection().
    * @return A string of the election type.
    **/
    string promptForElectionType();

    /**
    * @brief This function prompts the user for the number of seats that are
    * available for a cpl election. 
    * @return An int that represents the number of avaiable seats.
    **/
    int promptForNumSeats();

    /**
    * @brief This function prompts the user for the number of Candidates
    * that will be in the election. 
    * @return An int that represents the number of candidates in the
    * election.
    **/
    int promptForNumCandidates();

    /**
    * @brief This function uses promptForFileName() to get a filename and uses
    * that filename to attempt to open an input file. This function will call
    * promptForFileName again if it can not open an inputfile. The input file
    * will be place in the inputFile field.
    **/
    void openFile();

    /**
    * @brief This function will determine which type of election data is held
    * in the input file and then attempts to parse that input file. After the
    * input file is parsed, the 
    **/
    void parseFile();

    /**
    * @brief This function verifies with the user that the type of election
    * currently held in the election field is the type of election the user
    * wants to parse.
    * @return A string with the confirmation (YES or NO).
    **/
    string promptForConfirmType();

     /**
    * @brief Getter for the election field.
    * @return A Election type that represents the election to be run.
    **/
    Election* getElection();

    private:
        void irParse();
        void cplParse();

        Election* election;
        string filename = "NOFILE";
        ifstream inputFile;
        string electionType;
        int numSeats;
        int numBallots;
        int numCandidates;
};
#endif