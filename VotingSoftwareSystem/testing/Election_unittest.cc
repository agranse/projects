#include <gtest/gtest.h>
#include "../src/Election.h"
#include <iostream>
#include <string>
#include <cmath>

class ElectionPromptTest: public ::testing::Test { 
public:
    virtual void SetUp( ) override{ 
        // Algorithm for piping std::cin from https://stackoverflow.com/a/73666797

        // code here will execute just before the test ensues 
        testObj = Election();
        int fildes[2];
        if(pipe(fildes)){
            std::cout << "could not create pipe\n";
        }

        // Swap `stdin` fd with the "read" end of the pipe
        if (dup2(fildes[0], STDIN_FILENO)){
            std::cout << "could not set up pipe\n";
        }
    
        // Create payload
        const char buf[] = "12/03/1988\n"; //buf is where mock cin goes
        const int bsize  = strlen(buf);

        // Send payload through pipe
        ssize_t nbytes = write(fildes[1], buf, bsize);
        if (!nbytes==bsize){
            std::cout << "Could not write to pipe.\n";
        }

        // Create payload2
        const char buf2[] = "12/3/1988\n"; //buf is where mock cin goes
        const int bsize2  = strlen(buf2);

        // Send payload2 through pipe
        ssize_t nbytes2 = write(fildes[1], buf2, bsize2);
        if (!nbytes2==bsize2){
            std::cout << "Could not write to pipe.\n";
        }

        // Create payload3
        const char buf3[] = "2\n"; //buf is where mock cin goes
        const int bsize3  = strlen(buf3);

        // Send payload3 through pipe
        ssize_t nbytes3 = write(fildes[1], buf3, bsize3);
        if (!nbytes3==bsize3){
            std::cout << "Could not write to pipe.\n";
        }

        // Create payload4
        const char buf4[] = "234/12/2023\n"; //buf is where mock cin goes
        const int bsize4  = strlen(buf4);

        // Send payload4 through pipe
        ssize_t nbytes4 = write(fildes[1], buf4, bsize4);
        if (!nbytes4==bsize4){
            std::cout << "Could not write to pipe.\n";
        }

        // Create payload5
        const char buf5[] = "xy/12/fooo\n"; //buf is where mock cin goes
        const int bsize5  = strlen(buf5);

        // Send payload5 through pipe
        ssize_t nbytes5 = write(fildes[1], buf5, bsize5);
        if (!nbytes5==bsize5){
            std::cout << "Could not write to pipe.\n";
        }

        // Create payload6
        const char buf6[] = "\n"; //buf is where mock cin goes
        const int bsize6  = strlen(buf6);

        // Send payload6 through pipe
        ssize_t nbytes6 = write(fildes[1], buf6, bsize6);
        if (!nbytes6==bsize6){
            std::cout << "Could not write to pipe.\n";
        }

        // Create payload7
        const char buf7[] = "0/0/0\n"; //buf is where mock cin goes
        const int bsize7  = strlen(buf7);

        // Send payload7 through pipe
        ssize_t nbytes7 = write(fildes[1], buf7, bsize7);
        if (!nbytes7==bsize7){
            std::cout << "Could not write to pipe.\n";
        }
        close(fildes[1]);

        result1 = testObj.promptForDate();
        result2 = testObj.promptForDate();
        result3 = testObj.promptForDate();
        result4 = testObj.promptForDate();
        result5 = testObj.promptForDate();
        result6 = testObj.promptForDate();
        result7 = testObj.promptForDate();

        close(fildes[0]);
   }

   // put in any custom data members that you need 
    Election testObj;
    string result1;
    string result2;
    string result3;
    string result4;
    string result5;
    string result6;
    string result7;
};

class ElectionTest : public ::testing::Test{
    public:
    void SetUp() override {
        testObj = Election();
    }

    Election testObj;
};

TEST_F (ElectionPromptTest, promptForDateTest){

    EXPECT_EQ(result1, "12/03/1988");

    EXPECT_EQ(result2, "12/3/1988");

    EXPECT_EQ(result3, "Incorrect date format given.");

    EXPECT_EQ(result4, "Incorrect date format given.");

    EXPECT_EQ(result5, "Incorrect date format given.");

    EXPECT_EQ(result6, "Incorrect date format given.");

    EXPECT_EQ(result7, "Incorrect date format given.");
}


TEST_F (ElectionTest, levelTieTest){
    int n = 6;
    int temp;
    double chi = 11.07; //significance of 5%
    double expected = 100.0;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    int n6 = 0;

    for (int i=0; i<(n*100); i++){
        temp = testObj.levelTie(n);
        switch (temp){
            case 1:
                n1++;
                break;
            case 2:
                n2++;
                break;
            case 3:
                n3++;
                break;
            case 4:
                n4++;
                break;
            case 5:
                n5++;
                break;
            case 6:
                n6++;
                break;
        }
    }

    cout << endl;
    cout << n1 << endl;
    cout << n2 << endl;
    cout << n3 << endl;
    cout << n4 << endl;
    cout << n5 << endl;
    cout << n6 << endl;


    double x = (pow((double(n1)-expected),2)/expected + pow((double(n2)-expected),2)/expected + pow((double(n3)- expected),2)/expected +
               pow((double(n4)-expected),2)/expected + pow((double(n5)-expected),2)/expected + pow((double(n6)-expected),2)/expected);

    // test whether levelTie distributes randomly.
    EXPECT_LE(x, chi);

    EXPECT_NE(testObj.levelTie(6), 7);

    EXPECT_GT(testObj.levelTie(23), 0);

    // EXPECT_EQ(testObj.levelTie(0), 0); can't have leveltie with called with 0
}