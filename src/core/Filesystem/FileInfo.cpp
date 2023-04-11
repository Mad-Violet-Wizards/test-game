#include "FileInfo.hpp"

FileInfo::FileInfo(const std::string &filePath)
{

}

FileInfo::FileInfo(const std::string &basePath, const std::string& fileName, bool isDir)
{

}

FileInfo::FileInfo(const FileInfo &other)
  : m_fileName(other.m_fileName)
  , m_baseName(other.m_baseName)
  , m_extension(other.m_extension)
  , m_absolutePath(other.m_absolutePath)
  , m_basePath(other.m_basePath)
  , m_isDir(other.m_isDir)
{

}

FileInfo::FileInfo(FileInfo &&other) noexcept
  : m_fileName(std::move(other.m_fileName))
  , m_baseName(std::move(other.m_baseName))
  , m_extension(std::move(other.m_extension))
  , m_absolutePath(std::move(other.m_absolutePath))
  , m_basePath(std::move(other.m_basePath))
  , m_isDir(other.m_isDir)
{

}

FileInfo &FileInfo::operator=(const FileInfo &other)
{
  if (this != &other)
  {
    m_fileName = other.m_fileName;
    m_baseName = other.m_baseName;
    m_extension = other.m_extension;
    m_absolutePath = other.m_absolutePath;
    m_basePath = other.m_basePath;
    m_isDir = other.m_isDir;
  }

  return *this;
}

FileInfo &FileInfo::operator=(FileInfo &&other) noexcept
{
  if (this != &other)
  {
    m_fileName = std::move(other.m_fileName);
    m_baseName = std::move(other.m_baseName);
    m_extension = std::move(other.m_extension);
    m_absolutePath = std::move(other.m_absolutePath);
    m_basePath = std::move(other.m_basePath);
    m_isDir = other.m_isDir;
  }

  return *this;
}

const std::string &FileInfo::GetName() const
{
  return m_fileName;
}

const std::string& FileInfo::BaseName() const
{
  return m_baseName;
}

const std::string& FileInfo::Extension() const
{
  return m_extension;
}

const std::string& FileInfo::AbsolutePath() const
{
  return m_absolutePath;
}

const std::string& FileInfo::BasePath() const
{
  return m_basePath;
}
 
bool FileInfo::IsDir() const
{
  return m_isDir;
}

void FileInfo::Init(const std::string& basePath, const std::string& fileName, bool isDir)
{

}