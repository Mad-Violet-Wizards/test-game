#include "FileStorage.hpp"

#include <iostream>

std::unique_ptr<FileStorage> FileStorage::s_instance = nullptr;

FileStorage::FileStorage()
{
}

FileStorage::~FileStorage()
{
  for (auto &file : m_files)
  {
    std::cout << "Deleting file: " << file -> GetFilename() << std::endl;
    delete file;
  }

  m_files.clear();
}

FileStorage &FileStorage::GetInstance()
{
  if (FileStorage::s_instance == nullptr)
  {
    FileStorage::s_instance = std::unique_ptr<FileStorage>(new FileStorage);
  }

  return *s_instance;
}

void FileStorage::InsertFile(File *file)
{
  m_files.insert(file);
}

bool FileStorage::Empty() const
{
  return m_files.empty();
}

size_t FileStorage::Size() const
{
  return m_files.size();
}

void FileStorage::Clear()
{
  m_files.clear();
}