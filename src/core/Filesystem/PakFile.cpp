#include "PakFile.hpp"

PakFile::PakFile(const FileInfo &fileInfo)
  : File{ fileInfo }
  , m_FileSize { 0 }
{ }

PakFile::~PakFile()
{
  Close();
}

bool PakFile::Open(EFileMode mode)
{
  if (IsOpen())
  {
    return;
  }

  std::ios_base::openmode openMode = std::ios_base::binary;

  switch (mode)
  {
    case EFileMode::In:
      openMode |= std::ios_base::in;
      SetIsReadOnly(true);
      break;
    case EFileMode::Out:       [[fallthrough]]
    case EFileMode::ReadWrite: [[fallthrough]]
    case EFileMode::Append:    [[fallthrough]]
    case EFileMode::Truncate:  [[fallthrough]]
    default:
      FILE_LOG_WARNING("warnings.txt", "PakFile::Open - Failed to open file (pak is read-only): ", GetFileInfo().GetPath());
      return false;
  }

  m_FileStream.open(GetFileInfo().GetPath(), openMode);

  if (m_FileStream.is_open())
  {
    SetIsOpen(true);
    UpdateFileSize();

    return true;
  }

  FILE_LOG_WARNING("warnings.txt", "PakFile::Open - Failed to open file: ", GetFileInfo().GetPath());
  return false;
}