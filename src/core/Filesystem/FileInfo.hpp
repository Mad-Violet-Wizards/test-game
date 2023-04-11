#pragma once

class FileInfo
{
  public:

    FileInfo() = default;
    ~FileInfo() = default;

    FileInfo(const std::string& filePath);
    FileInfo(const std::string& basePath, const std::string& fileName, bool isDir);

    FileInfo(const FileInfo& other);
    FileInfo(FileInfo&& other) noexcept;

    FileInfo& operator=(const FileInfo& other);
    FileInfo& operator=(FileInfo&& other) noexcept;

    [[nodiscard]] const std::string &GetName() const;
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