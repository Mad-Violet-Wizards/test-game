#pragma once

#include "FileInfo.hpp"

class File
{
  public:

  enum class EFileMode
  {
    In,
    Out,
    ReadWrite,
    Append,
    Truncate
  };

  enum class Origin
  {
    Begin,
    End,
    Current
  };

  public:

    File() = default;
    File(const FileInfo &fileInfo);

    virtual ~File() { };

    virtual const FileInfo &GetFileInfo() const;

    virtual bool Open(EFileMode mode) = 0;
    virtual void Close() = 0;

    virtual uint64_t Read(void *buffer, size_t size) = 0;
    virtual uint64_t Write(const uint8_t *buffer, uint64_t size) = 0;

    virtual uint64_t Seek(uint64_t offset, Origin origin) = 0;
    virtual uint64_t Tell() = 0;
    virtual uint64_t Size() = 0;
    virtual bool IsEOF() const = 0;

    virtual bool IsOpen() const;
    virtual bool IsReadOnly() const = 0;

    template<typename T>
    bool Read(T &value)
    {
      return (Read(reinterpret_cast<uint8_t*>(&value), sizeof(T)) == sizeof(value));
    }

    template<typename T>
    uint64_t Write(const T &value)
    {
      return Write(reinterpret_cast<const uint8_t*>(&value), sizeof(T));
    }

  protected:

    void SetIsOpen(bool isOpen);
    void SetIsReadOnly(bool isReadOnly);

  private:

    FileInfo m_FileInfo;
    bool m_isOpen = false;
    bool m_isReadOnly = false;
    EFileMode m_FileMode;
};