#pragma once


#include "tileson.hpp"
#include "Level/MapRenderer.hpp"

class DrawableObjects
{

  public:

    DrawableObjects() = default;
    ~DrawableObjects() = default;

    void Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant);
    void ClearLayers();
    void ClearObjects();

    void ProcessRemovedObjects();

    void Update(float deltaTime);
    void Draw(Window &window);

  private:

    std::multimap<int, std::variant<std::shared_ptr<Object>, tson::Layer>> m_drawableObjects;

    MapRenderer m_mapRenderer;

};