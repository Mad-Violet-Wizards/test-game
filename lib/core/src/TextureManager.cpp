#include <iostream>
#include <filesystem>

#include "TextureManager.hpp"

TextureManager::TextureManager()
  : m_texturesDir("../assets/textures/")
{
  std::cout << "[TextureManager] Allocated new Texture Manager.\n";

  LoadTextureFiles();
}

TextureManager::~TextureManager()
{
  std::cout << "[TextureManager] Deallocated Texture Manager.\n";
}

//
// FIXME: We need to find better way to do it. Throw an exception? Use std::optional?
//

sf::Texture &TextureManager::GetTexture(const std::string &textureName) const
{
  auto texture = m_textures.find(textureName);

  if (texture != m_textures.end())
  {
    return *(texture) -> second;
  }
  else
  {
    throw std::runtime_error("[TextureManager][Error] Couldn't find the texture.");
  }
}

void TextureManager::LoadTextureFiles()
{
  try
  {
    if (std::filesystem::exists(m_texturesDir))
    {
      for (auto &entry : std::filesystem::directory_iterator(m_texturesDir))
      {
        std::filesystem::path file(entry);
        
        const char *supportedFileFormat = ".png";

        if (file.extension() == supportedFileFormat)
        {
          std::shared_ptr<sf::Texture> texture(new sf::Texture());

          if (!texture -> loadFromFile(entry.path().string()))
          {
            std::cout << "[TextureManager] Couldn't load texture.\n";
          }

          const std::string textureName = file.replace_extension().filename().string();

          m_textures.insert(std::pair< std::string, std::shared_ptr<sf::Texture> >(textureName, texture));
        }
        else
        {
          throw std::runtime_error("[TextureManager][Error] File format is not supported.\n");
        }
      }
    }
    else
    {
      std::cout << "[TextureManager][Warning] Texture directory is empty.\n";
    }
  }
  catch (const std::filesystem::filesystem_error &exception)
  {
    std::cout << exception.what() << "\n";
  }
  catch (const std::runtime_error &exception)
  {
    std::cout << exception.what() << "\n";
  }
}