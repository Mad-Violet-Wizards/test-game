#include "FileSystemManager.hpp"

std::unique_ptr<FileSystemManager> FileSystemManager::s_instance = nullptr;

FileSystemManager::~FileSystemManager()
{
  Shutdown();
}

FileSystemManager &FileSystemManager::GetInstance()
{
  if (!s_instance)
  {
    FileSystemManager::s_instance = std::unique_ptr<FileSystemManager>(new FileSystemManager);
  }

  return *s_instance;
}

void FileSystemManager::Initialize()
{
  for (auto &fileSystem : m_FileSystems)
  {
    fileSystem.second->Initialize();
  }
}

void FileSystemManager::Shutdown()
{
  for (auto &fileSystem : m_FileSystems)
  {
    fileSystem.second->Shutdown();
  }

  m_FileSystems.clear();
}

void FileSystemManager::AddFilesystem(const std::string &name, std::shared_ptr<FileSystem> fileSystem)
{
  if (fileSystem)
  {
    m_FileSystems[name] = fileSystem;
  }
}

void FileSystemManager::RemoveFilesystem(const std::string &name)
{
  m_FileSystems.erase(name);
}

bool FileSystemManager::FilesystemExists(const std::string &name) const
{
  return m_FileSystems.find(name) != m_FileSystems.end();
}

std::shared_ptr<FileSystem> FileSystemManager::GetFilesystem(const std::string &name) const
{
  if (FilesystemExists(name))
  {
    return m_FileSystems.at(name);
  }

  return nullptr;
}

std::shared_ptr<File> FileSystemManager::OpenFile(const FileInfo &fileInfo, File::EFileMode mode)
{
  std::shared_ptr<File> file;

  for (auto &fileSystem : m_FileSystems)
  {
    file = fileSystem.second->OpenFile(fileInfo, mode);

    if (file)
    {
      break;
    }
  }

  return file;
}

bool FileSystemManager::CloseFile(std::shared_ptr<File> file)
{
  if (!file)
  { 
    return false;
  }

  if (!file->IsOpen())
  {
    return false;
  }

  file->Close();
  return true;
}