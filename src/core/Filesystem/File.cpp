#include "File.hpp"

void File::LoadFile(const std::string &path, std::ios_base::openmode mode)
{
    std::ifstream input(path, mode);
    std::ostringstream ss;
    ss << input.rdbuf();
    m_data = ss.str();
    m_path = path;
    m_filename = path.substr(path.find_last_of("/") + 1, path.length() - path.find_last_of("/")); 

    input.close();
}

void File::SetData(const std::string &data)
{
    m_data = data;
}

const std::string &File::GetData() const
{
  return m_data;
}

void File::SetType(const std::string &type)
{
  if (type == "textures" || type == "maps")
  {
    m_type = Type::Texture;
  }
  else if (type == "images")
  {
    m_type = Type::Image;
  }
  else if (type == "fonts")
  {
    m_type = Type::Font;
  }
  else if (type == "json")
  {
    m_type = Type::Json;
  }
  else
  {
    m_type = Type::Unknown;
  }
}

const std::string &File::GetFilename() const
{
  return m_filename;
}
