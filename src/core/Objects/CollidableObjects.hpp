#pragma once


#include "tileson.hpp"
#include "Hashes.hpp"
#include "Quadtree.hpp"

class C_ColliderBox;

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