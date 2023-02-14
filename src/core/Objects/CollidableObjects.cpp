#include "CollidableObjects.hpp"

#include "C_InstanceID.hpp"
#include "C_ColliderBox.hpp"
#include "Quadtree.hpp"

#ifdef DEBUG
#include "Debug.hpp"
#endif

void CollidableObjects::Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant)
{
  if (std::holds_alternative<std::shared_ptr<Object>>(variant))
  {
    std::shared_ptr<Object> gameObject = std::get<std::shared_ptr<Object>>(variant);

    auto collider = gameObject -> GetComponent<C_ColliderBox>();

    int layerLevel = collider -> GetLayer();

    m_collidableObjects.insert({ layerLevel, gameObject });

    m_quadtree.Insert(collider);
  }
  else if (std::holds_alternative<std::shared_ptr<tson::Map>>(variant))
  {
    std::shared_ptr<tson::Map> map = std::get<std::shared_ptr<tson::Map>>(variant);

    for (auto &layer : map -> getLayers())
    {
      if (layer.getProperties().getValue<bool>("collidable"))
      {
        if (layer.getType() == tson::LayerType::ObjectGroup)
        {
          for (auto &collidableObject : layer.getObjects())
          {
            if (collidableObject.getProperties().getValue<bool>("collidable"))
            {
              std::shared_ptr<Object> gameObject = std::make_shared<Object>();

              int collidableObjectLayerlevel = collidableObject.getProperties().getValue<int>("level");

              auto colliderBox = gameObject -> AddComponent<C_ColliderBox>();

              gameObject -> transform -> SetStatic(true);

              colliderBox -> SetLayer(collidableObjectLayerlevel);

              colliderBox -> SetCollidable({ static_cast<float>(collidableObject.getPosition().x),
                                             static_cast<float>(collidableObject.getPosition().y),
                                             static_cast<float>(collidableObject.getSize().x),
                                             static_cast<float>(collidableObject.getSize().y) });

              m_collidableObjects.insert({ collidableObjectLayerlevel, gameObject });

              m_quadtree.Insert(colliderBox);
            }
            FILE_LOG_INFO("debug.txt", "[CollidableObjects][Add] Detected new collidable object");
          }
        }
        else
        {
          FILE_LOG_INFO("debug.txt", "[CollidableObjects][Add] Layer is not an object layer - engine does not support this yet");
          return;
        }
      }
    }
  }
  else
  {
    FILE_LOG_ERROR("debug.txt", "[CollidableObjects][Add] Unknown object type");
  }
}

void CollidableObjects::ClearObjects()
{

}

void CollidableObjects::ProcessRemovedObjects()
{
  for (auto it = m_collidableObjects.begin(); it != m_collidableObjects.end();)
  {
    if (it -> second -> QueuedForRemoval())
    {
      it = m_collidableObjects.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void CollidableObjects::Update(float deltaTime)
{
  m_quadtree.DrawDebug();

  ProcessCollidingObjects();

  m_quadtree.Clear();

  for (auto &[level, object] : m_collidableObjects)
  {
    auto collider = object -> GetComponent<C_ColliderBox>();

    m_quadtree.Insert(collider);
  }

  Resolve();
}

void CollidableObjects::Draw(Window &window)
{
  #ifdef DEBUG
  for (auto &[level, object] : m_collidableObjects)
  { 
    if (object -> HasComponent<C_ColliderBox>())
    {
      auto colliderBox = object -> GetComponent<C_ColliderBox>();

      Debug::AddRect(colliderBox -> GetCollidable());
    }
  }
  #endif
}

void CollidableObjects::ProcessCollidingObjects()
{
  for (auto it = m_objectsColliding.begin(); it != m_objectsColliding.end();)
  {
    auto pair = *it;

    std::shared_ptr<C_ColliderBox> first = pair.first;
    std::shared_ptr<C_ColliderBox> second = pair.second;

    if (first -> owner -> QueuedForRemoval() || second -> owner -> QueuedForRemoval())
    {
      first -> owner -> OnCollisionExit(second);
      second -> owner -> OnCollisionExit(first);

      it = m_objectsColliding.erase(it);
    }
    else
    {
      CollisionManifold m = first -> Intersects(second);

      if (m.colliding)
      {
        first -> owner -> OnCollisionStay(second);
        second -> owner -> OnCollisionStay(first);
                
        ++it;
      }
      else
      {
        first -> owner -> OnCollisionExit(second);
        second -> owner -> OnCollisionExit(first);

        it = m_objectsColliding.erase(it);
      }
    }
  }
}

void CollidableObjects::Resolve()
{
  for (auto &[level, object] : m_collidableObjects)
  {
    if (object -> transform -> IsStatic())
    {
      continue;
    }

    auto currentObjectColliderBox = object -> GetComponent<C_ColliderBox>();

    std::vector<std::shared_ptr<C_ColliderBox>> collisions = m_quadtree.Search(currentObjectColliderBox -> GetCollidable());

    for (auto collision : collisions)
    {
      if (currentObjectColliderBox == collision)
      {
        continue;
      }

      if (collision -> GetLayer() == currentObjectColliderBox -> GetLayer())
      {
        CollisionManifold m = currentObjectColliderBox -> Intersects(collision);

        if (m.colliding)
        {
          auto collisionPair = m_objectsColliding.emplace(std::make_pair(currentObjectColliderBox, collision));

          if (collisionPair.second)
          {
            currentObjectColliderBox -> owner -> OnCollisionEnter(collision);
            collision -> owner -> OnCollisionEnter(currentObjectColliderBox);
          }

          Debug::AddRect(currentObjectColliderBox -> GetCollidable(), sf::Color::Red);
          Debug::AddRect(collision -> GetCollidable(), sf::Color::Red);

          currentObjectColliderBox -> ResolveOverlap(m);
        }
      }
    }
  }
}