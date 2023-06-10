#pragma once

namespace aseprite
{
/////////////////////////////////////////////////////////////

  enum class EColorDepth : WORD
  {
    RGBA = 32,
    Grayscale = 16,
    Indexed = 8
  };

  EColorDepth WordToColorDepth(WORD colorDepth)
  {
    switch (colorDepth)
    {
      case 32:              return EColorDepth::RGBA;
      case 16:              return EColorDepth::Grayscale;
      case  8:              return EColorDepth::Indexed;
      default: [[unlikely]] return EColorDepth::RGBA;
    }
  }

  WORD ColorDepthToWord(EColorDepth colorDepth)
  {
    switch (colorDepth)
    {
      case EColorDepth::RGBA:      return 32;
      case EColorDepth::Grayscale: return 16;
      case EColorDepth::Indexed:   return 8;
      default: [[unlikely]]        return 32;
    }
  }

  const char* ColorDepthToString(EColorDepth colorDepth)
  {
    switch (colorDepth)
    {
      case EColorDepth::RGBA:      return "RGBA";
      case EColorDepth::Grayscale: return "Grayscale";
      case EColorDepth::Indexed:   return "Indexed";
      default: [[unlikely]]        return "RGBA";
    }
  }

/////////////////////////////////////////////////////////////

  enum class ELayerChunkFlag
  {
    Visible = 1,
    Editable = 2,
    LockMovement = 4,
    Background = 8,
    PreferLinkedCels = 16,
    Collapsed = 32,
    ReferenceLayer = 64
  };

  ELayerChunkFlag WordToLayerChunkFlag(WORD layerChunkFlag)
  {
    switch (layerChunkFlag)
    {
      case 1:  return ELayerChunkFlag::Visible;
      case 2:  return ELayerChunkFlag::Editable;
      case 4:  return ELayerChunkFlag::LockMovement;
      case 8:  return ELayerChunkFlag::Background;
      case 16: return ELayerChunkFlag::PreferLinkedCels;
      case 32: return ELayerChunkFlag::Collapsed;
      case 64: return ELayerChunkFlag::ReferenceLayer;
      default: [[unlikely]] return ELayerChunkFlag::Visible;
    }
  }

/////////////////////////////////////////////////////////////

  enum class ELayerChunkType
  {
    Normal = 0,
    Group = 1,
    Tilemap = 2
  };

  ELayerChunkType WordToLayerChunkType(WORD layerChunkType)
  {
    switch (layerChunkType)
    {
      case 0: return ELayerChunkType::Normal;
      case 1: return ELayerChunkType::Group;
      case 2: return ELayerChunkType::Tilemap;
      default: [[unlikely]] return ELayerChunkType::Normal;
    }
  }

/////////////////////////////////////////////////////////////

  enum class ELayerChunkBlendMode
  {
    Normal = 0,
    Multiply = 1,
    Screen = 2,
    Overlay = 3,
    Darken = 4,
    Lighten = 5,
    ColorDodge = 6,
    ColorBurn = 7,
    HardLight = 8,
    SoftLight = 9,
    Difference = 10,
    Exclusion = 11,
    Hue = 12,
    Saturation = 13,
    Color = 14,
    Luminosity = 15,
    Addition = 16,
    Subtract = 17,
    Divide = 18
  };

  ELayerChunkBlendMode WordToChunkBlendMode(WORD layerChunkBlendMode)
  {
    switch(layerChunkBlendMode)
    {
      case  0: return ELayerChunkBlendMode::Normal;
      case  1: return ELayerChunkBlendMode::Multiply;
      case  2: return ELayerChunkBlendMode::Screen;
      case  3: return ELayerChunkBlendMode::Overlay;
      case  4: return ELayerChunkBlendMode::Darken;
      case  5: return ELayerChunkBlendMode::Lighten;
      case  6: return ELayerChunkBlendMode::ColorDodge;
      case  7: return ELayerChunkBlendMode::ColorBurn;
      case  8: return ELayerChunkBlendMode::HardLight;
      case  9: return ELayerChunkBlendMode::SoftLight;
      case 10: return ELayerChunkBlendMode::Difference;
      case 11: return ELayerChunkBlendMode::Exclusion;
      case 12: return ELayerChunkBlendMode::Hue;
      case 13: return ELayerChunkBlendMode::Saturation;
      case 14: return ELayerChunkBlendMode::Color;
      case 15: return ELayerChunkBlendMode::Luminosity;
      case 16: return ELayerChunkBlendMode::Addition;
      case 17: return ELayerChunkBlendMode::Subtract;
      case 18: return ELayerChunkBlendMode::Divide;
    }
  }

/////////////////////////////////////////////////////////////

  enum class ECelChunkType
  {
    Raw = 0,
    Linked = 1,
    CompressedImage = 2,
    CompressedTilemap = 3
  };

};