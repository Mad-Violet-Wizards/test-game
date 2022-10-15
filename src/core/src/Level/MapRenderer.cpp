#include <memory>

#include "MapRenderer.hpp"
#include "AssetsManager.hpp"
#include "Log.hpp"

void MapRenderer::Update(float deltaTime)
{
  for (auto &[id, animation] : m_animationUpdateQueue)
  {
    animation -> update(deltaTime * 1000);
  }
}

void MapRenderer::DrawLayer(Window &window, tson::Layer &layer)
{
  switch (layer.getType())
  {
    case tson::LayerType::TileLayer:
    {
      DrawTileLayer(window, layer);
      break;
    }
    case tson::LayerType::ObjectGroup:
    {
      DrawObjectGroup(window, layer);
      break;
    }
    case tson::LayerType::ImageLayer:
    {
      DrawImageLayer(window, layer);
      break;
    }
    case tson::LayerType::Group:
    {
      for (auto &l : layer.getLayers())
      {
        DrawLayer(window, l);
      }

      break;
    }
    default:
    {
      break;
    }
  }
}

void MapRenderer::DrawTileLayer(Window &window, tson::Layer &layer)
{

  //
  // FIXME: Animated tiles has one issue - all animations that are
  // created on FIRSTLY added tileset to the map
  // are parsed and rendered okay. For every tileset that is
  //  added after first tileset, the animations are not rendered okay.
  //  This might be a bug in Tileson.
  //

  for (auto &[pos, tileObject] : layer.getTileObjects())
  {
    tson::Tileset *tileset = tileObject.getTile() -> getTileset();
    tson::Rect drawingRect;

    bool animated = tileObject.getTile() -> getAnimation().any();

    if (animated)
    {
      uint32_t ownerId = tileObject.getTile() -> getId();

      if(m_animationUpdateQueue.count(ownerId) == 0)
      {
        m_animationUpdateQueue[ownerId] = &tileObject.getTile() -> getAnimation();
      }

      uint32_t tileId = tileObject.getTile() -> getAnimation().getCurrentTileId();

      tson::Tile *animatedTile = tileset -> getTile(tileId);

      if (animatedTile != nullptr)
      {
        drawingRect = animatedTile -> getDrawingRect();
      }
    }
    else
    {
      drawingRect = tileObject.getDrawingRect();
    }

    sf::Sprite *sprite = m_tiledMapParser.GetTilesetImage(tileset -> getImage().generic_string(), { 0, 0 });

    if (sprite != nullptr)
    {
      tson::Vector2f position = tileObject.getPosition();

      sf::Vector2f scale = sprite -> getScale();
      sf::Vector2f originalScale = scale;
      
      float rotation = sprite -> getRotation();
      float originalRotation = rotation;

      sf::Vector2f origin { static_cast<float>(drawingRect.width) / 2, 
                            static_cast<float>(drawingRect.height) / 2 };

      if (tileObject.getTile() -> hasFlipFlags(tson::TileFlipFlags::Horizontally))
      {
        scale.x = -scale.x;
      }
      if (tileObject.getTile() -> hasFlipFlags(tson::TileFlipFlags::Vertically))
      {
        scale.y = -scale.y;
      }
      if (tileObject.getTile() -> hasFlipFlags(tson::TileFlipFlags::Diagonally))
      {
        rotation += 90.f;
      }

      position = { position.x + origin.x, position.y + origin.y };
      sprite -> setOrigin(origin);
      sprite -> setTextureRect({ drawingRect.x, drawingRect.y, drawingRect.width, drawingRect.height });
      sprite -> setPosition({ position.x, position.y });
      sprite -> setScale(scale);
      sprite -> setRotation(rotation);

      window.Draw(*sprite);

      sprite -> setScale(originalScale);
      sprite -> setRotation(originalRotation);
    }
  }

}

