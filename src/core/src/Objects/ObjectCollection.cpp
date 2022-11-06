#include "ObjectCollection.hpp"

#include "C_ColliderBox.hpp"
#include "C_Drawable.hpp"

#include <chrono>
#include <future>
#include <thread>

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
  auto objectsTasks = std::async(std::launch::async, [&]() {
    for (auto &object : m_objects)
    {
      object -> Update(deltaTime);
    }
  });

  auto collidableTasks = std::async(std::launch::async, [&]() {
    m_collidableObjects.Update(deltaTime);
  });

  auto drawableTasks = std::async(std::launch::async, [&]() {
    m_drawableObjects.Update(deltaTime);
  });

  objectsTasks.wait();
  collidableTasks.wait();
  drawableTasks.wait();
}

void ObjectCollection::LateUpdate(float deltaTime)
{
  for (auto &object : m_objects)
  {
    object -> LateUpdate(deltaTime);
  }
}

void ObjectCollection::Draw(Window &window)
{
  m_drawableObjects.Draw(window);
  m_collidableObjects.Draw(window);
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

      if (object -> HasComponent<C_Drawable>())
      {
        m_drawableObjects.Add(object);
      }

      if (object -> HasComponent<C_ColliderBox>())
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
      FILE_LOG_ERROR("[ObjectCollection][ProcessNewObjects] Unknown object type");
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