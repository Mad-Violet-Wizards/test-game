#include "TiledMapParser.hpp"

#include "Directory.hpp"
#include "Log.hpp"

TiledMapParser::TiledMapParser() : m_basePath("../assets/maps/") { }

std::shared_ptr<tson::Map> TiledMapParser::ParseMap(const std::string &locationName)
{
  tson::Tileson t;

  std::unique_ptr<tson::Map> map = t.parse(locationName);

  if (map -> getStatus() == tson::ParseStatus::OK)
  {
    for (auto &tilesetFile : map -> getTilesets())
    {
      LOG_INFO("[TiledMapParser][ParseMap] Tileset file: ", tilesetFile.getImage().generic_string());

      LoadAndStoreTilesetImage(tilesetFile.getImage().generic_string(), { 0, 0 });
    }

    LOG_INFO("[TiledMapParser][ParseMap] Map parsed successfully.");

    m_map = std::move(map);

    return m_map;
  }
  else
  {
    LOG_INFO("[TiledMapParser][ParseMap] Map parsing failed, reason: ", map -> getStatusMessage());
  }

  return nullptr;
}

sf::Sprite *TiledMapParser::LoadAndStoreTilesetImage(const std::string  &imageFile,
                                                     const sf::Vector2f &position)
{
  if (m_textures.count(imageFile) == 0)
  {
    fs::path path = m_basePath / imageFile;

    if (fs::exists(path) && fs::is_regular_file(path))
    {
      std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

      bool imageFound = texture -> loadFromFile(path.generic_string());

      if (imageFound)
      {
        std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();

        sprite -> setTexture(*texture);

        sprite -> setPosition(position);

        m_textures[imageFile] = std::move(texture);
        m_sprites[imageFile] = std::move(sprite);
      }
      else
      {
        LOG_INFO("[TiledMapParser][LoadAndStoreTilesetImage] Image file not found: ", path.generic_string());
      }
    }
    else
    {
      LOG_WARNING("[TiledMapParser][LoadAndStoreTilesetImage] Path not found/This is not file: ", path.generic_string());
    }
  }

  if (m_sprites.count(imageFile) > 0)
  {
    return m_sprites[imageFile].get();
  }

  LOG_WARNING("[TiledMapParser][LoadAndStoreTilesetImage] Returning nullptr.\n");

  return nullptr;

}

sf::Vector2f TiledMapParser::GetTileOffset(int tileId, tson::Map *map, tson::Tileset *tileset)
{
  uint32_t firstId = tileset -> getFirstgid();

  int columns = tileset -> getColumns();
  int rows = tileset -> getTileCount() / columns;

  uint32_t lastId = (tileset -> getFirstgid() + tileset -> getTileCount()) - 1;

  if (tileId >= firstId && tileId <= lastId)
  {
    uint32_t baseTilePosition = (tileId - firstId);

    int tileModX = (baseTilePosition % columns);
    int currentRow = (baseTilePosition / columns);
    int offsetX = (tileModX != 0) ? ((tileModX) * map -> getTileSize().x) : (0 * map -> getTileSize().x);
    int offsetY = (currentRow < rows - 1) ? (currentRow * map -> getTileSize().y) : ((rows - 1) * map -> getTileSize().y);

    return sf::Vector2f(static_cast<float>(offsetX), static_cast<float>(offsetY));
  }

  return { 0.f, 0.f };
}

fs::path TiledMapParser::GetTilesetImagePath(const tson::Tileset &tileset)
{
  fs::path tilesetPath = fs::path(Directory::MAPS_DIRECTORY / tileset.getImage().filename());

  return tilesetPath;
}