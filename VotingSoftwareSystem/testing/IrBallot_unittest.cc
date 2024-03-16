#include <gtest/gtest.h>
#include "../src/IrBallot.h"
#include <vector>

class IrBallotTest : public ::testing::Test {
    public:
        void SetUp( ) {
            // ballot = IrBallot("1,2,5");
        }

        // void TearDown( ) {
        //     delete ballot;
        // }

        // ~IrBallotTest( ) {
        //     // cleanup any pending stuff, but no exceptions allowed
        // }

    protected: 
        IrBallot *ballot = new IrBallot("1,2,5");
};

TEST_F(IrBallotTest, IRBallotConstructorTest) {
    vector<string> ranks; // = {1, 2, 5};
    ranks.push_back("1");
    ranks.push_back("2");
    ranks.push_back("5");
    EXPECT_EQ(ballot->getRanks(), ranks);
    EXPECT_EQ(ballot->getCurrentRank(), 0);
    ballot->setVote("Steve");
    EXPECT_EQ(ballot->getVote(), "Steve");
}