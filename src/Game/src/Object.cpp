#include "Object.hpp"

void Object::Awake()
{
  for (const auto& c : m_components)
  {
    c -> Awake();
  }
}

void Object::Start()
{
  for (const auto& c : m_components)
  {
    c -> Start();
  }
}

void Object::Update(float deltaTime)
{
  for (const auto& c : m_components)
  {
    c -> Update(deltaTime);
  }
}

void Object::Draw(Window& window)
{
  for (const auto& c : m_components)
  {
    c -> Draw(window);
  }
}