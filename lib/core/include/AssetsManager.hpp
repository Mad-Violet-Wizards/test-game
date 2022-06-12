#pragma once

#include "FontManager.hpp"
#include "TextureManager.hpp"

class AssetsManager
{

public:

  ~AssetsManager();

  static AssetsManager &GetInstance();
  FontManager &GetFontManager();
  TextureManager &GetTextureManager();

private:

  AssetsManager();

private:

  FontManager m_fontManager;
  TextureManager m_textureManager;

  static std::unique_ptr<AssetsManager> s_instance;

};