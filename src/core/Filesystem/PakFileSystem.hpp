#pragma once

#include "FileSystem.hpp"

class PakFileSystem : public FileSystem
{
  
    public:
  
      PakFileSystem();
      virtual ~PakFileSystem() = default;
  
      void Initialize() override;
      void Shutdown() override;
  
      bool IsInitialized() const override;
      bool IsReadOnly() const override;
  
      std::shared_ptr<File> OpenFile(const FileInfo  &fileInfo, File::EFileMode mode) override;
      bool CloseFile(std::shared_ptr<File> file) override;
      bool CreateFile(const FileInfo &fileInfo)  override;
      bool DeleteFile(const FileInfo &fileInfo) override;
      bool RenameFile(const FileInfo &fileInfo, const FileInfo &dest) override;
      bool CopyFile(const FileInfo &fileInfo, const FileInfo &dest) override;
  
      bool FileExists(const FileInfo &fileInfo) const override;
      bool IsFile(const FileInfo &fileInfo) const override;
      bool IsDirectory(const FileInfo &fileInfo) const override;
  
      const std::set<std::shared_ptr<File>> &GetFileSet() const override;
  
    private:

      std::shared_ptr<File> FindFile(const FileInfo &fileInfo) const;

    private:

      bool m_isInitialized;
};