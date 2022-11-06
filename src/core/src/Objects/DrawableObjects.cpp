#include "DrawableObjects.hpp"

#include "C_Drawable.hpp"
#include "FileLog.hpp"

void DrawableObjects::Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant)
{
  if (std::holds_alternative<std::shared_ptr<Object>>(variant))
  {
    std::shared_ptr<Object> obj = std::get<std::shared_ptr<Object>>(variant);
    
    int layerLevel = obj -> GetComponent<C_Drawable>() -> GetLayer();

    m_drawableObjects.insert({ layerLevel, obj });
  }
  else if (std::holds_alternative<std::shared_ptr<tson::Map>>(variant))
  {
    std::shared_ptr<tson::Map> map = std::get<std::shared_ptr<tson::Map>>(variant);

    for (auto &layer : map -> getLayers())
    {
      int layerLevel = layer.getProperties().getValue<int>("level");

      m_drawableObjects.insert({ layerLevel, layer });
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
      FILE_LOG_ERROR("[DrawableObjects][Draw] Unknown object type");
    }
  }
}