#pragma once

#include "FontManager.hpp"

class AssetsManager
{

public:

  ~AssetsManager();

  static AssetsManager &GetInstance();
  FontManager &GetFontManager();

private:

  AssetsManager();

private:

  FontManager m_fontManager;

  static std::unique_ptr<AssetsManager> s_instance;
};