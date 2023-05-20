#include "PakFileSystem.hpp"

#include "PakFile.hpp"

PakFileSystem::PakFileSystem()
  : m_isInitialized(false)
{
}

void PakFileSystem::Initialize()
{
  m_isInitialized = true;
}

void PakFileSystem::Shutdown()
{
  m_FileSet.clear();
  m_isInitialized = false;
}

bool PakFileSystem::IsInitialized() const
{
  return m_isInitialized;
}

bool PakFileSystem::IsReadOnly() const
{
  return true;
}

std::shared_ptr<File> PakFileSystem::OpenFile(const FileInfo &filePath, File::EFileMode mode)
{
  FileInfo fileInfo { filePath };

  auto file = FindFile(fileInfo);
  const bool fileExists = file != nullptr;

  if (!fileExists)
  {
    file.reset(new PakFile(fileInfo));
  }

  if (!file->Open(mode))
  {
    FILE_LOG_ERROR("errors.txt", "[PakFileSystem][OpenFile] Failed to open file: ", filePath.AbsolutePath());
  }

  if (!fileExists && file->IsOpen())
  {
    m_FileSet.insert(file);
  }

  return file;
}

bool PakFileSystem::CloseFile(std::shared_ptr<File> file)
{
  if (!file)
  {
    return false;
  }

  file->Close();
  return true;
}

bool PakFileSystem::CreateFile(const FileInfo &fileInfo)
{
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][CreateFile] Pak file system is read only.");
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][CreateFile] If you want to create a .pak file use pak-compiler.exe.");

  return false;
}

bool PakFileSystem::DeleteFile(const FileInfo &fileInfo)
{
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][DeleteFile] Pak file system is read only.");
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][DeleteFile] If you want to delete a .pak file use pak-compiler.exe.");

  return false;
}

bool PakFileSystem::RenameFile(const FileInfo &fileInfo, const FileInfo &dest)
{
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][RenameFile] Pak file system is read only.");
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][RenameFile] If you want to rename a .pak file use pak-compiler.exe.");

  return false;
}

bool PakFileSystem::CopyFile(const FileInfo &fileInfo, const FileInfo &dest)
{
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][CopyFile] Pak file system is read only.");
  FILE_LOG_WARNING("warnings.txt", "[PakFileSystem][CopyFile] If you want to copy a .pak file use pak-compiler.exe.");

  return false;
}

bool PakFileSystem::FileExists(const FileInfo &fileInfo) const
{
  return FindFile(fileInfo) != nullptr;
}

bool PakFileSystem::IsFile(const FileInfo &fileInfo) const
{
  /* Everything in .pak is a file. */
  return true;
}

bool PakFileSystem::IsDirectory(const FileInfo &fileInfo) const
{
  /* Everything in .pak is a file. */
  return false;
}

const std::set<std::shared_ptr<File>> &PakFileSystem::GetFileSet() const
{
  return m_FileSet;
}

std::shared_ptr<File> PakFileSystem::FindFile(const FileInfo &fileInfo) const
{
  auto it = std::find_if(m_FileSet.cbegin(), m_FileSet.cend(), [&fileInfo](const std::shared_ptr<File> &file)
  {
    return file->GetFileInfo() == fileInfo;
  });

  if (it == m_FileSet.cend())
  {
    return nullptr;
  }

  return *it;
}