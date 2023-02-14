#pragma once

#include "C_Collider.hpp"

class C_ColliderBox : public C_Collider
{

  public:

    C_ColliderBox(Object *owner);
    ~C_ColliderBox();

    CollisionManifold Intersects(std::shared_ptr<C_Collider> other) override;
    void ResolveOverlap(const CollisionManifold &manifold) override;

    void SetCollidable(const sf::FloatRect &rect);
    const sf::FloatRect &GetCollidable();

    sf::FloatRect GetPreviousFrameCollidable() const;

    void SetOffset(const sf::Vector2f &offset);
    void SetOffset(float x, float y);

    void SetSize(const sf::Vector2f &size);
    void SetSize(float width, float height);

  private:

    void SetPosition();

    sf::FloatRect m_AABB;
    sf::Vector2f m_offset;


};