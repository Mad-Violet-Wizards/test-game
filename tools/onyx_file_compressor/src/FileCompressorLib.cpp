#pragma once

#include <new>

#include "Library.hpp"
#include "Compressor.hpp"
#include "AssetsContainer.hpp"
#include "AssetsJsonDescriptor.hpp"

#include "Log.hpp"

extern "C"
{

  ONYX_FILE_COMPRESSOR_API const char *GetAssetsDirectoryInput()
  {
    return ASSETS_DIRECTORY_INPUT.c_str();
  }

  ONYX_FILE_COMPRESSOR_API const char *GetAssetsDirectoryOutput()
  {
    return ASSETS_DIRECTORY_OUTPUT.c_str();
  }

  ONYX_FILE_COMPRESSOR_API void* CreateAssetsContainer(void)
  {
    return new(std::nothrow) AssetsContainer;
  }

  ONYX_FILE_COMPRESSOR_API void DestroyClass(void *ptr)
  {
    delete ptr;
  }

  ONYX_FILE_COMPRESSOR_API void Compress(void* ptr, const char *path, bool createOutputDirectory)
  {
    try
    {
      auto assetsContainer = static_cast<AssetsContainer*>(ptr);
      assetsContainer->CollectAssets(path, createOutputDirectory);

      Compressor::CompressPathes(assetsContainer->GetPathes());
      
      AssetsJsonDescriptor assetsJsonDescriptor;

      assetsJsonDescriptor.CreateJsonFile(assetsContainer->GetPathes());
    }
    catch(...)
    {
      LOG("Error while compressing assets.");
    }
  }
}