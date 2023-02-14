#pragma once


#include "File.hpp"

enum class Type
{
  Texture = 0,
  Font = 1,
  Image = 2,
  Unknown = 3
};

class AssetsStorage
{

public:

  ~AssetsStorage();

  static AssetsStorage &GetInstance();

  void LoadAssets(const std::string &path);

  sf::Texture &GetTexture(const std::string &texturePath) const;
  sf::Font    &GetFont(const std::string &fontPath) const;
  sf::Image   &GetImage(const std::string &imagePath) const;

  void LoadTexture(const std::string &path);
  void LoadFont(const std::string &path);
  void LoadImage(const std::string &path);

private:

  AssetsStorage();

private:

  static std::unique_ptr<AssetsStorage> s_instance;

  std::vector<std::string> m_textureExtensions;
  std::vector<std::string> m_fontExtensions;
  std::vector<std::string> m_imageExtensions;

  std::map< std::string, std::shared_ptr<sf::Texture> > m_textures;
  std::map< std::string, std::shared_ptr<sf::Font> >    m_fonts;
  std::map< std::string, std::shared_ptr<sf::Image> >   m_images;
};