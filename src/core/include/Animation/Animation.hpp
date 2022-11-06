#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <string>

#include "rapidjson/document.h"

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
  int x;
  int y;

  int width;
  int height;

  double displayTime;
};

class Animation
{

public:

  Animation();
  ~Animation();

  // FIXME: Change the god damn name of this method.

  void LoadMovementAnimationSingleFile(rapidjson::Document &animationDocument,
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