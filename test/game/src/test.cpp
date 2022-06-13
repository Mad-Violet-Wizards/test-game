#include <SFML/Graphics.hpp>

#include "gtest/gtest.h"

#include "C_Transform.hpp"

TEST(C_TransformInitialPosition, BasicAssertions)
{
  C_Transform cTransform(nullptr);
  EXPECT_EQ(cTransform.GetPosition(), sf::Vector2f(0, 0));
}