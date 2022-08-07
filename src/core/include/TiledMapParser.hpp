#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <map>

#include "tileson.hpp"

class TiledMapParser
{

  public:

    TiledMapParser() = default;
    ~TiledMapParser() = default;

    std::unique_ptr<tson::Map> ParseMap(const std::string &locationName);

    sf::Sprite *LoadAndStoreTilesetImage(const std::string &tilesetImagePath, const sf::Vector2f &position);

    fs::path GetTilesetImagePath(const tson::Tileset &tileset);

  private:

    std::map<std::string, std::unique_ptr<sf::Sprite>> m_sprites;
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};