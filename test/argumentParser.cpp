#include <gtest/gtest.h>

TEST(MyFirstTest, ASimpleTest) { EXPECT_TRUE(true); }

int Sum(int a, int b) { return a + b; }

TEST(SumTestSuite, TestSum) { EXPECT_EQ(Sum(2, 2), 4); }

TEST(SumTestSuite, TestSum2) { EXPECT_EQ(Sum(2, 3), 4); }