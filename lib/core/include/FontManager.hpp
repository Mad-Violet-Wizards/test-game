#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class FontManager
{

public:

  FontManager();
  ~FontManager();

  sf::Font &GetFont(const std::string &fontName) const;

private:

  void LoadFontFiles();

  std::string m_fontsDir;
  std::map< std::string, std::shared_ptr<sf::Font> > m_fonts;

};