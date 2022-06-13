#include "gtest/gtest.h"

#include "Bitmask.hpp"

TEST(BitmaskTestEmpty, BasicAssertions)
{
  Bitmask bmsk;
  EXPECT_EQ(bmsk.GetMask(), 0);
}