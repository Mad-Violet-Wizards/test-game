#include "Quadtree.hpp"

Quadtree::Quadtree() : Quadtree(5, 5, 0, {0, 0, 1920, 1080}, nullptr)
{

}

Quadtree::Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree *parent)
  : m_maxObjects(maxObjects),
    m_maxLevels(maxLevels),
    m_level(level),
    m_bounds(bounds),
    m_parent(parent)
{

}

void Quadtree::DrawDebug()
{
  #ifdef DEBUG
  if (m_children[0] != nullptr)
  {
    for (int i = 0; i < 4; i++)
    {
      m_children[i] -> DrawDebug();
    }
  }

  Debug::AddRect(m_bounds, sf::Color::Red);
  #endif
}

void Quadtree::Insert(std::shared_ptr<C_ColliderBox> object)
{
  if (!m_bounds.intersects(object -> GetCollidable()))
  {
    return;
  }

  if (m_children[0] != nullptr)
  {
    int index = GetChildIndexForObject(object -> GetCollidable());

    if (index != CastToIndex(QuadtreeNodePosition::PARENT))
    {
      m_children[index] -> Insert(object);
      return;
    }
  }

  m_objects.emplace_back(object);

  if (m_objects.size() > m_maxObjects && m_level < m_maxLevels && m_children[0] == nullptr)
  {
    Split();

    auto it = m_objects.begin();

    while (it != m_objects.end())
    {
      auto object = *it;

      int index = GetChildIndexForObject(object -> GetCollidable());

      if (index != CastToIndex(QuadtreeNodePosition::PARENT))
      {
        m_children[index] -> Insert(object);
        it = m_objects.erase(it);
      }
      else
      {
        it++;
      }
    }
  }
}

void Quadtree::Remove(std::shared_ptr<C_ColliderBox> object)
{
  int index = GetChildIndexForObject(object -> GetCollidable());

  if (index == CastToIndex(QuadtreeNodePosition::PARENT) || m_children[index] == nullptr)
  {
    for (int i = 0; i < m_objects.size(); i++)
    {
      if (m_objects[i] == object)
      {
        m_objects.erase(m_objects.begin() + i);
        break;
      }
    }
  }
  else
  {
    return m_children[index] -> Remove(object);
  }
}

void Quadtree::Clear()
{
  m_objects.clear();

  for (int i = 0; i < 4; i++)
  {
    if (m_children[i] != nullptr)
    {
      m_children[i] -> Clear();
      m_children[i] = nullptr;
    }
  }
}

void Quadtree::UpdatePosition(std::shared_ptr<C_ColliderBox> object)
{
  Quadtree *quadtree = this;

  const sf::FloatRect &prevObjectRect = object -> GetPreviousFrameCollidable();

  int index = quadtree -> GetChildIndexForObject(prevObjectRect);

  while (index != CastToIndex(QuadtreeNodePosition::PARENT) && quadtree -> m_children[index] != nullptr)
  {
    quadtree = quadtree -> m_children[index].get();
    index = quadtree -> GetChildIndexForObject(prevObjectRect);
  }

  for (int i = 0; i < quadtree -> m_objects.size(); i++)
  {
    if (quadtree -> m_objects[i] == object)
    {
      const sf::FloatRect &objectRect = object -> GetCollidable();

      if (!quadtree -> GetBounds().intersects(objectRect))
      {
        quadtree -> Remove(object);

        quadtree = quadtree -> m_parent;

        while (quadtree != nullptr && !quadtree -> GetBounds().intersects(objectRect))
        {
          quadtree = quadtree -> m_parent;
        }

        if (quadtree != nullptr)
        {
          quadtree -> Insert(object);
        }
      }

      break;
    }
  }
}

std::vector<std::shared_ptr<C_ColliderBox>> Quadtree::Search(const sf::FloatRect &area)
{
  std::vector<std::shared_ptr<C_ColliderBox>> possibleOverlaps;

  Search(area, possibleOverlaps);

  std::vector<std::shared_ptr<C_ColliderBox>> result;

  for (auto collider : possibleOverlaps)
  {
    if (area.intersects(collider -> GetCollidable()))
    {
      result.emplace_back(collider);
    }
  }

  return result;
}

const sf::FloatRect &Quadtree::GetBounds() const
{
  return m_bounds;
}

void Quadtree::Search(const sf::FloatRect &area,
                      std::vector<std::shared_ptr<C_ColliderBox>> &overlappingObjects)
{
  overlappingObjects.insert(overlappingObjects.end(), m_objects.begin(), m_objects.end());

  if (m_children[0] != nullptr)
  {
    int index = GetChildIndexForObject(area);

    if (index == CastToIndex(QuadtreeNodePosition::PARENT))
    {
      for (int i = 0; i < 4; i++)
      {
        if (m_children[i] -> GetBounds().intersects(area))
        {
          m_children[i] -> Search(area, overlappingObjects);
        }
      }
    }
    else
    {
      m_children[index] -> Search(area, overlappingObjects);
    }
  }
}

int Quadtree::GetChildIndexForObject(const sf::FloatRect &objectBounds)
{
  int index = -1;

  double verticalMidPoint = m_bounds.left + m_bounds.width * 0.5f;
  double horizontalMidPoint = m_bounds.top + m_bounds.height * 0.5f;

  bool north = objectBounds.top < horizontalMidPoint && (objectBounds.top + objectBounds.height < horizontalMidPoint);
  bool south = objectBounds.top > horizontalMidPoint;
  bool west = objectBounds.left < verticalMidPoint && (objectBounds.left + objectBounds.width < verticalMidPoint);
  bool east = objectBounds.left > verticalMidPoint;

  if (east)
  {
    if (north)
    {
      index = CastToIndex(QuadtreeNodePosition::CHILD_NE);
    }
    else if (south)
    {
      index = CastToIndex(QuadtreeNodePosition::CHILD_SE);
    }
  }
  else if (west)
  {
    if (north)
    {
      index = CastToIndex(QuadtreeNodePosition::CHILD_NW);
    }
    else if (south)
    {
      index = CastToIndex(QuadtreeNodePosition::CHILD_SW);
    }
  }

  return index;
}

void Quadtree::Split()
{
  int childWidth = m_bounds.width * 0.5f;
  int childHeight = m_bounds.height * 0.5f;

  m_children[CastToIndex(QuadtreeNodePosition::CHILD_NE)] = std::make_shared<Quadtree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left + childWidth, m_bounds.top, childWidth, childHeight), this);

  m_children[CastToIndex(QuadtreeNodePosition::CHILD_NW)] = std::make_shared<Quadtree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left, m_bounds.top, childWidth, childHeight), this);

  m_children[CastToIndex(QuadtreeNodePosition::CHILD_SW)] = std::make_shared<Quadtree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left, m_bounds.top + childHeight, childWidth, childHeight), this);

  m_children[CastToIndex(QuadtreeNodePosition::CHILD_SE)] = std::make_shared<Quadtree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left + childWidth, m_bounds.top + childHeight, childWidth, childHeight), this);
}