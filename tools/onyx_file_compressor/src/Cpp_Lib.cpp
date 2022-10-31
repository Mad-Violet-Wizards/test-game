#include <string>

#include "Library.hpp"
#include "Compressor.hpp"
#include "AssetsContainer.hpp"
#include "AssetsJsonDescriptor.hpp"

#include "Log.hpp"

ONYX_FILE_COMPRESSOR_API std::string Cpp_DecompressString(const std::string &data)
{
  return OnyxTools::Compressor::Compressor::DecompressString(data);
}