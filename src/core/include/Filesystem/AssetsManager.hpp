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

  void ParseAssetsSchema(const std::string &path);

  sf::Texture &GetTexture(const std::string &texturePath) const;
  sf::Font    &GetFont(const std::string &fontPath) const;
  sf::Image   &GetImage(const std::string &imagePath) const;

private:

  AssetsManager();

private:

  static std::unique_ptr<AssetsManager> s_instance;

  std::map< std::string, std::shared_ptr<sf::Texture> > m_textures;
  std::map< std::string, std::shared_ptr<sf::Font> >    m_fonts;
  std::map< std::string, std::shared_ptr<sf::Image> >   m_images;
};