#include "DrawableObjects.hpp"

#include "Log.hpp"

void DrawableObjects::Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant)
{
  if (std::holds_alternative<std::shared_ptr<Object>>(variant))
  {
    std::shared_ptr<Object> obj = std::get<std::shared_ptr<Object>>(variant);

    m_drawableObjects.insert(std::make_pair(LayerLevel::PlayerLayer, obj));
  }
  else if (std::holds_alternative<std::shared_ptr<tson::Map>>(variant))
  {
    std::shared_ptr<tson::Map> map = std::get<std::shared_ptr<tson::Map>>(variant);

    for (auto &layer : map -> getLayers())
    {
      int level = layer.getProperties().getValue<int>("level");

      if (level < 0)
      {
        m_drawableObjects.insert(std::make_pair(LayerLevel::BelowLayer, layer));
      }
      else if (level > 0)
      {
        m_drawableObjects.insert(std::make_pair(LayerLevel::AboveLayer, layer));
      }
      else
      {
        m_drawableObjects.insert(std::make_pair(LayerLevel::StanardLayer, layer));
      }
    }
  }
}

void DrawableObjects::ClearLayers()
{
  for (auto &object : m_drawableObjects)
  {
    if (std::holds_alternative<tson::Layer>(object.second))
    {
      m_drawableObjects.erase(object.first);
    }
  }
}

void DrawableObjects::ClearObjects()
{
  for (auto &object : m_drawableObjects)
  {
    if (std::holds_alternative<std::shared_ptr<Object>>(object.second))
    {
      m_drawableObjects.erase(object.first);
    }
  }
}

void DrawableObjects::Update(float deltaTime)
{
  m_mapRenderer.Update(deltaTime);
}

void DrawableObjects::Draw(Window &window)
{
  for (auto &object : m_drawableObjects)
  {
    if (std::holds_alternative<std::shared_ptr<Object>>(object.second))
    {
      std::shared_ptr<Object> obj = std::get<std::shared_ptr<Object>>(object.second);

      obj -> Draw(window);
    }
    else if (std::holds_alternative<tson::Layer>(object.second))
    {
      tson::Layer layer = std::get<tson::Layer>(object.second);

      if (layer.getProperties().getValue<bool>("drawable") == true)
      {
        m_mapRenderer.DrawLayer(window, layer);
      }
    }
    else
    {
      LOG_ERROR("[DrawableObjects][Draw] Unknown object type");
    }
  }
}