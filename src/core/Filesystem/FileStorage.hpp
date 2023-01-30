#pragma once

#include <set>
#include <memory>

#include "File.hpp"

// The file storage class is being represented by std::set container.
// There's no need to hold duplicate files in the storage.

class FileStorage
{

  public:

    ~FileStorage();

    static FileStorage &GetInstance();

    void InsertFile(File *file);

    bool Empty() const;

    size_t Size() const;

    void Clear();

  private:

    FileStorage();

  private:

    static std::unique_ptr<FileStorage> s_instance;

    std::set<File*> m_files;

};