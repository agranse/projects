#include "IrBallot.h"
#include <vector>
#include <sstream>

    
    // A helper function to split a string by "," character.
   // A helper function to split a string by "," character.
vector<string> splitByComma2(string str){
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

    IrBallot :: IrBallot(string vote){
        this->ranks = splitByComma2(vote);
        
    }