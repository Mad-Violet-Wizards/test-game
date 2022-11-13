#include "C_ColliderBox.hpp"

#include "Object.hpp"
#include "C_Transform.hpp"

C_ColliderBox::C_ColliderBox(Object *owner) 
  : C_Collider(owner), 
    m_AABB(0.f, 0.f, 0.f, 0.f), 
    m_offset(0.f, 0.f)
{

}

C_ColliderBox::~C_ColliderBox() { }

CollisionManifold C_ColliderBox::Intersects(std::shared_ptr<C_Collider> other)
{
  CollisionManifold manifold;
  manifold.colliding = false;

  std::shared_ptr<C_ColliderBox> otherBox = std::dynamic_pointer_cast<C_ColliderBox>(other);

  if (otherBox)
  {
    const sf::FloatRect &r1 = GetCollidable();
    const sf::FloatRect &r2 = otherBox -> GetCollidable();

    if (r1.intersects(r2))
    {
      manifold.colliding = true;
      manifold.other = &r2;
    }
  }

  return manifold;
}

void C_ColliderBox::ResolveOverlap(const CollisionManifold &manifold)
{
  auto transform = owner -> transform;

  if (transform->IsStatic())
  {
    return;
  }

  const sf::FloatRect &r1 = GetCollidable();
  const sf::FloatRect *r2 = manifold.other;

  float resolve = 0;

  float xDiff = (r1.left + (r1.width * 0.5f) - (r2 -> left + (r2 -> width * 0.5f)));
  float yDiff = (r1.top + (r1.height * 0.5f) - (r2 -> top + (r2 -> height * 0.5f)));

  if (fabs(xDiff) > fabs(yDiff))
  {
    if (xDiff > 0)
    {
      resolve = (r2 -> left + r2 -> width) - r1.left;
    }
    else
    {
      resolve = -((r1.left + r1.width) - r2 -> left);
    }

    transform -> AddX(resolve);
  }
  else
  {
    if (yDiff > 0)
    {
      resolve = (r2 -> top + r2 -> height) - r1.top;
    }
    else
    {
      resolve = -((r1.top + r1.height) - r2 -> top);
    }

    transform -> AddY(resolve);
  }
}

void C_ColliderBox::SetCollidable(const sf::FloatRect &rect)
{
  m_AABB = rect;
  SetPosition();
}

const sf::FloatRect &C_ColliderBox::GetCollidable()
{
  SetPosition();
  return m_AABB;
}

sf::FloatRect C_ColliderBox::GetPreviousFrameCollidable() const
{
  const sf::Vector2f &pos = owner -> transform -> GetPreviousFramePosition();

  sf::FloatRect prevAABB;

  prevAABB.left = pos.x + m_offset.x;
  prevAABB.top = pos.y + m_offset.y;

  return prevAABB;
}

void C_ColliderBox::SetOffset(const sf::Vector2f &offset)
{
  m_offset = offset;
}

void C_ColliderBox::SetOffset(float x, float y)
{
  m_offset.x = x;
  m_offset.y = y;
}

void C_ColliderBox::SetSize(const sf::Vector2f &size)
{
  m_AABB.width = size.x;
  m_AABB.height = size.y;
}

void C_ColliderBox::SetSize(float x, float y)
{
  m_AABB.width = x;
  m_AABB.height = y;
}

void C_ColliderBox::SetPosition()
{
  auto transform = owner -> transform;

  if (!transform -> IsStatic())
  {
    m_AABB.left = transform -> GetPosition().x + m_offset.x;
    m_AABB.top = transform -> GetPosition().y + m_offset.y;
  }
}