#pragma once

#include "File.hpp"

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