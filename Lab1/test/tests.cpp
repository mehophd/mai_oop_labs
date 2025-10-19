#include <gtest/gtest.h>
#include "../include/euclid.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(euclid(8,6)==2);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(euclid(6,8)==2);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(euclid(100,0)==100);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(euclid(0,0)==0);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(euclid(-5,10)==5);
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(euclid(-12,-6)==6);
}

TEST(test_07, basic_test_set)
{
    ASSERT_TRUE(euclid(3,17)==1);
}

TEST(test_08, basic_test_set)
{
    ASSERT_TRUE(euclid(2367000,2862300)==300);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}