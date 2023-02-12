#include <iostream>
#include <filesystem>

#include "AssetsStorage.hpp"
#include "FileStorage.hpp"
#include "MapOperations.hpp"
#include "ConsoleLog.hpp"

#include "rapidjson/document.h"

std::unique_ptr<AssetsStorage> AssetsStorage::s_instance = nullptr;

AssetsStorage::AssetsStorage()
{
  m_textureExtensions = { ".png", ".jpg", ".jpeg", ".bmp", ".tga", ".psd", ".hdr", ".pic" };
  m_fontExtensions    = { ".ttf" };
  m_imageExtensions   = { ".png", ".jpg", ".jpeg", ".bmp", ".tga", ".psd", ".hdr", ".pic" };
}

AssetsStorage::~AssetsStorage()
{
}

sf::Texture &AssetsStorage::GetTexture(const std::string &textureName) const
{
  return OnyxCore::Containers::MapGetItem< sf::Texture >(textureName, m_textures);
}

sf::Font &AssetsStorage::GetFont(const std::string &fontName) const
{
  return OnyxCore::Containers::MapGetItem< sf::Font >(fontName, m_fonts);
}

sf::Image &AssetsStorage::GetImage(const std::string &imageName) const
{
  return OnyxCore::Containers::MapGetItem< sf::Image >(imageName, m_images);
}

void AssetsStorage::LoadTexture(const std::string &path)
{
  namespace fs = std::filesystem;

  const std::string &filename = fs::path(path).filename().string();

  if (m_textures.find(filename) != m_textures.end())
  {
    FILE_LOG_WARNING("debug.txt", "AssetsStorage::LoadTexture", "Texture already loaded: ", path);
    return;
  }

  const std::string &extension = fs::path(path).filename().extension().string();

  if (std::find(m_textureExtensions.begin(), m_textureExtensions.end(), extension) == m_textureExtensions.end())
  {
    FILE_LOG_ERROR("debug.txt", "AssetsStorage::LoadTexture", "Unknown texture extension: ", path);
    return;
  }
    
  m_textures[filename] = std::make_shared<sf::Texture>();
  m_textures[filename] -> loadFromFile(path);
}

void AssetsStorage::LoadFont(const std::string &path)
{
  namespace fs = std::filesystem;

  const std::string &filename = fs::path(path).filename().string();

  if (m_fonts.find(filename) != m_fonts.end())
  {
    FILE_LOG_WARNING("debug.txt", "AssetsStorage::LoadFont", "Font already loaded: ", path);
    return;
  }

  const std::string &extension = fs::path(path).filename().extension().string();

  if (std::find(m_fontExtensions.begin(), m_fontExtensions.end(), extension) == m_fontExtensions.end())
  {
    FILE_LOG_ERROR("debug.txt", "AssetsStorage::LoadFont", "Unknown font extension: ", path);
    return;
  }

  m_fonts[filename] = std::make_shared<sf::Font>();
  m_fonts[filename] -> loadFromFile(path);
}

void AssetsStorage::LoadImage(const std::string &path)
{
  namespace fs = std::filesystem;

  const std::string &filename = fs::path(path).filename().string();

  if (m_images.find(filename) != m_images.end())
  {
    FILE_LOG_WARNING("debug.txt", "AssetsStorage::LoadImage", "Image already loaded: ", path);
    return;
  }

  const std::string &extension = fs::path(path).filename().extension().string();

  if (std::find(m_imageExtensions.begin(), m_imageExtensions.end(), extension) == m_imageExtensions.end())
  {
    FILE_LOG_ERROR("debug.txt", "AssetsStorage::LoadImage", "Unknown image extension: ", path);
    return;
  }

  m_images[filename] = std::make_shared<sf::Image>();
  m_images[filename] -> loadFromFile(path);
}

AssetsStorage &AssetsStorage::GetInstance()
{
  if (AssetsStorage::s_instance == nullptr)
  {
    AssetsStorage::s_instance = std::unique_ptr<AssetsStorage>(new AssetsStorage);
  }

  return *s_instance;
}

void AssetsStorage::LoadAssets(const std::string &path)
{
  namespace fs = std::filesystem;

  auto GetType = [this](const std::string &extension)
  {
    if (std::find(m_textureExtensions.begin(), m_textureExtensions.end(), extension) != m_textureExtensions.end())
    {
      return Type::Texture;
    }
    if (std::find(m_fontExtensions.begin(), m_fontExtensions.end(), extension) != m_fontExtensions.end())
    {
      return Type::Font;
    }
    if (std::find(m_imageExtensions.begin(), m_imageExtensions.end(), extension) != m_imageExtensions.end())
    {
      return Type::Image;
    }

    return Type::Unknown;
  };

  for (const auto &entry : fs::directory_iterator(path))
  {
    if (entry.is_directory())
    {
      LoadAssets(entry.path().string());
    }

    if (entry.is_regular_file())
    {
      const std::string &extension = entry.path().extension().string();

      const std::string& filename = entry.path().filename().string();

      if (GetType(extension) == Type::Texture)
      {
        m_textures[filename] = std::make_shared<sf::Texture>();

        if (!m_textures[filename] -> loadFromFile(entry.path().string()))
        {
          CONSOLE_LOG_ERROR("Failed to load texture: ", entry.path().string());
        }
      }
      else if (GetType(extension) == Type::Font)
      {
        m_fonts[filename] = std::make_shared<sf::Font>();

        if (!m_fonts[filename] -> loadFromFile(entry.path().string()))
        {
          CONSOLE_LOG_ERROR("Failed to load font: ", entry.path().string());
        }
      }
      else if (GetType(extension) == Type::Image)
      {
        m_images[filename] = std::make_shared<sf::Image>();
        
        if (!m_images[filename] -> loadFromFile(entry.path().string()))
        {
          CONSOLE_LOG_ERROR("Failed to load image: ", entry.path().string());
        }
      }
      else
      {
        FILE_LOG_ERROR("debug.txt", "Unknown asset type: ", entry.path().string());
      }
    }
  }
}
