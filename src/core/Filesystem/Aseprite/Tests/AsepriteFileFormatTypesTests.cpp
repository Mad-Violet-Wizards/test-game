#include <gtest/gtest.h>

#include "AsepriteFileFormatTypes.hpp"

// Refer to the docs on the Aseprite site:
// https://github.com/aseprite/aseprite/blob/main/docs/ase-file-specs.md

TEST(AsepriteTypesTests, AsepriteFileFormatTypesMatchDocumentation)
{
  using namespace aseprite;

  EXPECT_EQ(typeid(BYTE), typeid(uint8_t));

  EXPECT_EQ(typeid(BYTE),   typeid(uint8_t));
  EXPECT_EQ(typeid(WORD),   typeid(uint16_t));
  EXPECT_EQ(typeid(SHORT),  typeid(int16_t));
  EXPECT_EQ(typeid(DWORD),  typeid(uint32_t));
  EXPECT_EQ(typeid(LONG),   typeid(int32_t));
  EXPECT_EQ(typeid(FLOAT),  typeid(float));
  EXPECT_EQ(typeid(DOUBLE), typeid(double));
  EXPECT_EQ(typeid(QWORD),  typeid(uint64_t));
  EXPECT_EQ(typeid(LONG64), typeid(int64_t));
  EXPECT_EQ(typeid(BYTE),   typeid(unsigned char));
}

TEST(AsepriteFileFormatTypesTests, AsepriteFileFormatTypesStructsMatchDocumentation)
{
  using namespace aseprite;

  EXPECT_EQ(typeid(STRING_STRUCT),  typeid(STRING));
  EXPECT_EQ(typeid(POINT_STRUCT),   typeid(POINT));
  EXPECT_EQ(typeid(SIZE_STRUCT),    typeid(SIZE));
  EXPECT_EQ(typeid(RECT_STRUCT),    typeid(RECT));
  EXPECT_EQ(typeid(PIXEL_STRUCT),   typeid(PIXEL));
}

TEST(AsepriteFileFormatTypesTests, AsepriteFileFormatTypesTileTypesMatchDocumentation)
{
  using namespace aseprite;

  EXPECT_EQ(typeid(TILE_BYTE),  typeid(BYTE));
  EXPECT_EQ(typeid(TILE_WORD),  typeid(WORD));
  EXPECT_EQ(typeid(TILE_DWORD), typeid(DWORD));
}
