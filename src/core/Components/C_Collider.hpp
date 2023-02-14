#pragma once


class Component;

struct CollisionManifold
{
  bool colliding = false;
  const sf::FloatRect *other;
};

class C_Collider : public Component
{
  public:

    C_Collider(Object *owner);
    ~C_Collider() = default;

    virtual CollisionManifold Intersects(std::shared_ptr<C_Collider> other) = 0;
    virtual void ResolveOverlap(const CollisionManifold &manifold) = 0;

    void SetLayer(int layer);
    int GetLayer() const;

  private:

    int m_layer;
};
