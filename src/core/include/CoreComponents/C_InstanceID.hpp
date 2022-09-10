#pragma once

#include "Component.hpp"

class C_InstanceID : public Component
{

  public:

    C_InstanceID(Object *owner);
    ~C_InstanceID() = default;

    unsigned int GetID() const;

  private:

    static unsigned int s_counter;
    unsigned int m_instanceID;
};