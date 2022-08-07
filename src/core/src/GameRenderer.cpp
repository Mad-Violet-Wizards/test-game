#include "GameRenderer.hpp"

void GameRenderer::Draw(Window &window)
{
  m_mapRenderer -> DrawLayersBelowPlayer(window);
  m_mapRenderer -> DrawLayerPlayerLevel(window);

  m_objectCollection -> Draw(window);

  m_mapRenderer -> DrawLayersAbovePlayer(window);
}

void GameRenderer::AssignMapRenderer(MapRenderer *mapRenderer)
{
  m_mapRenderer = mapRenderer;
}

void GameRenderer::AssignObjects(ObjectCollection *objectCollection)
{
  m_objectCollection = objectCollection;
}