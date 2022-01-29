#pragma once

#include "Window.hpp"

class Object;

class Component
{
public:

  Component(Object* owner) : m_owner(owner) {}

  virtual void Awake() {};
  virtual void Start() {};

  virtual void Update(float deltaTime) {};
  virtual void Draw(Window& window) {};

protected:

  Object* m_owner;
};
