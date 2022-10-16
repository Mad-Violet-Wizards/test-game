#pragma once

#include <string>
#include <vector>

namespace OnyxTools
{
  namespace Compressor
  {
    class AssetsJsonDescriptor
    {

    public:

      enum class Type
      {
        Texture,
        Font,
        Image,
        Map,
        Animation,
        Unknown
      };

      AssetsJsonDescriptor() = default;
      ~AssetsJsonDescriptor() = default;

      void CreateJsonFile(const std::vector<std::string> &files);
    };
  }
}