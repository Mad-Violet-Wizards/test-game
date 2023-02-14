#pragma once


class File
{
  public:

    enum class Type
    {
      Texture,
      Font,
      Image,
      Json,
      Unknown
    };

    File() = default;
    ~File() = default;

    void LoadFile(const std::string &path, std::ios_base::openmode mode = std::ios_base::in);

    void SetData(const std::string &data);
    const std::string &GetData() const;

    void SetType(const std::string &type);
    void SetType(Type type) { m_type = type; };
    const Type GetType() const { return m_type; };

    void SetPath(const std::string &path) { m_path = path; };
    const std::string &GetPath() const { return m_path; };

    const std::string &GetFilename() const;

  private:

    Type m_type;

    std::string m_path;
    std::string m_data;
    std::string m_filename;
};