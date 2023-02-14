#include "Animation.hpp"

Animation::Animation() 
  : m_currentFrameIndex(0),
  m_currentFrameTime(0.f),
  m_releaseFirstFrame(true),
  m_looped(false) {}

Animation::~Animation() {}

void Animation::AddFrame(int x, int y, int width, int height, double displayTime)
{
  m_frames.push_back(FrameData{ x, y, width, height, displayTime});
}

void Animation::AddFrameAction(int frame, AnimationAction action)
{
  if (frame < m_frames.size())
  {
    auto actionKey = m_actions.find(frame);

    if (actionKey == m_actions.end())
    {
      m_framesWithAction.SetBit(frame);
      m_actions.insert({frame, std::vector<AnimationAction>{action}});
    }
    else
    {
      actionKey->second.emplace_back(action);
    }
  }
  else
  {
    FILE_LOG_ERROR("debug.txt", "[Animation] Frame index out of range.");
  }
}

void Animation::LoadMovementAnimationFromFile(rapidjson::Document &animationDocument,
                                                AnimationState state,
                                                FacingDirection direction)
{
  using namespace rapidjson;

  Value animationDetails;

  if (state == AnimationState::Walk)
  {
    if (direction == FacingDirection::North)      { animationDetails = animationDocument["walking-north"]; }
    else if (direction == FacingDirection::East)  { animationDetails = animationDocument["walking-east"]; }
    else if (direction == FacingDirection::South) { animationDetails = animationDocument["walking-south"]; }
    else if (direction == FacingDirection::West)  { animationDetails = animationDocument["walking-west"]; }
  }
  else if (state == AnimationState::Idle)
  {
    if (direction == FacingDirection::North)      { animationDetails = animationDocument["idle-north"]; }
    else if (direction == FacingDirection::East)  { animationDetails = animationDocument["idle-east"]; }
    else if (direction == FacingDirection::South) { animationDetails = animationDocument["idle-south"]; }
    else if (direction == FacingDirection::West)  { animationDetails = animationDocument["idle-west"]; }
  }

  // FIXME: Tile width & height should be read from the json file.

  int tileRow = animationDetails["tileRow"].GetInt();
  int tileWidth = 32;
  int tileHeight = 32;
  int frameCount = animationDetails["frameCount"].GetInt();
  float frameDuration = animationDetails["frameDuration"].GetDouble();

  int x = 0;
  int y = tileRow * tileHeight;

  for (int i = 0; i < frameCount; i++)
  {
    FrameData frameData;

    frameData.x = x;
    frameData.y = y;

    frameData.width = tileWidth;
    frameData.height = tileHeight;

    frameData.displayTime = animationDetails["frameDuration"].GetDouble();

    m_frames.push_back(frameData);

    x += tileWidth;
  }
}

const FrameData *Animation::GetCurrentFrame() const
{
  if (m_frames.size() > 0) 
  { 
    return &m_frames[m_currentFrameIndex]; 
  }

  FILE_LOG_WARNING("debug.txt", "[Animation][GetCurrentFrame] Returned nullptr.");
  return nullptr;
}

bool Animation::UpdateFrame(float deltaTime)
{
  if (m_releaseFirstFrame)
  {
    RunActionForCurrentFrame();
    m_releaseFirstFrame = false;
    return true;
  }

  if (m_frames.size() > 1 && (m_looped || m_currentFrameIndex < m_frames.size() - 1))
  {
    m_currentFrameTime += deltaTime;

    if (m_currentFrameTime >= m_frames.at(m_currentFrameIndex).displayTime)
    {
      m_currentFrameTime = 0.0;

      IncrementFrame();
      RunActionForCurrentFrame();

      return true;
    }
  }

  return false;
}

void Animation::Reset()
{
  m_currentFrameIndex = 0;
  m_currentFrameTime = 0.f;
  m_releaseFirstFrame = true;
}

void Animation::SetLooped(bool looped)
{
  m_looped = looped;
}

bool Animation::IsLooped() const
{
  return m_looped;
}

void Animation::IncrementFrame()
{
  m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
}

void Animation::RunActionForCurrentFrame()
{
  if (m_actions.size() > 0)
  {
    if (m_framesWithAction.GetBit(m_currentFrameIndex))
    {
      auto actionsToRun = m_actions.at(m_currentFrameIndex);

      for (auto action : actionsToRun)
      {
        action();
      }
    }
  }
}