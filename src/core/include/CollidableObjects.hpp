#pragma once

#include <variant>
#include <map>

#include "tileson.hpp"
#include "Object.hpp"
#include "LayerLevel.hpp"

class CollidableObjects
{
  
    public:
  
      CollidableObjects() = default;
      ~CollidableObjects() = default;
  
      void Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant);
      void ClearObjects();
  
      void Update(float deltaTime);
      void Draw(Window &window);
  
    private:

    std::multimap<LayerLevel, std::shared_ptr<Object>> m_collidableObjects;
};