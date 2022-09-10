#pragma once

#include "C_BoxCollider.hpp"

class C_Collidable
{
  public:

    virtual void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other) = 0;
    virtual void OnCollisionStay(std::shared_ptr<C_BoxCollider> other) = 0;
    virtual void OnCollisionExit(std::shared_ptr<C_BoxCollider> other) = 0;
};