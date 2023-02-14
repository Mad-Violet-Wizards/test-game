#include "C_RemoveObjectOnCollisionEnter.hpp"

C_RemoveObjectOnCollisionEnter::C_RemoveObjectOnCollisionEnter(Object *owner)
  : Component(owner)
{
}

void C_RemoveObjectOnCollisionEnter::OnCollisionEnter(std::shared_ptr<C_ColliderBox> other)
{
  owner -> QueueForRemoval();
}