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
  std::ios_base::openmode openMode = std::ios_base::binary;

  switch (mode)
  {
    case EFileMode::In:
      openMode |= std::ios_base::in;
      SetIsReadOnly(true);
      break;
    case EFileMode::Out:       [[fallthrough]];
    case EFileMode::ReadWrite: [[fallthrough]];
    case EFileMode::Append:    [[fallthrough]];
    case EFileMode::Truncate:  [[fallthrough]];
    default:
      FILE_LOG_WARNING("warnings.txt", "[PakFile][Open] Failed to open file (pak is read-only): ", GetFileInfo().AbsolutePath());
      return false;
  }

  m_FileStream.open(GetFileInfo().AbsolutePath(), openMode);

  if (m_FileStream.is_open())
  {
    SetIsOpen(true);
    UpdateFileSize();

    return true;
  }

  FILE_LOG_WARNING("warnings.txt", "[PakFile][Open] Failed to open file: ", GetFileInfo().AbsolutePath());
  return false;
}

void PakFile::Close()
{
  if (IsOpen())
  {
    m_FileStream.close();
    SetIsOpen(false);
  }
}

uint64_t PakFile::Read(void *buffer, size_t size)
{
  if (!IsOpen())
  {
    return 0;
  }

  m_FileStream.read(reinterpret_cast<char*>(buffer), size);
  return static_cast<uint64_t>(m_FileStream.gcount());
}

uint64_t PakFile::Write(const uint8_t *buffer, uint64_t size)
{
  if (!IsOpen() || IsReadOnly() || !m_FileStream.good())
  {
    return 0;
  }

  m_FileStream.write(reinterpret_cast<const char*>(buffer), size);
  return static_cast<uint64_t>(m_FileStream.gcount());
}

uint64_t PakFile::Seek(uint64_t offset, Origin origin)
{
  if (!IsOpen())
  {
    return 0;
  }

  std::ios_base::seekdir seekDir;

  switch (origin)
  {
    case Origin::Begin:
      seekDir = std::ios_base::beg;
      break;
    case Origin::End:
      seekDir = std::ios_base::end;
      break;
    case Origin::Current:
      seekDir = std::ios_base::cur;
      break;
    default:
      return 0;
  }

  m_FileStream.seekg(offset, seekDir);
  return static_cast<uint64_t>(m_FileStream.tellg());
}

uint64_t PakFile::Tell()
{
  if (!IsOpen())
  {
    return 0;
  }

  return static_cast<uint64_t>(m_FileStream.tellg());
}

uint64_t PakFile::Size()
{
  if (!IsOpen())
  {
    return 0;
  }

  return m_FileSize;
}

bool PakFile::IsEOF() const
{
  return m_FileStream.eof();
}

bool PakFile::IsReadOnly() const
{
  return true;
}

void PakFile::UpdateFileSize()
{
  if (!IsOpen())
  {
    return;
  }

  m_FileStream.seekg(0, std::ios_base::end);
  m_FileSize = static_cast<uint64_t>(m_FileStream.tellg());
  m_FileStream.seekg(0, std::ios_base::beg);
}