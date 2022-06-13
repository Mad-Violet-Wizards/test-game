#include "gtest/gtest.h"

TEST(HelloTest, BasicAssertions)
{
  EXPECT_STRNE("hello", "world");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}