#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>

#include "JsonHandler.hpp"

enum class FacingDirection
{
  None,
  North,
  East,
  South,
  West
};

enum class AnimationState
{
  None,
  Idle,
  Walk
};

struct FrameData
{
  std::shared_ptr<sf::Texture> texture;

  int width;
  int height;

  double displayTime;
};

class Animation
{

public:

  Animation();
  ~Animation();

  void LoadMovementAnimation(const std::string &filePath, 
                             AnimationState state, 
                             FacingDirection direction);

  const FrameData *GetCurrentFrame() const;

  bool UpdateFrame(float deltaTime);

  void Reset();

private:

  void IncrementFrame();

private:

  std::vector<FrameData> m_frames;

  int m_currentFrameIndex;

  float m_currentFrameTime;
  bool m_releaseFirstFrame;

};