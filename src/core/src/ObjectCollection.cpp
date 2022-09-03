#include "ObjectCollection.hpp"

ObjectCollection::ObjectCollection()
{

}

ObjectCollection::~ObjectCollection()
{

}

void ObjectCollection::Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant)
{
  m_newObjects.push(variant);
}

void ObjectCollection::Update(float deltaTime)
{
  for (auto &object : m_objects)
  {
    object -> Update(deltaTime);
  }

  m_collidableObjects.Update(deltaTime);
  m_drawableObjects.Update(deltaTime);
}

void ObjectCollection::Draw(Window &window)
{
  m_collidableObjects.Draw(window);
  m_drawableObjects.Draw(window);
}

void ObjectCollection::ProcessNewObjects()
{
  while (!m_newObjects.empty())
  {
    auto VariantObject = m_newObjects.front();

    if (std::holds_alternative<std::shared_ptr<Object>>(VariantObject))
    { 
      std::shared_ptr<Object> object = std::get<std::shared_ptr<Object>>(VariantObject);

      object -> Awake();
      object -> Start();

      if (object -> Drawable())
      {
        m_drawableObjects.Add(object);
      }

      if (object -> Collidable())
      {
        m_collidableObjects.Add(object);
      }

      m_objects.push_back(object);
    }
    else if (std::holds_alternative<std::shared_ptr<tson::Map>>(VariantObject))
    {
      std::shared_ptr<tson::Map> map = std::get<std::shared_ptr<tson::Map>>(VariantObject);

      m_collidableObjects.Add(map);
      m_drawableObjects.Add(map);
    }
    else
    {
      LOG_ERROR("[ObjectCollection][ProcessNewObjects] Unknown object type");
    }

    m_newObjects.pop();
  }
}

void ObjectCollection::ProcessRemovedObjects()
{
  auto it = m_objects.begin();

  while (it != m_objects.end())
  {
    auto object = **it;

    if (object.QueuedForRemoval())
    {
      it = m_objects.erase(it);
    }
    else
    {
      ++it;
    }
  }
}