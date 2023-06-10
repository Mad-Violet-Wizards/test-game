#pragma once

#include "AsepriteFileFormatTypes.hpp"

namespace aseprite
{

/////////////////////////////////////////////////////////////

  struct Header // 128 bytes.
  {
    DWORD m_fileSize;
    WORD m_magicNumber; // Always 0xA5E0.
    WORD m_frames;
    WORD m_width;
    WORD m_height;
    WORD m_colorDepth;
    DWORD m_flags;
    WORD m_speed; // DEPRACTED.
    DWORD m_reserved;
    DWORD m_reserved2;
    BYTE m_paletteEntry;
    BYTE m_reserverd3[3];
    WORD m_numberOfColors;
    BYTE m_pixelWidth;
    BYTE m_pixelHeight;
    SHORT m_gridX;
    SHORT m_gridY;
    WORD m_gridWidth;
    WORD m_gridHeight;
  };

/////////////////////////////////////////////////////////////

  struct FrameHeader
  {
    DWORD m_frameSize;
    WORD m_magicNumber; // Always 0xF1FA.
    WORD m_oldChunks; // Old field - number of chunks.
    WORD m_duration;
    BYTE m_reserved[2];
    DWORD m_chunks;
  };

/////////////////////////////////////////////////////////////

  struct ChunkHeader
  {
    DWORD m_chunkSize;
    WORD m_chunkType;
  };

/////////////////////////////////////////////////////////////

  struct LayerChunk
  {
    WORD m_flags;
    WORD m_type;
    WORD m_childLevel;
    WORD m_defaultLayerWidth;
    WORD m_defaultLayerHeight;
    WORD m_blendMode;
    BYTE m_opacity;
    BYTE m_reserved[3];
    STRING m_layerName;
    DWORD m_tilesetIndex; // Only when type == 2.
  };

/////////////////////////////////////////////////////////////

  struct CelChunk
  {
    WORD m_layerIndex;
    SHORT m_x;
    SHORT m_y;
    BYTE m_opacity;
    BYTE m_type;
    SHORT m_zIndex;
  }
};