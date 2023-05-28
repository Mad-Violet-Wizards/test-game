#pragma once

#include <array>
#include <vector>

namespace aseprite
{
  using BYTE   = uint8_t;
  using WORD   = uint16_t;
  using SHORT  = int16_t;
  using DWORD  = uint32_t;
  using LONG   = int32_t;
  using FLOAT  = float;
  using DOUBLE = double;
  using QWORD  = uint64_t;
  using LONG64 = int64_t;
  using BYTE   = unsigned char;

  struct STRING_STRUCT
  {
    STRING_STRUCT(WORD length)
    : m_length(length)
    {
      m_data.reserve(length);
    }

    STRING_STRUCT(WORD length, const std::vector<char> &data)
      : m_length(length)
      , m_data(data)
    {}

    WORD              m_length;
    std::vector<char> m_data;
  };

  using STRING = STRING_STRUCT;

  struct POINT_STRUCT
  {
    LONG m_x;
    LONG m_y;
  };

  using POINT = POINT_STRUCT;

  struct SIZE_STRUCT
  {
    LONG m_width;
    LONG m_height;
  };

  using SIZE = SIZE_STRUCT;

  struct RECT_STRUCT
  {
    POINT m_origin;
    SIZE  m_size;
  };

  using RECT = RECT_STRUCT;

  struct PIXEL_STRUCT
  {
    std::array<BYTE, 4> m_rgba;
    std::array<BYTE, 2> m_grayscale;
    BYTE                m_index;
  };

  using PIXEL = PIXEL_STRUCT;

  using TILE_BYTE = BYTE;
  using TILE_WORD = WORD;
  using TILE_DWORD = DWORD;

  using UUID = std::array<BYTE, 16>;
};