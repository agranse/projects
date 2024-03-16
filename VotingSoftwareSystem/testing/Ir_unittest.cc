#include <gtest/gtest.h>
#include "../src/Ir.h"
#include "../src/IrBallot.h"
#include "../src/Candidate.h"
#include "../src/IrResult.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class IrTest : public ::testing::Test {
    public:
        void SetUp() {
            // candidate1 = Candidate("Abel");
            // candidate2 = Candidate("Billy");
            // candidate3 = Candidate("Candace");

            // candidateList.push_back(candidate1);
            // candidateList.push_back(candidate2);
            // candidateList.push_back(candidate3);

            // candidateList2.push_back(candidate1);
            // candidateList2.push_back(candidate2);

            // rankses.at(2) = 1;
            // ballot1 = IrBallot("Candace", rankses);

            // irVotes.push_back(ballot1);
            // candidate3.setVotes(irVotes); //put back

            // ir = Ir(3, candidateList, 5); // numCandidates, candidateList, numBallots
            // ir2 = Ir(2, candidateList2, 5);
        }

        // void TearDown() {
        //     delete ballot1;
        // }

    protected:
        Candidate candidate1 = Candidate("Abel");
        Candidate candidate2 = Candidate("Billy");
        Candidate candidate3 = Candidate("Candace");
        // vector<Candidate> candidateList{candidate1, candidate2, candidate3};
        // vector<Candidate> candidateList2{candidate1, candidate2};
        // string rankses = ",,2";
        // IrBallot *ballot1 = new IrBallot(",,2");
        // vector<Ballot*> irVotes{ballot1};
        // IrBallot ballot2;
        // Ir ir = Ir(3, candidateList, 5);
        // Ir ir2 = Ir(2, candidateList2, 5);
};

TEST_F(IrTest, IrConstructorTest) {
    IrBallot *ballot1 = new IrBallot(",,2");
    vector<Ballot*> irVotes{ballot1};

    candidate3.setVotes(irVotes);
    vector<Candidate> candidateList{candidate1, candidate2, candidate3};
    Ir ir = Ir(3, candidateList, 5);
    
    EXPECT_EQ(ir.getNumCandidates(), 3);
    EXPECT_EQ(ir.getNumCandidates(), candidateList->size());

    for (int i = 0; i < candidateList->size(); i++) {

        EXPECT_EQ(ir.getCandidates().at(i).getCandidateName(), candidateList->at(i).getCandidateName());
    }
    cout << "here?" << endl;

    // EXPECT_EQ(ir.getCandidates(), candidateList);
    EXPECT_EQ(ir.getNumBallots(), 5);
}

TEST_F(IrTest, RunIrMajorityTest) {
    IrBallot *ballot1 = new IrBallot(",,2");
    vector<Ballot*> irVotes{ballot1};

    candidate3.setVotes(irVotes);
    candidate1.setVoteCount(3);
    candidate2.setVoteCount(1);
    candidate3.setVoteCount(1);

    vector<Candidate> candidateList{candidate1, candidate2, candidate3};
    Ir ir = Ir(3, candidateList, 5);

    ir.runIr();

    // IrResult result = IrResult();
    // result.setWinner(ir.getResults().getWinner());
    // Result result = ir.getResults();
    // Candidate winner = result.getWinner();
    // Candidate winner = ir.getResults().getWinner();
    // cout << "in test, winner: " << ir.getResults().getWinner().getCandidateName() << endl;

    EXPECT_EQ(ir.getCandidates().at(0).getCandidateName(), "Abel");
    // EXPECT_EQ(winner.getName(), "Abel");
    // delete ballot1;
}

TEST_F(IrTest, RunIrPopularityVoteTest) {
    candidate1.setVoteCount(3);
    candidate2.setVoteCount(2);
    vector<Candidate> candidateList2{candidate1, candidate2};
    Ir ir2 = Ir(2, candidateList2, 5);

    ir2.runIr();

    // Result result = ir2.getResults();
    // Candidate winner = result.getWinner();

    // EXPECT_EQ(winner.getName(), "Abel");
    EXPECT_EQ(ir2.getCandidates().at(0).getCandidateName(), "Abel");
}

TEST_F(IrTest, RunIrTieTest) {
    IrBallot *ballot1 = new IrBallot(",,2");
    vector<Ballot*> irVotes{ballot1};

    candidate3.setVotes(irVotes);
    candidate1.setVoteCount(2);
    candidate2.setVoteCount(2);
    candidate3.setVoteCount(1);

    vector<Candidate> candidateList{candidate1, candidate2, candidate3};
    Ir ir = Ir(3, candidateList, 5);

    ir.runIr();

    // Result result = ir.getResults();
    // Candidate winner = result.getWinner();

    string allowedOne =  "Abel";
    string allowedTwo = "Billy";
    string notAllowed = "Candace";
    // string real       =  winner.getName();
    string real       = ir.getCandidates().at(0).getCandidateName();
 
    EXPECT_TRUE (real == allowedOne || real == allowedTwo)
            << "Where real value: "   << real
            << " not equal neither: " << allowedOne
            << " nor: "               << allowedTwo << ".";
    // EXPECT_EQ ((real == allowedOne || real == allowedTwo), true)
    //         << "Where real value: "   << real
    //         << " not equal neither: " << allowedOne
    //         << " nor: "               << allowedTwo << ".";

    EXPECT_NE (real, notAllowed);
}
