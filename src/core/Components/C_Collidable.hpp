#pragma once

class C_ColliderBox;

class C_Collidable
{
  public:

    virtual void OnCollisionEnter(std::shared_ptr<C_ColliderBox> other) {};
    virtual void OnCollisionStay(std::shared_ptr<C_ColliderBox> other) {};
    virtual void OnCollisionExit(std::shared_ptr<C_ColliderBox> other) {};
};