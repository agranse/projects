#include <gtest/gtest.h>
#include "../src/CplBallot.h"

class CplBallotTest : public ::testing::Test {
    public:
        void SetUp( ) {
            ballot = CplBallot("Democratic"); 
        }

        // void TearDown( ) {
        //     delete ballot;
        //     delete ballot2;
        //     delete ballot3;
        // }

        // ~IrBallotTest( ) {
        //     // cleanup any pending stuff, but no exceptions allowed
        // }

    protected: 
        CplBallot ballot;
};

TEST_F(CplBallotTest, CplBallotConstructorTest) {
    EXPECT_EQ(ballot.getVote(), "Democratic");
}