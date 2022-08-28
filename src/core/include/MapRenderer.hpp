#pragma once

#include <filesystem>

#include "tileson.hpp"
#include "Window.hpp"
#include "TiledMapParser.hpp"

class MapRenderer
{

  public:

    MapRenderer() = default;
    ~MapRenderer() = default;

    void Update(float deltaTime);

    void DrawLayer(Window &window, tson::Layer &layer);

  private:

    void DrawTileLayer(Window &window, tson::Layer &layer);
    void DrawObjectGroup(Window &window, tson::Layer &layer);
    void DrawImageLayer(Window &window, tson::Layer &layer);

  private:

    TiledMapParser m_tiledMapParser;

};