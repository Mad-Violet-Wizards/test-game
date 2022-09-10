#include "C_InstanceID.hpp"

unsigned int C_InstanceID::s_counter = 0;

C_InstanceID::C_InstanceID(Object *owner) 
  : Component(owner),
    m_instanceID(s_counter++)
{

}

unsigned int C_InstanceID::GetID() const
{
  return m_instanceID;
}