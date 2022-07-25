#pragma once

#include <memory>
#include <filesystem>
#include <map>

#include "Log.hpp"

// TODO: Think of the better name for this file.
// TODO: Think of the better name for this function.

template <typename T, typename S>
constexpr void CreateFilesMap(const S &directory, 
                              const S &supportedFileFormat,
                              std::map < std::string, std::shared_ptr<T> > &map)
{
  if (std::filesystem::exists(directory))
  {
    for (auto &entry : std::filesystem::directory_iterator(directory))
    {
      std::filesystem::path file(entry);

      if (file.extension() == supportedFileFormat)
      {
        std::shared_ptr<T> SFML_OBJECT(new T);

        if (!SFML_OBJECT -> loadFromFile(entry.path().string()))
        {
          std::cout << "[FileLoader] Couldn't load the file.\n";
        }

        const std::string name = file.replace_extension().filename().string();

        map.insert(std::pair< std::string, std::shared_ptr<T> >(name, SFML_OBJECT));
      }
      else
      {
        LOG_ERROR("[FileLoader][Error] File format is not supported.");
      }
    }
  }
  else
  {
    LOG_WARNING("[FileLoader][Warning] Directory does not exists.");
  }
}

template<typename T, typename Key>
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
  }
}


