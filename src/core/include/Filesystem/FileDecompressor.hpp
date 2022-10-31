#pragma once

#include <string>

#define ONYX_CORE_IMPORT __declspec(dllimport);

ONYX_CORE_IMPORT std::string Cpp_DecompressString(const std::string &data);

namespace OnyxCore
{
    namespace Filesystem
    {
      void DecompressFile(File *file)
      {
        file -> SetData(Cpp_DecompressString(file -> GetData()));
      }
    }
}