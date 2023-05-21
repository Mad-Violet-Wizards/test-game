#pragma once

#include <array>

class PakFile_HeaderMetadata
{
  public:

    PakFile_HeaderMetadata() = default;

    PakFile_HeaderMetadata(uint32_t filesCount, uint32_t version)
    : m_filesCount { filesCount }
    , m_version { version }
    { }

    ~PakFile_HeaderMetadata() = default;

  public:

    uint32_t m_filesCount;
    uint32_t m_version;
};

class PakFile_EntryMetadata
{
  public:

    PakFile_EntryMetadata() = default;

    PakFile_EntryMetadata(const std::array<char, 256> &filePath, uint32_t offset, uint32_t size)
    : m_filePath { filePath }
    , m_offset { offset }
    , m_size { size }
    { }

    ~PakFile_EntryMetadata() = default;

  public:

    std::array<char, 256> m_filePath;
    uint32_t m_offset;
    uint32_t m_size;
};