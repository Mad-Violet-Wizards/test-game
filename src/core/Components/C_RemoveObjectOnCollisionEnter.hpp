#pragma once

#include "Component.hpp"
#include "C_Collidable.hpp"

class C_RemoveObjectOnCollisionEnter : public Component, public C_Collidable
{

  public:

    C_RemoveObjectOnCollisionEnter(Object *owner);

    void OnCollisionEnter(std::shared_ptr<C_ColliderBox> other) override;
};