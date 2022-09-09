#pragma once

#include "Component.hpp"
#include "Object.hpp"

class C_Drawable : public Component
{

  public:

    C_Drawable(Object *owner);
    ~C_Drawable() = default;

    void SetLayer(int layer);
    int GetLayer() const;

  private:

    int m_layer;
};