#pragma once

#include "File.hpp"
#include "FileInfo.hpp"

class FileSystem
{

  public:

    FileSystem() = default;
    virtual ~FileSystem() = default;

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;

    virtual bool IsInitialized() const = 0;
    virtual bool IsReadyOnly() const = 0;

    virtual std::shared_ptr<File> OpenFile(const FileInfo  &fileInfo, File::EFileMode mode) = 0;
    virtual bool CloseFile(std::shared_ptr<File> file) = 0;
    virtual bool CreateFile(const FileInfo &fileInfo)  = 0;
    virtual bool DeleteFile(const FileInfo &fileInfo) = 0;
    virtual bool RenameFile(const FileInfo &fileInfo, const FileInfo &dest) = 0;
    virtual bool CopyFile(const FileInfo &fileInfo, const FileInfo &dest) = 0;

    virtual bool FileExists(const FileInfo &fileInfo) const = 0;
    virtual bool IsFile(const FileInfo &fileInfo) const = 0;
    virtual bool IsDirectory(const FileInfo &fileInfo) const = 0;

    virtual const std::set<std::shared_ptr<File>> &GetFileSet() const

    virtual const std::string& GetBasePath() const = 0;

  public:

    std::set<std::shared_ptr<File>> m_FileSet;
};