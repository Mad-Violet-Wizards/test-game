#include "Component.hpp"
#include "C_Collider.hpp"

C_Collider::C_Collider(Object *owner) 
  : Component(owner),
    m_layer(0) 
{

}

void C_Collider::SetLayer(int layer) 
{ 
  m_layer = layer;
}

int C_Collider::GetLayer() const
{
  return m_layer;
}
