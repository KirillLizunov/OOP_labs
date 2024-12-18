#include "../BitString.h"
#include <gtest/gtest.h>


TEST(BitStringTest, ConstructorFromString) {
    BitString bitStr("10101");

    std::stringstream ss;
    ss << bitStr;

    EXPECT_EQ(ss.str(), "10101");
}

TEST(BitStringTest, ConstructorWithSize) {
    BitString bitStr(5);

    std::stringstream ss;
    ss << bitStr;

    EXPECT_EQ(ss.str(), "00000");
}

TEST(BitStringTest, BitwiseOR) {
    BitString bitStr1("10101");
    BitString bitStr2("11011");

    BitString result = bitStr1 + bitStr2;

    std::stringstream ss;
    ss << result;

    EXPECT_EQ(ss.str(), "11111");
}

TEST(BitStringTest, BitwiseAND) {
    BitString bitStr1("10101");
    BitString bitStr2("11011");

    BitString result = bitStr1 - bitStr2;

    std::stringstream ss;
    ss << result;

    EXPECT_EQ(ss.str(), "00100");
}

TEST(BitStringTest, BitwiseXOR) {
    BitString bitStr1("10101");
    BitString bitStr2("11011");

    BitString result = bitStr1 ^ bitStr2;

    std::stringstream ss;
    ss << result;

    EXPECT_EQ(ss.str(), "01110");
}

TEST(BitStringTest, BitwiseNOT) {
    BitString bitStr("10101");

    BitString result = ~bitStr;

    std::stringstream ss;
    ss << result;

    EXPECT_EQ(ss.str(), "01010");
}


TEST(BitStringTest, AssignmentOperator) {
    BitString bitStr1("10101");
    BitString bitStr2("11011");

    bitStr1 = bitStr2;

    std::stringstream ss;
    ss << bitStr1;

    EXPECT_EQ(ss.str(), "11011");
}


TEST(BitStringTest, CompoundAssignmentOperators) {
    BitString bitStr1("10101");
    BitString bitStr2("11011");

    bitStr1 += bitStr2;

    std::stringstream ss;
    ss << bitStr1;

    EXPECT_EQ(ss.str(), "11111");

    bitStr1 -= bitStr2;

    ss.str("");
    ss << bitStr1;

    EXPECT_EQ(ss.str(), "00100");
}


TEST(BitStringTest, DifferentSizeBitStrings) {
    BitString bitStr1("10101");
    BitString bitStr2("110");

    EXPECT_THROW(bitStr1 + bitStr2, std::invalid_argument);
    EXPECT_THROW(bitStr1 - bitStr2, std::invalid_argument);
    EXPECT_THROW(bitStr1 ^ bitStr2, std::invalid_argument);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}