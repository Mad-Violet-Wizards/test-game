#pragma once

#include "Utility/Bitmask.hpp"

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
  Walk,
  Projectile
};

struct FrameData
{
  int x;
  int y;

  int width;
  int height;

  double displayTime;
};

using AnimationAction = std::function<void(void)>;

class Animation
{

public:

  Animation();
  ~Animation();

  // TODO: Maybe this method should be moved to different place?

  void LoadMovementAnimationFromFile(rapidjson::Document &animationDocument,
                                       AnimationState state, 
                                       FacingDirection direction);

  void AddFrame(int x, int y, int width, int height, double displayTime);

  void AddFrameAction(int frame, AnimationAction action);

  const FrameData *GetCurrentFrame() const;

  bool UpdateFrame(float deltaTime);

  void Reset();

  void SetLooped(bool looped);
  bool IsLooped() const;

private:

  void IncrementFrame();
  void RunActionForCurrentFrame();

private:

  std::vector<FrameData> m_frames;

  int m_currentFrameIndex;

  float m_currentFrameTime;
  bool m_releaseFirstFrame;
  bool m_looped;

  std::map<int, std::vector<AnimationAction>> m_actions;
  Bitmask m_framesWithAction;

};