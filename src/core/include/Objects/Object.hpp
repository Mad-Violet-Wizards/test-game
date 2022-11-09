#pragma once

#include <vector>
#include <memory>

#include "Window.hpp"
#include "Component.hpp"
#include "FileLog.hpp"

#include "Component.hpp"
#include "C_InstanceID.hpp"
#include "C_Transform.hpp"

class Object
{

public:

  Object();
  ~Object();

  void Awake(); // Called when object created. Use to ensure required components are present.
  void Start(); // Called after Awake method. Use to initialise variables.

  void Update(float deltaTime);
  void LateUpdate(float deltaTime);
  void Draw(Window &window);

  bool QueuedForRemoval() const;
  void QueueForRemoval();

  std::shared_ptr<C_Transform> transform;
  std::shared_ptr<C_InstanceID> instanceID;

  template <typename T, typename ...Args>
  std::shared_ptr<T> AddComponent(Args &&...args)
  {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    // Check that we don't already have a component of this type.
    for (auto& exisitingComponent : m_components)
    {
      if (std::dynamic_pointer_cast<T>(exisitingComponent))
      {
        return std::dynamic_pointer_cast<T>(exisitingComponent);
      }
    }

    std::shared_ptr<T> newComponent = std::make_shared<T>(this, std::forward<Args>(args)...);
    m_components.push_back(newComponent);

    return newComponent;
  };

  template <typename T>
  std::shared_ptr<T> GetComponent()
  {
    // Check that we don't already have a component of this type.
    for (auto& exisitingComponent : m_components)
    {
      if (std::dynamic_pointer_cast<T>(exisitingComponent))
      {
        return std::dynamic_pointer_cast<T>(exisitingComponent);
      }
    }

    FILE_LOG_WARNING("[Object][GetComponent] Returned nullptr.");

    return nullptr;
  };

  template <typename T>
  bool HasComponent() const
  {
    for (auto& exisitingComponent : m_components)
    {
      if (std::dynamic_pointer_cast<T>(exisitingComponent))
      {
        return true;
      }
    }

    return false;
  };

private:

  std::vector<std::shared_ptr<Component>> m_components;
  bool m_queuedForRemoval;

};
