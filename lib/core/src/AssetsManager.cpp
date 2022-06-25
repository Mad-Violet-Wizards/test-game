#include <iostream>

#include "AssetsManager.hpp"
#include "FileManager.hpp"

std::unique_ptr<AssetsManager> AssetsManager::s_instance = nullptr;

AssetsManager::AssetsManager()
{
  std::cout << "[AssetsManager] Created new instance of AssetsManager.\n";

  CreateFilesMap< sf::Texture >(std::string { "../assets/textures/" },
                                std::string { ".png" },
                                m_textures );

  CreateFilesMap< sf::Font >(std::string { "../assets/fonts/"},
                             std::string { ".ttf" },
                             m_fonts );
}

AssetsManager::~AssetsManager()
{
  std::cout << "[AssetsManager] Deleted instance of AssetsManager.\n";
}

//
// TODO: Add check if assets dir even exists.
//

sf::Texture &AssetsManager::GetTexture(const std::string &textureName) const
{
  return FindInFilesMap< sf::Texture >(textureName, m_textures);
}

sf::Font &AssetsManager::GetFont(const std::string &fontName) const
{
  return FindInFilesMap< sf::Font >(fontName, m_fonts);
}

AssetsManager &AssetsManager::GetInstance()
{
  if (AssetsManager::s_instance == nullptr)
  {
    AssetsManager::s_instance = std::unique_ptr<AssetsManager>(new AssetsManager);
  }

  return *s_instance;
}
