#pragma once

#include <map>

#include "FileLog.hpp"

namespace OnyxCore
{
  namespace Containers
  {
    template <typename T, typename Key>
    constexpr static inline T &MapGetItem(const Key &key, const std::map<Key, T> &map)
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

    template <typename T, typename Key>
    constexpr static inline T &MapGetItem(const Key &key, const std::map<Key, std::shared_ptr<T>> &map)
    {
      auto item_pair = map.find(key);

      if (item_pair != map.end())
      {
        return *(item_pair) -> second;
      }
      else
      {
        FILE_LOG_ERROR("[MapOperations][Error] Key not found.");

        throw std::runtime_error("[MapOperations] Key not found.");
      }
    }
  }
}