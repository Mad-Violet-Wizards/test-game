#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <map>

#include "File.hpp"

class AssetsStorage
{

public:

  ~AssetsStorage();

  static AssetsStorage &GetInstance();

  void ParseAssetsSchema(const std::string &path);

  sf::Texture &GetTexture(const std::string &texturePath) const;
  sf::Font    &GetFont(const std::string &fontPath) const;
  sf::Image   &GetImage(const std::string &imagePath) const;

  void LoadTexture(const std::string &path, bool isCompressed);
  void LoadFont(const std::string &path, bool isCompressed);
  void LoadImage(const std::string &path, bool isCompressed);

  int GetAssetsLoadedCount() const { return m_assetsLoaded; }
  int GetAssetsCount() const { return m_totalAssets; }

private:

  AssetsStorage();

private:

  static std::unique_ptr<AssetsStorage> s_instance;

  std::map< std::string, std::shared_ptr<sf::Texture> > m_textures;
  std::map< std::string, std::shared_ptr<sf::Font> >    m_fonts;
  std::map< std::string, std::shared_ptr<sf::Image> >   m_images;

  int m_assetsLoaded = 0;
  int m_totalAssets = 0;
};