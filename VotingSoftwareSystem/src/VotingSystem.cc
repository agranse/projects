#include <iostream>
#include "Scanner.h"
using namespace std;

int main(int argc, char* argv[]) { 
    Scanner scan;
    // convert type char* arguments into type string arguments.
    // String type arguments stored in args[]
    vector<string> args(argc);     
        for (int i = 0; i < argc; ++i){
            args[i] = argv[i];
    }
    
    if (argc > 1){
        scan = Scanner(args.at(1)); 
    } else {
        scan = Scanner();
    }
    scan.openFile();
    scan.parseFile();
    // cout << scan.StringToUpper("yo there") << endl;

    // // IR election
    if (scan.getElection()->getElectionType() == "IR") {
        cout << "run ir" <<endl;
        scan.getElection()->runIr();
    }

    // // CPL election
    if (scan.getElection()->getElectionType() == "CPL") {
        cout << "run cpl" << endl;
        scan.getElection()->runCpl();
    }
}