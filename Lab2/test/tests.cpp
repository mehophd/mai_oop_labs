#include <gtest/gtest.h>
#include "bitstring.h"
#include <stdexcept>
#include <sstream> 

TEST(test_01, basic_test_set) {
    BitString bs;
    std::ostringstream oss;
    bs.print(oss);
    EXPECT_EQ(oss.str(), "0");
    EXPECT_EQ(bs.equals(BitString("0")), true);
}

TEST(test_02, basic_test_set) {
    BitString bs1(5, 0);
    std::ostringstream oss1;
    bs1.print(oss1);
    EXPECT_EQ(oss1.str(), "0");

    BitString bs2(5, 1);
    std::ostringstream oss2;
    bs2.print(oss2);
    EXPECT_EQ(oss2.str(), "11111");
}

TEST(test_03, basic_test_set) {
    BitString bs1("1010");
    std::ostringstream oss1;
    bs1.print(oss1);
    EXPECT_EQ(oss1.str(), "1010");

    BitString bs2("00001111");
    std::ostringstream oss2;
    bs2.print(oss2);
    EXPECT_EQ(oss2.str(), "1111"); 

    BitString bs3("0");
    std::ostringstream oss3;
    bs3.print(oss3);
    EXPECT_EQ(oss3.str(), "0");

    EXPECT_THROW(BitString bs_invalid("102"), std::invalid_argument);
    EXPECT_THROW(BitString bs_invalid2("10a1"), std::invalid_argument);
}

TEST(test_04, basic_test_set) {
    BitString bs1({1, 0, 1, 0});
    std::ostringstream oss1;
    bs1.print(oss1);
    EXPECT_EQ(oss1.str(), "1010");

    BitString bs2({0, 0, 0, 1});
    std::ostringstream oss2;
    bs2.print(oss2);
    EXPECT_EQ(oss2.str(), "1"); 

    EXPECT_THROW(BitString bs_invalid({1, 0, 2}), std::invalid_argument);
}

TEST(test_05, basic_test_set) {
    BitString bs1("11001");
    BitString bs2 = bs1; 
    EXPECT_TRUE(bs1.equals(bs2));

    BitString bs3 = std::move(BitString("0101"));
    BitString expected("0101");
    EXPECT_TRUE(bs3.equals(expected));
}

TEST(test_06, basic_test_set) {
    BitString bs1("1010");
    BitString bs2("1010");
    BitString bs3("1100");
    BitString bs4("101");

    EXPECT_TRUE(bs1.equals(bs2));
    EXPECT_FALSE(bs1.is_greater(bs2));
    EXPECT_FALSE(bs1.is_less(bs2));

    EXPECT_TRUE(bs3.is_greater(bs1));
    EXPECT_TRUE(bs1.is_less(bs3));

    EXPECT_TRUE(bs1.is_greater(bs4)); 
    EXPECT_TRUE(bs4.is_less(bs1));   
}

TEST(test_07, basic_test_set) {
    BitString bs1("101"); 
    BitString bs2("011"); 
    BitString sum = BitString::add(bs1, bs2); 
    std::ostringstream oss;
    sum.print(oss);
    EXPECT_EQ(oss.str(), "1000");

    BitString bs3("1111"); 
    BitString bs4("0001"); 
    BitString sum2 = BitString::add(bs3, bs4); 
    std::ostringstream oss2;
    sum2.print(oss2);
    EXPECT_EQ(oss2.str(), "10000");
}

TEST(test_08, basic_test_set) {
    BitString bs1("1010"); 
    BitString bs2("0011"); 
    BitString diff = BitString::subtract(bs1, bs2); 
    std::ostringstream oss;
    diff.print(oss);
    EXPECT_EQ(oss.str(), "111");

    BitString bs3("1000"); 
    BitString bs4("1000"); 
    BitString diff2 = BitString::subtract(bs3, bs4); 
    std::ostringstream oss2;
    diff2.print(oss2);
    EXPECT_EQ(oss2.str(), "0");

    EXPECT_THROW(BitString::subtract(bs2, bs1), std::invalid_argument);
}

TEST(test_09, basic_test_set) {
    BitString bs1("1100");
    BitString bs2("1010");
    BitString result = BitString::bit_and(bs1, bs2);
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "1000"); 
}

TEST(test_10, basic_test_set) {
    BitString bs1("1100");
    BitString bs2("1010");
    BitString result = BitString::bit_or(bs1, bs2);
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "1110");
}

TEST(test_11, basic_test_set) {
    BitString bs1("1100");
    BitString bs2("1010");
    BitString result = BitString::bit_xor(bs1, bs2);
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "110");
}

TEST(test_12, basic_test_set) {
    BitString bs1("1010");
    BitString result = bs1.bit_not();
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "101"); 

    BitString bs2("1111");
    BitString result2 = bs2.bit_not();
    std::ostringstream oss2;
    result2.print(oss2);
    EXPECT_EQ(oss2.str(), "0");
}

TEST(test_13, basic_test_set) {
    BitString bs1("101");
    BitString bs2("011");

    BitString result_add = bs1.assign_add(bs2);
    std::ostringstream oss_add;
    result_add.print(oss_add);
    EXPECT_EQ(oss_add.str(), "1000"); 

    BitString bs3("1010");
    BitString bs4("0011");
    BitString result_sub = bs3.assign_subtract(bs4);
    std::ostringstream oss_sub;
    result_sub.print(oss_sub);
    EXPECT_EQ(oss_sub.str(), "111"); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}