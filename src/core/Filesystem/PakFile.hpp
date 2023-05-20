#pragma once

#include "File.hpp"

struct PakFile_HeaderMetadata
{
  PakFile_HeaderMetadata()
  : m_filesCount { 0 }
  , m_version { 0 }
  {
    
  }

  ~PakFile_HeaderMetadata() = default;

  uint32_t m_filesCount;
  uint32_t m_version;
};

struct PakFile_EntryMetadata
{
  PakFile_EntryMetadata() = default;

  PakFile_EntryMetadata(const std::array<char, 256> &filePath, uint32_t offset, uint32_t size)
  : m_filePath { filePath }
  , m_offset { offset }
  , m_size { size }
  {
    
  }

  ~PakFile_EntryMetadata() = default;

  std::array<char, 256> m_filePath;
  uint32_t m_offset;
  uint32_t m_size;
};

class PakFile : public File
{

  public:

    PakFile(const FileInfo &fileInfo);
    virtual ~PakFile();

    virtual bool Open(EFileMode mode) override;
    virtual void Close() override;

    virtual uint64_t Read(void *buffer, size_t size) override;
    virtual uint64_t Write(const uint8_t *buffer, uint64_t size) override;

    virtual uint64_t Seek(uint64_t offset, Origin origin) override;
    virtual uint64_t Tell() override;
    virtual uint64_t Size() override;
    virtual bool IsEOF() const override;

    virtual bool IsReadOnly() const override;

  private:

    mutable std::fstream m_FileStream;
    size_t m_FileSize;

    void UpdateFileSize();

};