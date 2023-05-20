#pragma once

#include <map>

#include "FileSystem.hpp"
#include "File.hpp"

class FileSystemManager
{
    public:

      ~FileSystemManager();

      static FileSystemManager &GetInstance();

      void Initialize();
      void Shutdown();

      void AddFilesystem(const std::string &name, std::shared_ptr<FileSystem> fileSystem);
      void RemoveFilesystem(const std::string &name);
      bool FilesystemExists(const std::string &name) const;

      std::shared_ptr<FileSystem> GetFilesystem(const std::string &name) const;

      std::shared_ptr<File> OpenFile(const FileInfo  &fileInfo, File::EFileMode mode);
      bool CloseFile(std::shared_ptr<File> file);
    
    private:

      FileSystemManager() = default;

      static std::unique_ptr<FileSystemManager> s_instance;

    private:

      std::unordered_map<std::string, std::shared_ptr<FileSystem>> m_FileSystems;
};