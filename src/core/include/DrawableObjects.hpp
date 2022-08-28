#pragma once

#include <variant>
#include <map>

#include "tileson.hpp"
#include "Object.hpp"
#include "MapRenderer.hpp"

enum class LayerLevel
{
  BelowLayer,
  StanardLayer,
  PlayerLayer,
  AboveLayer
};

class DrawableObjects
{

  public:

    DrawableObjects() = default;
    ~DrawableObjects() = default;

    void Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> object);
    void ClearLayers();
    void ClearObjects();

    void Update(float deltaTime);
    void Draw(Window &window);

  private:

    std::multimap<LayerLevel, std::variant<std::shared_ptr<Object>, tson::Layer>> m_drawableObjects;

    MapRenderer m_mapRenderer;

};