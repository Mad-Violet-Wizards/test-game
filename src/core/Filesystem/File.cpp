#include "File.hpp"

File::File(const FileInfo &fileInfo)
  : m_FileInfo(fileInfo)
  , m_isOpen(false)
  , m_isReadOnly(false)
{
}

const FileInfo &File::GetFileInfo() const
{
  return m_FileInfo;
}

bool File::IsOpen() const
{
  return m_isOpen;
}

bool File::IsReadOnly() const
{
  return m_isReadOnly;
}

void File::SetIsOpen(bool isOpen)
{
  m_isOpen = isOpen;
}

void File::SetIsReadOnly(bool isReadOnly)
{
  m_isReadOnly = isReadOnly;
}