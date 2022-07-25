#include <iostream>

#include "AssetsManager.hpp"
#include "FileManager.hpp"

std::unique_ptr<AssetsManager> AssetsManager::s_instance = nullptr;

AssetsManager::AssetsManager()
{
  CreateFilesMap< sf::Texture >(std::string { "../assets/textures/" },
                                { ".bmp", ".png", ".tga", ".jpg", ".gif", ".psd", ".hdr", ".pic" },
                                m_textures );

  CreateFilesMap< sf::Font >(std::string { "../assets/fonts/"},
                             { ".ttf" },
                             m_fonts );

  CreateFilesMap< sf::Image >(std::string {"../assets/images/" },
                              { ".bmp", ".png", ".tga", ".jpg", ".gif", ".psd", ".hdr", ".pic" },
                              m_images );
}

AssetsManager::~AssetsManager()
{
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

sf::Image &AssetsManager::GetImage(const std::string &imageName) const
{
  return FindInFilesMap< sf::Image >(imageName, m_images);
}

AssetsManager &AssetsManager::GetInstance()
{
  if (AssetsManager::s_instance == nullptr)
  {
    AssetsManager::s_instance = std::unique_ptr<AssetsManager>(new AssetsManager);
  }

  return *s_instance;
}
