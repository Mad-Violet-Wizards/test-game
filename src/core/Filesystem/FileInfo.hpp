#pragma once

class FileInfo
{
  public:

    FileInfo() = default;
    ~FileInfo() = default;

    FileInfo(const std::string& filePath);
    FileInfo(const std::string& basePath, const std::string& fileName, bool isDir);

    FileInfo(const FileInfo& other) = default;
    FileInfo(FileInfo&& other) noexcept = default;

    FileInfo& operator=(const FileInfo& other) = default;
    FileInfo& operator=(FileInfo&& other) noexcept = default;

    [[nodiscard]] const std::string& Filename() const;
    [[nodiscard]] const std::string& BaseName() const;
    [[nodiscard]] const std::string& Extension() const;
    [[nodiscard]] const std::string& AbsolutePath() const;
    [[nodiscard]] const std::string& BasePath() const;

    bool IsDir() const;

  private:

    void Init(const std::string& basePath, const std::string& fileName, bool isDir);

  private:

    std::string m_fileName;
    std::string m_baseName;
    std::string m_extension;
    std::string m_absolutePath;
    std::string m_basePath;

    bool m_isDir;
};

inline bool operator==(const FileInfo& lhs, const FileInfo& rhs)
{
  return lhs.AbsolutePath() == rhs.AbsolutePath();
}

inline std::ostream& operator<<(std::ostream& os, const FileInfo& fileInfo)
{
  os << "\n=== FileInfo === \n"
     << "Filename: "     << fileInfo.Filename() << "\n"
     << "BaseName: "     << fileInfo.BaseName() << "\n"
     << "Extension: "    << fileInfo.Extension() << "\n"
     << "AbsolutePath: " << fileInfo.AbsolutePath() << "\n"
     << "BasePath: "     << fileInfo.BasePath() << "\n";

  return os;
}