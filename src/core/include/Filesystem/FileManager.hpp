#pragma once

#include <memory>
#include <filesystem>
#include <map>
#include <initializer_list>

#include "Log.hpp"

// TODO: Think of the better name for this file.
// TODO: Think of the better name for this function.

// UNUSED.
// template <typename T, typename Key = std::string>
// constexpr void ParseAssetsToMap(const Key &directory,
//                               const std::initializer_list<const char*> &supportedFileFormats,
//                               std::map < Key, std::shared_ptr<T> > &map)
// {
//   if (std::filesystem::exists(directory))
//   {
//     for (auto &entry : std::filesystem::directory_iterator(directory))
//     {
//       std::filesystem::path file(entry);

//       bool fileFormatSupported = false;

//       for (const Key &supportedFileFormat : supportedFileFormats)
//       {
//         if (file.extension() == supportedFileFormat)
//         {
//           fileFormatSupported = true;
//         }
//       }

//       if (fileFormatSupported)
//       {
//         std::shared_ptr<T> SFML_OBJECT = std::make_shared<T>();

//         if (!SFML_OBJECT -> loadFromFile(entry.path().string()))
//         {
//           std::cout << "[FileLoader] Couldn't load the file.\n";
//         }

//         const Key name = file.filename().string();

//         map.insert(std::pair< Key, std::shared_ptr<T> >(name, SFML_OBJECT));
//       }
//       else
//       {
//         LOG_ERROR("[FileLoader][Error] File format is not supported.");
//       }
//     }
//   }
//   else
//   {
//     LOG_WARNING("[FileLoader][Warning] Directory does not exists.");
//   }
// }

template<typename T, typename Key = std::string>
constexpr T &FindInFilesMap(const Key &name, const std::map< Key, std::shared_ptr<T> > &map)
{
  auto SFML_OBJECT = map.find(name);

  if (SFML_OBJECT != map.end())
  {
    return *(SFML_OBJECT) -> second;
  }
  else
  {
    LOG_ERROR("[FileManager][Error] Couldn't find the object associated with this name.");

    std::shared_ptr<T> EMPTY_SFML_OBJECT = std::make_shared<T>();

    return *(EMPTY_SFML_OBJECT);
  }
}


