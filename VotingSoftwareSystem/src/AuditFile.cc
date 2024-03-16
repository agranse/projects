#include "AuditFile.h"
#include <iostream>
#include <fstream>

// AuditFile :: AuditFile(){
//     auditFileName = "audit_"+promptForFileName();
//     //I am struggling with file stuff here

// }

AuditFile::AuditFile(){}

string AuditFile :: promptForFileName(){
    string date;
    cout << "Enter date of Election: ";
    cin >> date;
    return date;
}

void AuditFile :: createAuditFile(){
    bool cont = true;
    while(cont){
        try {
            cout << "a" << endl;
            //ofstream aFile(auditFileName);
            cout << "b" << endl;
            this->aFile.open(auditFileName, ios::out);
            cont = false;
        }
        catch(...) {
            cout << "Could not open file with filename " << auditFileName << endl;
            cout << "Try again." << endl;
        }
    }  
 }

bool AuditFile :: log(string action){
    aFile << action;
    //error handling
    return true;
}

string AuditFile::finalizeAuditFile(){
    //permissions
    aFile.close();
    return "change this";
}

void AuditFile::displayAuditToUser(){
    cout << getAuditFileName();
    return;
}

