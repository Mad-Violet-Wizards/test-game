#pragma once


#include "File.hpp"
#include "Objects/Asset.hpp"
#include "Design-Patterns/Singleton.hpp"

class AssetsStorage
{

public:

  AssetsStorage();
  ~AssetsStorage() = default;

  void LoadAssets(const std::string &path);
  void LoadDefaultAssets();

  void SetRelativePaths(bool state);
  bool IsRelativePaths() const;

  sf::Texture &GetTexture(const std::string &texturePath) const;
  sf::Font    &GetFont(const std::string &fontPath) const;

  void LoadTexture(const std::string &path);
  void LoadFont(const std::string &path);

private:

  std::vector<std::string> m_textureExtensions;
  std::vector<std::string> m_fontExtensions;

  std::unique_ptr<Asset<sf::Texture>> m_defaultTexture;
  std::unique_ptr<Asset<sf::Font>>    m_defaultFont;

  std::map<std::string, std::unique_ptr<Asset<sf::Texture>>> m_textures;
  std::map<std::string, std::unique_ptr<Asset<sf::Font>>>    m_fonts;

  bool m_relativePaths;
};

using AssetsStorageSingleton = Singleton<AssetsStorage>;