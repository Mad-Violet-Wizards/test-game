#include "AssetsJsonDescriptor.hpp"

#include <algorithm>
#include <filesystem>
#include <regex>
#include <ranges>
#include <string_view>

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

  constexpr std::string_view delimeter("/");

  rapidjson::Document document;
  document.SetObject();

  rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

  rapidjson::Value assetsSchemaArray(rapidjson::kArrayType);

  for (const std::string_view &file : files)
  {
    std::vector<std::string> splittedFile;

    for (auto word : std::views::split(file, delimeter))
    {
      splittedFile.push_back({word.begin(), word.end()});
    }

    const std::string &type = splittedFile[splittedFile.size() - 2];
    const std::string &filename = splittedFile.back();
    const std::string &fileExtension = GetFileExtension(filename);

    std::filesystem::path path = std::filesystem::path(file);
    path.replace_extension(".dat");
    const std::string &compressedFile = path.filename().generic_string();
    const std::string &releasePath = "../assets/" + type + "/" + compressedFile;

    rapidjson::Value outputObj(rapidjson::kObjectType);

    outputObj.AddMember("file", rapidjson::Value(compressedFile.c_str(), allocator).Move(), allocator);
    outputObj.AddMember("filename", rapidjson::Value(filename.c_str(), allocator).Move(), allocator);
    outputObj.AddMember("extension", rapidjson::Value(fileExtension.c_str(), allocator).Move(), allocator);
    outputObj.AddMember("path", rapidjson::Value(releasePath.c_str(), allocator).Move(), allocator);
    outputObj.AddMember("type", rapidjson::Value(type.c_str(), allocator).Move(), allocator);

    if (fileExtension != ".json")
    {
      assetsSchemaArray.PushBack(outputObj.Move(), allocator);
    }
  }

  // Create schema for assets.
  {
    document.AddMember("assets", assetsSchemaArray, allocator);

    std::string output = ASSETS_DIRECTORY_OUTPUT + "assets-schema.json";

    FILE *fp = fopen(output.c_str(), "wb");

    char writeBuffer[65536];

    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
    document.Accept(writer);

    fclose(fp);
  }
}