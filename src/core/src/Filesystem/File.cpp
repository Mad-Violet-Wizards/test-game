#include "File.hpp"

#include <sstream>

void File::LoadFile(const std::string &path, std::ios_base::openmode mode)
{
    std::ifstream input(path, mode);
    std::ostringstream ss;
    ss << input.rdbuf();
    m_data = ss.str();

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