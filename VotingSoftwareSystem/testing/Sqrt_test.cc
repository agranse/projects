#include <gtest/gtest.h>

#include <cmath>

double square_root(double number){
    return sqrt(number);
}

// A test fixture is used to pre-initialize data and varibles
// that will be used within test. THIS IS OPTIONAL and is not use
// in this example. 
class SqrtTestFixture : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
  }
 protected:
    // these attributes are used to test against functions
};

// This is the actual test object that will be called by RUN_ALL_TESTS()
TEST(Sqrt_test, PositiveNos) {

    double result1 = square_root(4.0);
    double result2 = square_root(16.0);

    EXPECT_EQ(result1, 2.0);
    EXPECT_EQ(result2, 4.0);
}
