#include <iostream>

#include "AssetsManager.hpp"
#include "FileManager.hpp"
#include "File.hpp"
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

AssetsManager &AssetsManager::GetInstance()
{
  if (AssetsManager::s_instance == nullptr)
  {
    AssetsManager::s_instance = std::unique_ptr<AssetsManager>(new AssetsManager);
  }

  return *s_instance;
}

void AssetsManager::ParseAssetsSchema(const std::string &path)
{
  ObjectBroker broker;

  File assetsSchema;
  assetsSchema.LoadFile(path);

  rapidjson::Document assetsSchemaDocument;
  assetsSchemaDocument.Parse(assetsSchema.GetData().c_str());

  rapidjson::Value assetsFiles;
  assetsFiles = assetsSchemaDocument["assets"];

  for (const auto &jsonData : assetsFiles.GetArray())
  {
    // FIXME: There's a memory leak.

    File *file = new File;

    file -> LoadFile(jsonData["path"].GetString(), std::ios::binary);
    file -> SetType(jsonData["type"].GetString());

    switch(file -> GetType())
    {
      case (File::Type::Texture):
      {
        m_textures.insert( { jsonData["filename"].GetString(), broker.CreateObjectFromFile< sf::Texture >(file, true) });
        break;
      }
      case (File::Type::Image):
      {
        m_images.insert( { jsonData["filename"].GetString(), broker.CreateObjectFromFile< sf::Image >(file, true) });
        break;
      }
      case (File::Type::Font):
      {
        m_fonts.insert( { jsonData["filename"].GetString(), broker.CreateObjectFromFile< sf::Font >(file, true) });
        break;
      }
      default:
      {
        break;
      }
    }
  }
}
