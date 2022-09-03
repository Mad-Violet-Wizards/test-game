#include "CollidableObjects.hpp"

#include "C_ColliderBox.hpp"

#ifdef DEBUG
#include "Debug.hpp"
#endif

#include "Log.hpp"

void CollidableObjects::Add(std::variant<std::shared_ptr<Object>, std::shared_ptr<tson::Map>> variant)
{
  if (std::holds_alternative<std::shared_ptr<Object>>(variant))
  {
    std::shared_ptr<Object> gameObject = std::get<std::shared_ptr<Object>>(variant);

    m_collidableObjects.insert({ LayerLevel::PlayerLayer, gameObject });
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

              auto colliderBox = gameObject -> AddComponent<C_ColliderBox>();

              colliderBox -> SetCollidable({ static_cast<float>(collidableObject.getPosition().x),
                                             static_cast<float>(collidableObject.getPosition().y),
                                             static_cast<float>(collidableObject.getSize().x),
                                             static_cast<float>(collidableObject.getSize().y) });

              m_collidableObjects.insert({ LayerLevel::PlayerLayer, gameObject });
            }
            LOG_INFO("[CollidableObjects][Add] Detected new collidable object");
          }
        }
        else
        {
          LOG_INFO("[CollidableObjects][Add] Layer is not an object layer - engine does not support this yet");
          return;
        }
      }
    }
  }
  else
  {
    LOG_ERROR("[CollidableObjects][Add] Unknown object type");
  }
}

void CollidableObjects::ClearObjects()
{

}

void CollidableObjects::Update(float deltaTime)
{

}

void CollidableObjects::Draw(Window &window)
{
  #ifdef DEBUG
  for (auto &[level, object] : m_collidableObjects)
  {
    auto colliderBox = object -> GetComponent<C_ColliderBox>();

    if (colliderBox)
    {
      Debug::AddRect(colliderBox -> GetCollidable());
    }
  }
  #endif
}