#include "AssetsStorage.hpp"

#include "FileSystemManager.hpp"
#include "PakFileSystem.hpp"
#include "PakFile.hpp"
#include "PakFilesystemHeaders.hpp"

#include "rapidjson/document.h"

std::unique_ptr<AssetsStorage> AssetsStorage::s_instance = nullptr;

AssetsStorage::AssetsStorage()
{
  m_textureExtensions = { ".png", ".jpg", ".jpeg", ".bmp", ".tga", ".psd", ".hdr", ".pic" };
  m_fontExtensions    = { ".ttf" };

  m_relativePaths = false;

  LoadDefaultAssets();
}

AssetsStorage::~AssetsStorage()
{
}

sf::Texture &AssetsStorage::GetTexture(const std::string &textureName) const
{
  if (m_textures.find(textureName) == m_textures.end())
  {
    return *m_defaultTexture->GetAsset();
  }

  return *(m_textures.at(textureName))->GetAsset();
}

sf::Font &AssetsStorage::GetFont(const std::string &fontName) const
{
  if (m_fonts.find(fontName) == m_fonts.end())
  {
    return *m_defaultFont->GetAsset();
  }

  return *(m_fonts.at(fontName))->GetAsset();
}

void AssetsStorage::LoadTexture(const std::string &path)
{

}

void AssetsStorage::LoadFont(const std::string &path)
{

}

AssetsStorage &AssetsStorage::GetInstance()
{
  if (AssetsStorage::s_instance == nullptr)
  {
    AssetsStorage::s_instance = std::unique_ptr<AssetsStorage>(new AssetsStorage);
  }

  return *s_instance;
}

void AssetsStorage::LoadAssets(const std::string &path)
{
  std::shared_ptr<PakFileSystem> pakFileSystem = std::make_shared<PakFileSystem>();
  FileSystemManager &fileSystemManager = FileSystemManager::GetInstance();
  fileSystemManager.AddFilesystem("assets/", pakFileSystem);

  std::shared_ptr<File> assets = pakFileSystem->OpenFile(path, File::EFileMode::In);

  Timer assets_profile;

  assets_profile.Start();

  if (!assets)
  {
    FILE_LOG_ERROR("errors.txt", "[AssetsStorage][LoadAssets]: Failed to open pak file.");
    return;
  }

  if (!assets->IsOpen())
  {
    FILE_LOG_ERROR("errors.txt", "[AssetsStorage][LoadAssets]: Pak file is not open.");
    return;
  }

  PakFile_HeaderMetadata headerMetadata;

  assets->Read(reinterpret_cast<char*>(&headerMetadata), sizeof(PakFile_HeaderMetadata));

  for (auto i = 0; i < headerMetadata.m_filesCount; ++i)
  {
      PakFile_EntryMetadata entryMetadata;

      assets->Read(reinterpret_cast<char*>(&entryMetadata), sizeof(PakFile_EntryMetadata));

      const std::string entryFilepath { entryMetadata.m_filePath.data() };
      const std::string entryExtension = entryFilepath.substr(entryFilepath.find_last_of('.'));

      auto doesContaintExtension = [&entryExtension](const std::string& rhs) -> bool
      {
        return entryExtension == rhs;
      };

      auto is_texture = std::any_of(m_textureExtensions.cbegin(), m_textureExtensions.cend(), doesContaintExtension);
      auto is_font    = std::any_of(m_fontExtensions.cbegin(), m_fontExtensions.cend(), doesContaintExtension);

      const std::string baseFileName = entryFilepath.substr(entryFilepath.find_last_of("/\\") + 1);

      std::vector<uint8_t> fileData(entryMetadata.m_size);
      assets->Read(reinterpret_cast<char*>(fileData.data()), entryMetadata.m_size);

      if (is_texture)
      {
        std::unique_ptr<Asset<sf::Texture>> asset_texture = std::make_unique<Asset<sf::Texture>>(fileData);
        asset_texture->InitializeFromInternalData();

        m_textures.insert({ baseFileName, std::move(asset_texture) });
      }

      else if (is_font)
      {
        std::unique_ptr<Asset<sf::Font>> asset_font = std::make_unique<Asset<sf::Font>>(fileData);
        asset_font->InitializeFromInternalData();

        m_fonts.insert({ baseFileName, std::move(asset_font) });
      }
  }

  assets_profile.Stop();

  CONSOLE_LOG_INFO("[AssetsStorage][LoadAssets] ", assets_profile.GetElapsedTime<std::chrono::milliseconds>(), " ms.");
}

void AssetsStorage::LoadDefaultAssets()
{
  m_defaultTexture = std::make_unique<Asset<sf::Texture>>();
  m_defaultFont = std::make_unique<Asset<sf::Font>>();

  m_defaultTexture->InitializeFromExternalData("../assets/default/default-texture.png");
  m_defaultFont->InitializeFromExternalData("../assets/default/default-font.ttf");
}


void AssetsStorage::SetRelativePaths(bool state)
{
  m_relativePaths = state;
}

bool AssetsStorage::IsRelativePaths() const
{
  return m_relativePaths;
}