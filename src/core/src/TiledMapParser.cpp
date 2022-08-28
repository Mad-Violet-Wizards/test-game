#include "TiledMapParser.hpp"

#include "Directory.hpp"
#include "Log.hpp"

std::shared_ptr<tson::Map> TiledMapParser::ParseMap(const std::string &locationName)
{
  tson::Tileson t;

  std::unique_ptr<tson::Map> map = t.parse(locationName);

  if (map -> getStatus() == tson::ParseStatus::OK)
  {
    for (auto &tileset : map -> getTilesets())
    {
      fs::path tilesetPath = GetTilesetImagePath(tileset);

      LoadAndStoreTilesetImage(tilesetPath.string(), { 0, 0 });
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

sf::Sprite *TiledMapParser::LoadAndStoreTilesetImage(const std::string  &tilesetImagePath, 
                                                     const sf::Vector2f &position)
{
  auto search = m_sprites.find(tilesetImagePath);

  if (search != m_sprites.end())
  {
    return search -> second.get();
  }
  else
  {
    if (fs::exists(tilesetImagePath) && fs::is_regular_file(tilesetImagePath))
    {
      std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

      bool imageFound = texture -> loadFromFile(tilesetImagePath);

      if (imageFound)
      {
        std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
        sprite -> setTexture(*texture);
        sprite -> setPosition(position);
        m_textures[tilesetImagePath] = std::move(texture);
        m_sprites[tilesetImagePath]  = std::move(sprite);
      }
      else
      {
        LOG_INFO("[TiledMapParser][LoadAndStoreTilesetImage] Image loading failed, path: ", tilesetImagePath);
      }
    }
    else
    {
      LOG_INFO("[TiledMapParser][LoadAndStoreTilesetImage] Tileset image not found: ", tilesetImagePath);
    }
  }

  return nullptr;
}

fs::path TiledMapParser::GetTilesetImagePath(const tson::Tileset &tileset)
{
  fs::path tilesetPath = fs::path(Directory::MAPS_DIRECTORY / tileset.getImage().filename());

  return tilesetPath;
}