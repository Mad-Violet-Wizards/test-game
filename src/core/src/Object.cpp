#include "Object.hpp"

Object::Object()
  : m_queuedForRemoval(false)
{
  transform = AddComponent<C_Transform>();
  instanceID = AddComponent<C_InstanceID>();
}

Object::~Object() { }

void Object::Awake()
{
  for (const auto &c : m_components)
  {
    c -> Awake();
  }
}

void Object::Start()
{
  for (const auto &c : m_components)
  {
    c -> Start();
  }
}

void Object::Update(float deltaTime)
{
  for (const auto &c : m_components)
  {
    c -> Update(deltaTime);
  }
}

void Object::LateUpdate(float deltaTime)
{
  for (const auto &c : m_components)
  {
    c -> LateUpdate(deltaTime);
  }
}

void Object::Draw(Window &window)
{
  for (const auto &c : m_components)
  {
    c -> Draw(window);
  }
}

bool Object::QueuedForRemoval() const
{
  return m_queuedForRemoval;
}

void Object::QueueForRemoval()
{
  m_queuedForRemoval = true;
}
