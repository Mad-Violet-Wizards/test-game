#include <iostream>

#include "gtest/gtest.h"
#include "Bitmask.hpp"

class BitmaskFixture : public ::testing::Test {

 protected:

  BitmaskFixture()
  {
    b1.SetBit(0, 0);
    b1.SetBit(1, 1);
    b1.SetBit(2, 1);

    b2.SetBit(0, 1);
    b2.SetBit(1, 1);
    b2.SetBit(1, 1);
  }

protected:

  Bitmask b1;
  Bitmask b2;
};

TEST_F(BitmaskFixture, TestMoveSemantics)
{
  // Test of copy constructor.

  Bitmask b3(b2);

  EXPECT_EQ(b3.GetMask(), b2.GetMask());
  ASSERT_NE(b2.GetMask(), b1.GetMask());

  // Test of move constructor.

  Bitmask b4(std::move(b2));

  EXPECT_EQ(b4.GetMask(), b3.GetMask());
  EXPECT_EQ(b2.GetMask(), 0);

  // Test of copy operator.

  b4 = b1;
  EXPECT_EQ(b4.GetMask(), b1.GetMask());
  ASSERT_NE(b4.GetMask(), b3.GetMask());

  // Test of move operator.

  Bitmask b5(6); // Because b1 is 6. 110 (2) = 6 (10)

  b4 = std::move(b1);
  EXPECT_EQ(b4.GetMask(), b5.GetMask());
  EXPECT_EQ(b1.GetMask(), 0);
}