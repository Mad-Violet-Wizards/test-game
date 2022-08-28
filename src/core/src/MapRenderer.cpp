#include <memory>

#include "MapRenderer.hpp"

void MapRenderer::Update(float deltaTime)
{

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
  // TODO: Add animated tiles.
  //

  for (auto &[pos, tileObject] : layer.getTileObjects())
  {
    tson::Tileset *tileset = tileObject.getTile() -> getTileset();
    tson::Rect drawingRect = tileObject.getDrawingRect();

    fs::path tilesetPath = m_tiledMapParser.GetTilesetImagePath(*tileset);
    sf::Sprite *sprite = m_tiledMapParser.LoadAndStoreTilesetImage(tilesetPath.string(), { 0, 0 }); // Change it.

    if (sprite != nullptr)
    {
      tson::Vector2f position = tileObject.getPosition();

      sf::Vector2f scale = sprite -> getScale();
      sf::Vector2f originalScale = scale;
      
      float rotation = sprite -> getRotation();
      float originalRotation = rotation;

      sf::Vector2f origin { static_cast<float>(drawingRect.width) / 2, 
                            static_cast<float>(drawingRect.height) / 2 };

      if(tileObject.getTile() -> hasFlipFlags(tson::TileFlipFlags::Horizontally))
      {
        scale.x = -scale.x;
      }
      if(tileObject.getTile() -> hasFlipFlags(tson::TileFlipFlags::Vertically))
      {
        scale.y = -scale.y;
      }
      if(tileObject.getTile() -> hasFlipFlags(tson::TileFlipFlags::Diagonally))
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
  // TODO: Implement.
}

void MapRenderer::DrawImageLayer(Window &window, tson::Layer &layer)
{
  // TODO: Implement.
}