#include <gtest/gtest.h>

//Add test files below. Sqrt_test.cc is an example.
// #include "Sqrt_test.cc"
#include "Election_unittest.cc"
#include "Candidate_unittest.cc"
#include "Party_unittest.cc" 
#include "CplBallot_unittest.cc"
#include "IrBallot_unittest.cc"
#include "Ir_unittest.cc"
// #include "Cpl_unittest.cc"

//Below is main for test. You do not need to change any of this
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// //Below is main for test. You do not need to change any of this
// int main(int argc, char **argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }