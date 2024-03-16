#include <gtest/gtest.h>
#include "../src/Candidate.h"

class CandidateTest : public ::testing::Test {
    public:
        void SetUp( ) {
            candidate = Candidate("Billy");
        }

    protected: 
        Candidate candidate;
};

TEST_F(CandidateTest, CandidateConstructorTest) {
    EXPECT_EQ(candidate.getCandidateName(), "Billy");
    EXPECT_EQ(candidate.getVoteCount(), 0);
}