#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <map>

#include "tileson.hpp"

class TiledMapParser
{

  public:

    TiledMapParser();
    ~TiledMapParser() = default;

    std::shared_ptr<tson::Map> ParseMap(const std::string &locationName);

    sf::Sprite *LoadAndStoreTilesetImage(const std::string &imageFile, const sf::Vector2f &position);

    sf::Vector2f GetTileOffset(int tileId, tson::Map *map, tson::Tileset *tileset);

    //
    // CURRENTLY UNUSED.
    //

    fs::path GetTilesetImagePath(const tson::Tileset &tileset);

  private:

    fs::path m_basePath;

    std::shared_ptr<tson::Map> m_map;

    std::map<std::string, std::unique_ptr<sf::Sprite>> m_sprites;
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};