#include <gtest/gtest.h>
#include "../src/Cpl.h"
#include "../src/Party.h"
#include <iostream>
#include <string>
#include <cmath>

class CplTest : public ::testing::Test {
    public:
        void SetUp( ) {
            // party1 = Party("Democratic");
            // party2 = Party("Republican");
            // party3 = Party("Independent");

            parties.push_back(party1);
            parties.push_back(party2);

            parties2.push_back(party1);
            parties2.push_back(party2);
            parties2.push_back(party3);

            // candidate1 = Candidate(1);
            // candidate2 = Candidate(2);
            // candidate3 = Candidate(3);

            // candidates.push_back(candidate1);
            // candidates.push_back(candidate2);

            // candidates2.push_back(candidate1);
            // candidates2.push_back(candidate2);
            // candidates2.push_back(candidate3);

            // cpl = Cpl(2, parties, 5, 10);  //num parties, parties vector, num seats, num ballots
            // cpl2 = Cpl(3, parties2, 5, 11);
        }

    protected: 
        Party party1 = Party("Democratic");
        Party party2 = Party("Republican");
        Party party3 = Party("Independent");;
        // Candidate candidate1;
        // Candidate candidate2;
        // Candidate candidate3;
        vector<Party> parties;
        vector<Party> parties2;
        // vector<Candidate> candidates;
        // vector<Candidate> candidates2;
        Cpl cpl = Cpl(2, parties, 5, 10);;
        Cpl cpl2 = Cpl(3, parties2, 5, 11);;
};

TEST_F(CplTest, CplConstructorTest) {
    EXPECT_EQ(cpl.getNumParties(), 2);
    for (int i = 0; i < candidateList.size(); i++) {
        EXPECT_EQ(cpl.getParties().at(i).getName(), parties.at(i).getName());
    }
    // EXPECT_EQ(cpl.getParties(), parties);
    EXPECT_EQ(cpl.getNumSeats(), 5);
    EXPECT_EQ(cpl.getNumBallots(), 10);
}

TEST_F(CplTest, RunCpl) {
    //2 parties test, no extras, no remainders
    //cpl 5 seats, 10 ballots
    party1.setVoteCount(6);
    party2.setVoteCount(4);

    party1.setCandidateList(["Jane", "Jill", "Bella"]);
    party2.setCandidateList(["Tom", "Joe"]);

    // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
    cpl.runCpl();
    // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
    EXPECT_EQ(party1.getSeatsWon(), 3);
    EXPECT_EQ(party2.getSeatsWon(), 2);
    // party seats EXtra
    EXPECT_EQ(party1.getSeatsExtra(), 0);
    EXPECT_EQ(party2.getSeatsExtra(), 0);
    // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num

    //2 parties test, extras, no remainders
    //cpl 5 seats, 10 ballots
    party1.setVoteCount(6);
    party2.setVoteCount(4);

    party1.setCandidateList(["Tom", "Joe"]);
    party2.setCandidateList(["Jane", "Jill", "Bella"]);

    // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
    cpl.runCpl();
    // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
    EXPECT_EQ(party1.getSeatsWon(), 3);
    EXPECT_EQ(party2.getSeatsWon(), 2);
    // party seats EXtra
    EXPECT_EQ(party1.getSeatsExtra(), 1);
    EXPECT_EQ(party2.getSeatsExtra(), 0);
    // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num

    //remainder test
    //2 parties test, extras, remainders
    //cpl 5 seats, 10 ballots
    party1.setVoteCount(7);
    party2.setVoteCount(3);

    party1.setCandidateList(["Tom", "Joe"]);
    party2.setCandidateList(["Jane", "Jill", "Bella"]);

    // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
    cpl.runCpl();
    // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
    EXPECT_EQ(party1.getSeatsWon(), 3);
    EXPECT_EQ(party2.getSeatsWon(), 1);
    
    EXPECT_EQ(party1.getSeatsExtra(), 1);
    EXPECT_EQ(party2.getSeatsExtra(), 0);
    // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num
    // not sure how to test to make sure last seat got allocated

    //3 parties test, 2 extra seats
    //cpl2 5 seats, 11 ballots
    party1.setVoteCount(6);
    party2.setVoteCount(4);
    party3.setVoteCount(1);

    party1.setCandidateList(["Jane", "Jill", "Bella"]);
    party2.setCandidateList(["Tom", "Joe"]);
    party3.setCandidateList(["Zach"]);

    // quota variable doesn't exist. Idk how to fix this but probs just use determinequota function inside runcpl
    cpl.runCpl();
    // get results // no cplresult constructor so can't test. Really only could test using display result so probs only test that in CplResult
    EXPECT_EQ(party1.getSeatsWon(), 2);
    EXPECT_EQ(party2.getSeatsWon(), 1);
    EXPECT_EQ(party3.getSeatsWon(), 0);

    EXPECT_EQ(party1.getSeatsExtra(), 0);
    EXPECT_EQ(party2.getSeatsExtra(), 0);
    EXPECT_EQ(party3.getSeatsExtra(), 0);
    // seatsallocated? currently doesn't use allocated variable. If switched shouold test to make sure allocated = total num
    // not sure how to test to make sure last seats got allocated
    // EXPECT_EQ(party1.getSeatsWon() + party2.getSeatsWon() + party3.getSeatsWon(), 5);
}

// TEST_F(CplTest, DetermineQuota) {
//     int expectedOutput;

//     //even % test
//     party1.setVoteCount(4);
//     expectedOutput = 4 / 10; //party votes / total votes

//     EXPECT_EQ(cpl.determineQuota(party1), expectedOutput);
//     EXPECT_EQ(cpl.determineQuota(party1) - expectedOutput, 0);

//     //non even % test
//     party2.setVoteCount(4);
//     expectedOutput = 4 / 11; //party votes / total votes

//     EXPECT_EQ(cpl2.determineQuota(party2), expectedOutput);
//     EXPECT_EQ(cpl2.determineQuota(party2) - expectedOutput, 0);

//     //100% test
//     party1.setVoteCount(10);
//     expectedOutput = 10 / 10; //party votes / total votes

//     EXPECT_EQ(cpl.determineQuota(party1), expectedOutput);
//     EXPECT_EQ(cpl.determineQuota(party1), 1); // might need to change
//     EXPECT_EQ(cpl.determineQuota(party1) - expectedOutput, 0);

//     //0% test
//     party2.setVoteCount(0);
//     expectedOutput = 0 / 11; //party votes / total votes

//     EXPECT_EQ(cpl2.determineQuota(party2), expectedOutput);
//     EXPECT_EQ(cpl2.determineQuota(party2), 0); //might need to change
//     EXPECT_EQ(cpl2.determineQuota(party2) - expectedOutput, 0);
// }

