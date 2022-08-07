#pragma once

#include "tileson.hpp"
#include "Window.hpp"
#include "ObjectCollection.hpp"
#include "MapRenderer.hpp"

class GameRenderer
{

  public:

    GameRenderer() = default;
    ~GameRenderer() = default;

    void Draw(Window &window);

    void AssignMapRenderer(MapRenderer *mapRenderer);
    void AssignObjects(ObjectCollection *objectCollection);

  private:

    MapRenderer *m_mapRenderer;
    ObjectCollection *m_objectCollection;

};