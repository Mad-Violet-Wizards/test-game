#include "C_Drawable.hpp"

C_Drawable::C_Drawable(Object *owner) 
  : Component(owner), 
    m_layer(0)
{

}

void C_Drawable::SetLayer(int layer)
{
  m_layer = layer;
}

int C_Drawable::GetLayer() const
{
  return m_layer;
}