#ifndef AUDITFILE_H
#define AUDITFILE_H

#include <string>
using namespace std;

#include <fstream>

/**
 * @brief This class holds the information related to the audit file, created to keep
 * track of how the election progressed and how the winner was declared.
**/
class AuditFile{

    private:
        string auditFileName;
        ofstream aFile;
        
    public:

        AuditFile();

        /**
         * @brief Prompt user for the election date. This information is needed
         * to name the audit file.
         * @return string of date
        **/
        string promptForFileName();

        /**
         * @brief Using the file name created from user input, create a FILE.
         * Permissions should be write-only at this point.
        **/
        void createAuditFile();

        /**
         * @brief To be called at the end of most voting algorithm processes.
         * This function will take a string describing the action just completed,
         * for example how many votes a specific candidate had, and write that string to
         * the audit file in sequence.
         * @return Bool if success or fail
        **/
        bool log(string action);

        /**
         * @brief Close the file. Change permissions of the audit file to read-only
         * for delivery of the file to the user.
         * @return String of audit file name to access
        **/
        string finalizeAuditFile();

        /**
         * @brief Deliver the file to the user at the completion of the election.
        **/
        void displayAuditToUser();

        /**
         * @brief Getter for Audit File name.
         * @return String for audit file name.
        **/
        string getAuditFileName() {
		    return this->auditFileName;
	    }

        /**
         * @brief Setter for Audit File name.
        **/
        void setAuditFileName(string name) {
            this->auditFileName = name;
        }


};

#endif
