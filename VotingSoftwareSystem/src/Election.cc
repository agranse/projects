#include "Election.h"

#include <iostream>
using namespace std;

    Election :: ~Election(){
        delete results;
    }

    string Election::promptForDate(){
        cout << "Please enter date of eletion (MM/DD/YYYY).";
        cin >> date;
        if (date.length() != 10) {                      // check if input is correct length therefore correct format
            date = "Incorrect date format given.";
            return date;
        }
        setDate(date);                                  // set date with input date
        return date;
	}

    int Election::levelTie(int n){
        int result;
        for (int i = 0; i <= 100; i++) {                // randomly choose number 100 times
            result = 1 + (rand() % n);
            cout << result;
        }
        return result;
	}