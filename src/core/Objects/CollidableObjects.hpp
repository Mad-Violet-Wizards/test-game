#pragma once

#include <variant>
#include <map>
#include <unordered_set>

#include "tileson.hpp"
#include "Object.hpp"
#include "Quadtree.hpp"
#include "C_ColliderBox.hpp"
#include "Hashes.hpp"

class CollidableObjects
{
  
    public:
  
      CollidableObjects() = default;
      ~CollidableObjects() = default;
  
      void Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant);
      void ClearObjects();

      void ProcessRemovedObjects();
  
      void Update(float deltaTime);
      void Draw(Window &window);

    private:

      void ProcessCollidingObjects();
      void Resolve();
  
    private:

      std::multimap<int, std::shared_ptr<Object>> m_collidableObjects;
      std::unordered_set<std::pair<std::shared_ptr<C_ColliderBox>, std::shared_ptr<C_ColliderBox>>, ComponentPairHash> m_objectsColliding; 
      Quadtree m_quadtree;
};