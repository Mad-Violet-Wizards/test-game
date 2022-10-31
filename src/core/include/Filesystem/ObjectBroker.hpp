#pragma once

#include <memory>

#include "File.hpp"
#include "FileDecompressor.hpp"

class ObjectBroker
{

  public:

    ObjectBroker() = default;
    ~ObjectBroker() = default;

    template <typename T>
    std::shared_ptr<T> CreateObjectFromFile(File *file, bool dataCompressed)
    {
      if (dataCompressed)
      {
        OnyxCore::Filesystem::DecompressFile(file);
      }

      std::shared_ptr<T> object = std::make_shared<T>();

      if (object -> loadFromMemory(file -> GetData().data(), file -> GetData().size()))
      {
        return object;
      }

      return nullptr;
    }

};