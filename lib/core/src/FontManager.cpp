#include <iostream>
#include <filesystem>

#include "FontManager.hpp"

FontManager::FontManager()
  : m_fontsDir("../assets/fonts/")
{
  std::cout << "[FontManager] Allocated new Font Manager.\n";

  LoadFontFiles();
}

FontManager::~FontManager()
{
  std::cout << "[FontManager] Deallocated Font Manager.\n";
}

//
// FIXME: We need to find better way to do it. Throw an exception? Use std::optional?
//

sf::Font &FontManager::GetFont(const std::string &fontName) const
{
  auto font = m_fonts.find(fontName);

  if (font != m_fonts.end())
  {
    return *(font) -> second;
  }
  else
  {
    throw std::runtime_error("[FontManager][Error] Couldn't find the font.");
  }
}

void FontManager::LoadFontFiles()
{
  try
  {
    if (std::filesystem::exists(m_fontsDir))
    {
      for (auto &entry : std::filesystem::directory_iterator(m_fontsDir))
      {
        std::filesystem::path file(entry);
        
        const char *supportedFileFormat = ".ttf";

        if (file.extension() == supportedFileFormat)
        {
          std::shared_ptr<sf::Font> font(new sf::Font());

          if (!font -> loadFromFile(entry.path().string()))
          {
            std::cout << "[FontManager] Couldn't load font.\n";
          }

          const std::string fontName = file.replace_extension().filename().string();

          m_fonts.insert(std::pair< std::string, std::shared_ptr<sf::Font> >(fontName, font));
        }
        else
        {
          throw std::runtime_error("[FontManager][Error] File format is not supported.\n");
        }
      }
    }
    else
    {
      std::cout << "[FontManager][Warning] Font directory is empty.\n";
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
