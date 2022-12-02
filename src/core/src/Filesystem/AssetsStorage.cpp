#include <iostream>

#include "AssetsStorage.hpp"
#include "FileStorage.hpp"
#include "MapOperations.hpp"
#include "ObjectBroker.hpp"

#include "rapidjson/document.h"

std::unique_ptr<AssetsStorage> AssetsStorage::s_instance = nullptr;

AssetsStorage::AssetsStorage()
{
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

void AssetsStorage::LoadTexture(const std::string &path, bool isCompressed)
{
  ObjectBroker broker;

  File *file = new File(); 

  FileStorage::GetInstance().InsertFile(file);

  file -> LoadFile(path, std::ios::binary);
  file -> SetType(File::Type::Texture);

  if (m_textures.count(file -> GetFilename()) == 0)
  {
    m_textures.insert( { file -> GetFilename(), broker.CreateObjectFromFile< sf::Texture >(file, isCompressed) } );
  }
}

void AssetsStorage::LoadFont(const std::string &path, bool isCompressed)
{
  ObjectBroker broker;

  File *file = new File();

  FileStorage::GetInstance().InsertFile(file);

  file -> LoadFile(path, std::ios::binary);
  file -> SetType(File::Type::Font);

  if (m_fonts.count(file -> GetFilename()) == 0)
  {
    m_fonts.insert( { file -> GetFilename(), broker.CreateObjectFromFile< sf::Font >(file, isCompressed) } );
  }
}

void AssetsStorage::LoadImage(const std::string &path, bool isCompressed)
{
  ObjectBroker broker;

  File *file = new File();

  FileStorage::GetInstance().InsertFile(file);

  file -> LoadFile(path, std::ios::binary);
  file -> SetType(File::Type::Image);

  if (m_images.count(file -> GetFilename()) == 0)
  {
    m_images.insert( { file -> GetFilename(), broker.CreateObjectFromFile< sf::Image >(file, isCompressed) } );
  }
}

AssetsStorage &AssetsStorage::GetInstance()
{
  if (AssetsStorage::s_instance == nullptr)
  {
    AssetsStorage::s_instance = std::unique_ptr<AssetsStorage>(new AssetsStorage);
  }

  return *s_instance;
}

void AssetsStorage::ParseAssetsSchema(const std::string &path)
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
    File *file = new File;

    FileStorage::GetInstance().InsertFile(file);

    file -> LoadFile(jsonData["path"].GetString(), std::ios::binary);
    file -> SetType(jsonData["type"].GetString());

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
}
