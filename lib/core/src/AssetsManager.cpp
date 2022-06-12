#include <iostream>

#include "AssetsManager.hpp"

std::unique_ptr<AssetsManager> AssetsManager::s_instance = nullptr;

AssetsManager::AssetsManager()
{
  std::cout << "[AssetsManager] Created new instance of EventHandler.\n";
}

AssetsManager::~AssetsManager()
{
  std::cout << "[AssetsManager] Deleted instance of EventHandler.\n";
}

//
// TODO: Add check if assets dir even exists.
//

AssetsManager &AssetsManager::GetInstance()
{
  if (AssetsManager::s_instance == nullptr)
  {
    AssetsManager::s_instance = std::unique_ptr<AssetsManager>(new AssetsManager);
  }

  return *s_instance;
}

FontManager &AssetsManager::GetFontManager()
{
  if (s_instance == nullptr)
  {
    throw std::logic_error("[Error] You've to use it on a instance of AssetsManager.");
  }
  else
  {
    return m_fontManager;
  }
}

TextureManager &AssetsManager::GetTextureManager()
{
  if (s_instance == nullptr)
  {
    throw std::logic_error("[Error] You've to use it on a instance of AssetsManager.");
  }
  else
  {
    return m_textureManager;
  }
}