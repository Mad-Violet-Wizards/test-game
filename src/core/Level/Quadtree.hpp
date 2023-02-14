#pragma once


#include "C_ColliderBox.hpp"
#include "Debug.hpp"

enum class QuadtreeNodePosition
{
  PARENT = -1,
  CHILD_NE = 0,
  CHILD_NW = 1,
  CHILD_SW = 2,
  CHILD_SE = 3
};

class Quadtree
{

  public:

    Quadtree();
    Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree *parent);

    void DrawDebug();

    void Insert(std::shared_ptr<C_ColliderBox> object);
    void Remove(std::shared_ptr<C_ColliderBox> object);
    void Clear();
    void UpdatePosition(std::shared_ptr<C_ColliderBox> object);

    std::vector<std::shared_ptr<C_ColliderBox>> Search(const sf::FloatRect &area);

    const sf::FloatRect &GetBounds() const;

  private:

    void Search(const sf::FloatRect &area, std::vector<std::shared_ptr<C_ColliderBox>> &overlappingObjects);

    int GetChildIndexForObject(const sf::FloatRect &objectBounds);
    void Split();

    int CastToIndex(QuadtreeNodePosition position) { return static_cast<int>(position); }


  private:

    int m_maxObjects;
    int m_maxLevels;
    int m_level;

    sf::FloatRect m_bounds;

    Quadtree *m_parent;
    std::shared_ptr<Quadtree> m_children[4];

    std::vector<std::shared_ptr<C_ColliderBox>> m_objects;
};