#include <iostream>

#include "AssetsManager.hpp"
#include "FileManager.hpp"
#include "Directory.hpp"

std::unique_ptr<AssetsManager> AssetsManager::s_instance = nullptr;

AssetsManager::AssetsManager()
{
  ParseAssetsToMap< sf::Texture >( Directory::TEXTURES_DIRECTORY,
                                { ".bmp", ".png", ".tga", ".jpg", ".gif", ".psd", ".hdr", ".pic" },
                                m_textures );

  ParseAssetsToMap< sf::Font >( Directory::FONTS_DIRECTORY,
                             { ".ttf" },
                             m_fonts );

  ParseAssetsToMap< sf::Image >( Directory::IMAGES_DIRECTORY,
                              { ".bmp", ".png", ".tga", ".jpg", ".gif", ".psd", ".hdr", ".pic" },
                              m_images );

  ParseAssetsToMap< sf::Texture>( Directory::MAPS_DIRECTORY,
                               { ".png" },
                               m_textures );
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

// void AssetsManager::AddTexture(const std::string &textureName, const std::string &texturePath)
// {
//   AddToFilesMap< sf::Texture >(textureName, m_textures);
// }

AssetsManager &AssetsManager::GetInstance()
{
  if (AssetsManager::s_instance == nullptr)
  {
    AssetsManager::s_instance = std::unique_ptr<AssetsManager>(new AssetsManager);
  }

  return *s_instance;
}
