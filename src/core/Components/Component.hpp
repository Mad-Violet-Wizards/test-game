#pragma once

class Object;
class Window;

class Component
{

public:

  Component(Object *owner) : owner(owner) {}

  virtual void Awake() {};
  virtual void Start() {};

  virtual void Update(float deltaTime) {};
  virtual void LateUpdate(float deltaTime) {};
  virtual void Draw(Window &window) {};

  //
  // The only exception where we don't use m_ prefix for class member.
  //

  Object *owner;

};
