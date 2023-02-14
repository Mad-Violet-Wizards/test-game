#pragma once


namespace OnyxCore
{
  namespace Filesystem
  {
    void ReplaceExtension(std::string &path, const std::string &newExtension)
    {
      path = path.substr(0, path.find_last_of('.')) + newExtension;
    }

    std::string ReplaceExtension(const std::string &path, const std::string &newExtension)
    {
      std::string newPath = path;
      ReplaceExtension(newPath, newExtension);
      return newPath;
    }
  }
}
