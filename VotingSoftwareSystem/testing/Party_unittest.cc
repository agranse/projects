#include <gtest/gtest.h>
#include "../src/Party.h"

class PartyTest : public ::testing::Test {
    public:
        void SetUp( ) {
            // party = Party(); // ("Democratic", {"Steve", "Brenda"}); 
            party.setName("Democratic");
        }

    protected: 
        Party party = Party();;
};

TEST_F(PartyTest, PartyConstructorTest) {
    EXPECT_EQ(party.getName(), "Democratic");
    // std::string clist[2] = {"Steve", "Brenda"};
    // party.setCandidateList(clist);

    // for (int i = 0; i < clist.size(); i++) {
    //     EXPECT_EQ(party.getCandidateList().at(i), clist[i]);
    // }
    // EXPECT_EQ(party.getCandidateList(), clist);

    EXPECT_EQ(party.getInitialSeatsWon(), 0);
    EXPECT_EQ(party.getFinalSeatsWon(), 0);
    EXPECT_EQ(party.getInitialSeatsExtra(), 0);
    EXPECT_EQ(party.getFinalSeatsExtra(), 0);
    EXPECT_EQ(party.getRemainderVotes(), 0);
}