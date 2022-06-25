#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <map>

class AssetsManager
{

public:

  ~AssetsManager();

  static AssetsManager &GetInstance();

  sf::Texture &GetTexture(const std::string &textureName) const;
  sf::Font    &GetFont(const std::string &fontName) const;

private:

  AssetsManager();

private:

  static std::unique_ptr<AssetsManager> s_instance;

  std::map< std::string, std::shared_ptr<sf::Texture> > m_textures;
  std::map< std::string, std::shared_ptr<sf::Font> > m_fonts;
};