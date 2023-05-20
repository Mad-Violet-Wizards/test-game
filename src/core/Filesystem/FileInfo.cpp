#include "FileInfo.hpp"

FileInfo::FileInfo(const std::string &filePath)
{
  auto found = filePath.find_last_of("/\\");

  if (found != std::string::npos)
  {
    const std::string basePath = filePath.substr(0, found);

    const std::string fileName = filePath.substr(found + 1);

    Init(basePath, fileName, false);
  }
}

FileInfo::FileInfo(const std::string &basePath, const std::string& fileName, bool isDir)
{
  Init(basePath, fileName, isDir);
}

const std::string &FileInfo::Filename() const
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
  m_basePath = basePath;
  m_fileName = fileName;
  m_isDir = isDir;

  if (m_basePath.back() != '/')
  {
    m_basePath += "/";
  }

  if (m_isDir && m_fileName.back() != '/')
  {
    m_fileName += "/";
  }

  if (m_fileName.front() == '/')
  {
    m_fileName = m_fileName.substr(1);
  }

  m_absolutePath = m_basePath + m_fileName;

  if (m_fileName.find_last_of(".") != std::string::npos)
  {
    m_extension = m_fileName.substr(m_fileName.find_last_of(".") + 1);
  }
}