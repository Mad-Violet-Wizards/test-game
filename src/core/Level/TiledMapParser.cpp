#include "TiledMapParser.hpp"

TiledMapParser::TiledMapParser() : m_basePath("../assets/maps/") { }

std::shared_ptr<tson::Map> TiledMapParser::ParseMap(const std::string &locationName)
{
  tson::Tileson t;

  std::unique_ptr<tson::Map> map = t.parse(locationName);

  if (map -> getStatus() == tson::ParseStatus::OK)
  {
    FILE_LOG_INFO("debug.txt", "[TiledMapParser][ParseMap] Map parsed successfully.");

    m_map = std::move(map);

    return m_map;
  }
  else
  {
    FILE_LOG_INFO("debug.txt", "[TiledMapParser][ParseMap] Map parsing failed, reason: ", map -> getStatusMessage());
  }

  return nullptr;
}

sf::Sprite *TiledMapParser::GetTilesetImage(const std::string  &imageFile,
                                            const sf::Vector2f &position)
{
  if (m_sprites.count(imageFile) == 0)
  {
    std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();

    sprite -> setTexture(AssetsStorage::GetInstance().GetTexture(imageFile));
    sprite -> setPosition(position);

    m_sprites[imageFile] = std::move(sprite);
  }

  if (m_sprites.count(imageFile) > 0)
  {
    return m_sprites[imageFile].get();
  }

  FILE_LOG_WARNING("debug.txt", "[TiledMapParser][LoadAndStoreTilesetImage] Returning nullptr.\n");

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
  fs::path tilesetPath = fs::path("assets/maps/" / tileset.getImage().filename());

  return tilesetPath;
}