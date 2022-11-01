#include <iostream>

#include "AssetsManager.hpp"
#include "FileManager.hpp"
#include "ObjectBroker.hpp"

#include "rapidjson/document.h"

std::unique_ptr<AssetsManager> AssetsManager::s_instance = nullptr;

AssetsManager::AssetsManager()
{
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

void AssetsManager::LoadTexture(const std::string &path, bool isCompressed)
{
  ObjectBroker broker;

  File *file = new File();

  file -> LoadFile(path, std::ios::binary);
  file -> SetType(File::Type::Texture);

  if (m_textures.count(file -> GetFilename()) == 0)
  {
    m_textures.insert( { file -> GetFilename(), broker.CreateObjectFromFile< sf::Texture >(file, isCompressed) } );
  }
}

void AssetsManager::LoadFont(const std::string &path, bool isCompressed)
{
  ObjectBroker broker;

  File *file = new File();

  file -> LoadFile(path, std::ios::binary);
  file -> SetType(File::Type::Font);

  if (m_fonts.count(file -> GetFilename()) == 0)
  {
    m_fonts.insert( { file -> GetFilename(), broker.CreateObjectFromFile< sf::Font >(file, isCompressed) } );
  }
}

void AssetsManager::LoadImage(const std::string &path, bool isCompressed)
{
  ObjectBroker broker;

  File *file = new File();

  file -> LoadFile(path, std::ios::binary);
  file -> SetType(File::Type::Image);

  if (m_images.count(file -> GetFilename()) == 0)
  {
    m_images.insert( { file -> GetFilename(), broker.CreateObjectFromFile< sf::Image >(file, isCompressed) } );
  }
}

AssetsManager &AssetsManager::GetInstance()
{
  if (AssetsManager::s_instance == nullptr)
  {
    AssetsManager::s_instance = std::unique_ptr<AssetsManager>(new AssetsManager);
  }

  return *s_instance;
}

bool AssetsManager::ParseAssetsSchema(const std::string &path)
{
  ObjectBroker broker;

  File assetsSchema;
  assetsSchema.LoadFile(path);

  rapidjson::Document assetsSchemaDocument;
  assetsSchemaDocument.Parse(assetsSchema.GetData().c_str());

  rapidjson::Value assetsFiles;
  assetsFiles = assetsSchemaDocument["assets"];

  m_totalAssets = assetsFiles.Size();

  for (const auto &jsonData : assetsFiles.GetArray())
  {
    // FIXME: There's a memory leak.

    File *file = new File;

    file -> LoadFile(jsonData["path"].GetString(), std::ios::binary);
    file -> SetType(jsonData["type"].GetString());

    m_assetsLoaded++;

    switch(file -> GetType())
    {
      case (File::Type::Texture):
      {
        if (m_textures.count(jsonData["file"].GetString()) == 0)
        {
          m_textures.insert( { jsonData["file"].GetString(), broker.CreateObjectFromFile< sf::Texture >(file, true) });
        }
        break;
      }
      case (File::Type::Image):
      {
        if (m_images.count(jsonData["file"].GetString()) == 0)
        {
          m_images.insert( { jsonData["file"].GetString(), broker.CreateObjectFromFile< sf::Image >(file, true) });
        }
        break;
      }
      case (File::Type::Font):
      {
        if (m_fonts.count(jsonData["file"].GetString()) == 0)
        {
          m_fonts.insert( { jsonData["file"].GetString(), broker.CreateObjectFromFile< sf::Font >(file, true) });
        }
        break;
      }
      default:
      {
        break;
      }
    }
  }

  return true;
}
