#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class TextureManager
{

public:

  TextureManager();
  ~TextureManager();

  sf::Texture &GetTexture(const std::string &textureName) const;

private:

  void LoadTextureFiles();

  std::string m_texturesDir;
  std::map< std::string, std::shared_ptr<sf::Texture> > m_textures;

};