void MapRenderer::DrawObjectGroup(Window &window, tson::Layer &layer)
{
  auto *map = layer.getMap();

  for (auto &obj : layer.getObjects())
  {
    if (obj.getProperties().getValue<bool>("drawable") == true)
    {
      switch(obj.getObjectType())
      {
        case tson::ObjectType::Object:
        {
          tson::Tileset *tileset = map -> getTilesetByGid(obj.getGid());
          sf::Vector2f offset = m_tiledMapParser.GetTileOffset(obj.getGid(), map, tileset);

          sf::Sprite *sprite = m_tiledMapParser.GetTilesetImage(tileset -> getImage().generic_string(), { 0, 0 });

          sf::Vector2f position = { static_cast<float>(obj.getPosition().x), static_cast<float>(obj.getPosition().y) };

          if (sprite != nullptr)
          {
            sf::Vector2f scale = { static_cast<float>(obj.getSize().x) / static_cast<float>(map -> getTileSize().x),
                                    static_cast<float>(obj.getSize().y) / static_cast<float>(map -> getTileSize().y) };

            sf::Vector2f originalScale = scale;

            float rotation = obj.getRotation();
            float originalRotation = rotation;

            sf::Vector2f origin { (static_cast<float>(map -> getTileSize().x) / 2),
                                  (static_cast<float>(map -> getTileSize().y) / 2) };

            if (obj.hasFlipFlags(tson::TileFlipFlags::Horizontally))
            {
              scale.x = -scale.x;
            }
            if (obj.hasFlipFlags(tson::TileFlipFlags::Vertically))
            {
              scale.y = -scale.y;
            }
            if (obj.hasFlipFlags(tson::TileFlipFlags::Diagonally))
            {
              rotation += 90.f;
            }

            position = { position.x + origin.x, position.y + origin.y };

            sprite -> setOrigin(origin);
            sprite -> setTextureRect( {static_cast<int>(offset.x),
                                      static_cast<int>(offset.y),
                                      map -> getTileSize().x,
                                      map -> getTileSize().y });

            sprite -> setPosition( {position.x, position.y - map -> getTileSize().y });
            sprite -> setScale(scale);
            sprite -> setRotation(rotation);

            window.Draw(*sprite);

            sprite -> setScale(originalScale);
            sprite -> setRotation(originalRotation);
          }

          break;
        }
        case tson::ObjectType::Ellipse:
        {
          //
          // TODO: Implement.
          //

          break;
        }
        case tson::ObjectType::Rectangle:
        {
          //
          // TODO: Implement.
          //

          break;
        }
        case tson::ObjectType::Point:
        {
          //
          // TODO: Implement.
          //

          break;
        }
        case tson::ObjectType::Polygon:
        {
          //
          // TODO: Implement.
          //

          break;
        }
        case tson::ObjectType::Polyline:
        {
          //
          // TODO: Implement.
          //

          break;
        }
        case tson::ObjectType::Text:
        {
          sf::Text *text = new sf::Text();

          text -> setFont(AssetsManager::GetInstance().GetFont("GoudyBookletter.ttf"));
          text -> setPosition(static_cast<float>(obj.getPosition().x), static_cast<float>(obj.getPosition().y));
          text -> setString(obj.getText().text);
          text -> setFillColor(sf::Color(255, 255, 255));
          text -> setCharacterSize(32);
          text -> setScale(1.f, 1.f);

          window.Draw(*text);

          break;
        }
        case tson::ObjectType::Template:
        {
          //
          // TODO: Implement.
          //

          break;
        }
      }
    }
  }
}

void MapRenderer::DrawImageLayer(Window &window, tson::Layer &layer)
{
  sf::Sprite *sprite = m_tiledMapParser.GetTilesetImage(layer.getImage(),
                                                      { layer.getOffset().x,
                                                        layer.getOffset().y });
  if (sprite != nullptr)
  {
    window.Draw(*sprite);
  }
}