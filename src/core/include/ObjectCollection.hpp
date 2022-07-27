#pragma once

#include <memory>
#include <vector>
#include <queue>

#include "Object.hpp"

class ObjectCollection
{

public:

  ObjectCollection();
  ~ObjectCollection();

  void Add(std::shared_ptr<Object> object);

  void Update(float deltaTime);
  void Draw(Window &window);

  void ProcessNewObjects();
  void ProcessRemovedObjects();

private:

  std::vector<std::shared_ptr<Object>> m_objects;
  std::priority_queue<std::shared_ptr<Object>> m_newObjects;

};