#pragma once


#include "File.hpp"
#include "Objects/Asset.hpp"

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
  void LoadDefaultAssets();

  void SetRelativePaths(bool state);
  bool IsRelativePaths() const;

  sf::Texture &GetTexture(const std::string &texturePath) const;
  sf::Font    &GetFont(const std::string &fontPath) const;

  void LoadTexture(const std::string &path);
  void LoadFont(const std::string &path);

private:

  AssetsStorage();

private:

  static std::unique_ptr<AssetsStorage> s_instance;

  std::vector<std::string> m_textureExtensions;
  std::vector<std::string> m_fontExtensions;

  std::unique_ptr<Asset<sf::Texture>> m_defaultTexture;
  std::unique_ptr<Asset<sf::Font>>    m_defaultFont;

  std::map<std::string, std::unique_ptr<Asset<sf::Texture>>> m_textures;
  std::map<std::string, std::unique_ptr<Asset<sf::Font>>>    m_fonts;

  bool m_relativePaths;
};