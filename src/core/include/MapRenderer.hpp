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

    void PrepareLocation(const std::string &locationName);

    void Update(float deltaTime);

    void DrawLayersAbovePlayer(Window &window);
    void DrawLayerPlayerLevel(Window &window);
    void DrawLayersBelowPlayer(Window &window);

  private:

    bool PrepareLayers();

    void DrawLayer(Window &window, tson::Layer &layer);

    void DrawTileLayer(Window &window, tson::Layer &layer);
    void DrawObjectGroup(Window &window, tson::Layer &layer);
    void DrawImageLayer(Window &window, tson::Layer &layer);
  
  private:

    TiledMapParser m_tiledMapParser;

    std::vector<tson::Layer> m_layersAbovePlayer;
    std::vector<tson::Layer> m_layerPlayerLevel;
    std::vector<tson::Layer> m_layersBelowPlayer;

    std::unique_ptr<tson::Map> m_map;

};