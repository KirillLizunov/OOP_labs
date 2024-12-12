#include <gtest/gtest.h>
#include "../sol.h"

TEST(ReplacerTests1, BasicTest) {
    EXPECT_EQ(replacer(2, 'a', 'o', std::string("abacadae")), std::string("abocadoe"));
}

TEST(ReplacerTests2, BasicTest){
    EXPECT_EQ(replacer(2, 'a', 'o', std::string("Vader said: No, I am your father!")), std::string("Vader soid: No, I am your fother!"));
}

TEST(ReplacerTests3, BasicTest){
    
    EXPECT_EQ(replacer(5, 'b', 'c', std::string("b")), std::string("b"));
}

TEST(ReplacerTests4, BasicTest){
    EXPECT_EQ(replacer(1, 'h', 'A', std::string("The children Have grownh up")), std::string("TAe cAildren Have grownA up"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();               
}
