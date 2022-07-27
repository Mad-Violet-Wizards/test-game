#include "ObjectCollection.hpp"

ObjectCollection::ObjectCollection()
{

}

ObjectCollection::~ObjectCollection()
{

}

void ObjectCollection::Add(std::shared_ptr<Object> object)
{
  m_newObjects.push(object);
}

void ObjectCollection::Update(float deltaTime)
{
  for (auto &object : m_objects)
  {
    object -> Update(deltaTime);
  }
}

void ObjectCollection::Draw(Window &window)
{
  for (auto &object : m_objects)
  {
    object -> Draw(window);
  }
}

void ObjectCollection::ProcessNewObjects()
{
  while (!m_newObjects.empty())
  {
    std::shared_ptr<Object> object = m_newObjects.top();

    object -> Awake();
    object -> Start();

    m_objects.push_back(object);
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