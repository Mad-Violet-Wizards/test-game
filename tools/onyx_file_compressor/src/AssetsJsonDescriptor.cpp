#include "AssetsJsonDescriptor.hpp"

#include <algorithm>
#include <filesystem>
#include <regex>

#include "Directory.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"

#include "Log.hpp"

void OnyxTools::Compressor::AssetsJsonDescriptor::CreateJsonFile(const std::vector<std::string> &files)
{

  auto GetFileExtension = [](const std::string &file)
  {
    auto pos = file.find_last_of('.');
    return file.substr(pos);
  };

  auto StringContains = [](const std::string &str, const std::string &substr)
  {
    return str.find(substr) != std::string::npos;
  };

  auto DetermineAssetType = [&](const std::string &file)
  {
    if (StringContains(file, "textures"))
    {
      return Type::Texture;
    }
    else if (StringContains(file, "fonts"))
    {
      return Type::Font;
    }
    else if (StringContains(file, "images"))
    {
      return Type::Image;
    }
    else if (StringContains(file, "maps"))
    {
      return Type::Map;
    }
    else if (StringContains(file, "animations"))
    {
      return Type::Animation;
    }
    else
    {
      return Type::Unknown;
    }
  };

  rapidjson::Document document;
  document.SetObject();

  rapidjson::Value texturesArray(rapidjson::kArrayType);
  rapidjson::Value fontsArray(rapidjson::kArrayType);
  rapidjson::Value imagesArray(rapidjson::kArrayType);
  rapidjson::Value mapsArray(rapidjson::kArrayType);
  rapidjson::Value animationsArray(rapidjson::kArrayType);

  rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

  for (const std::string &file : files)
  {
    rapidjson::Value outputObj(rapidjson::kObjectType);

    std::string fileExtension = GetFileExtension(file);
    
    std::filesystem::path path = std::filesystem::path(file);
    path.replace_extension(".dat");
    std::string compressedFile = std::move(path.filename().generic_string());

    outputObj.AddMember("file", rapidjson::Value(compressedFile.c_str(), allocator).Move(), allocator);
    outputObj.AddMember("raw-extension", rapidjson::Value(fileExtension.c_str(), allocator).Move(), allocator);

    switch (DetermineAssetType(file))
    {
      case Type::Texture:
      {
        texturesArray.PushBack(outputObj.Move(), allocator);
        break;
      }
      case Type::Font:
      {
        fontsArray.PushBack(outputObj.Move(), allocator);
        break;
      }
      case Type::Image:
      {
        imagesArray.PushBack(outputObj.Move(), allocator);
        break;
      }
      case Type::Map:
      {
        mapsArray.PushBack(outputObj.Move(), allocator);
        break;
      }
      case Type::Animation:
      {
        animationsArray.PushBack(outputObj.Move(), allocator);
        break;
      }
      default:
      {
        break;
      }
    } 
  }

  document.AddMember("textures", texturesArray, allocator);
  document.AddMember("fonts", fontsArray, allocator);
  document.AddMember("images", imagesArray, allocator);
  document.AddMember("maps", mapsArray, allocator);
  document.AddMember("animations", animationsArray, allocator);

  std::string output = ASSETS_DIRECTORY_OUTPUT + "schema.json";

  FILE *fp = fopen(output.c_str(), "wb");

  char writeBuffer[65536];

  rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
  rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
  document.Accept(writer);

  fclose(fp);
}