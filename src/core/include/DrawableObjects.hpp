#pragma once

#include <variant>
#include <map>

#include "tileson.hpp"
#include "Object.hpp"
#include "MapRenderer.hpp"
#include "LayerLevel.hpp"

class DrawableObjects
{

  public:

    DrawableObjects() = default;
    ~DrawableObjects() = default;

    void Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant);
    void ClearLayers();
    void ClearObjects();

    void Update(float deltaTime);
    void Draw(Window &window);

  private:

    std::multimap<LayerLevel, std::variant<std::shared_ptr<Object>, tson::Layer>> m_drawableObjects;

    MapRenderer m_mapRenderer;

};