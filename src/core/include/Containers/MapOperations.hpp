#pragma once

#include <map>
#include "FileLog.hpp"

template <typename Key, typename T>
constexpr static inline T &MapGetItem(const Key &key, std::map<Key, T> &map)
{
  if (map.find(key) != map.end())
  {
    return map[key];
  }
  else
  {
    FILE_LOG_ERROR("[MapOperations][Error] Key not found.");
  }
}

template <typename Key, typename T>
constexpr static inline T &MapGetItem(const Key &key, std::map<Key, std::shared_ptr<T>> &map)
{
  if (map.find(key) != map.end())
  {
    return *map[key];
  }
  else
  {
    FILE_LOG_ERROR("[MapOperations][Error] Key not found.");
  }
}