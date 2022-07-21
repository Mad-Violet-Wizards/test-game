#include <iostream>
#include <fstream>

#include "Log.hpp"
#include "JsonHandler.hpp"
#include "Animation.hpp"

#include "rapidjson/document.h"

Animation::Animation() 
  : m_currentFrameIndex(0),
  m_currentFrameTime(0.f),
  m_releaseFirstFrame(true) {}

Animation::~Animation() {}

//
// FIXME: Problem here is that we're loading JSON 4 times
// for every sprite that requires to allocate 
// animation textures and informations.
//

void Animation::LoadMovementAnimation(const std::string &filePath, 
                                      AnimationState state, 
                                      FacingDirection direction)
{
  using namespace rapidjson;

  LOG_INFO("[Animation] Loading animations for: ", filePath);

  static JsonHandler jsonHandler;
  jsonHandler.LoadFile(filePath);

  static Document animationDocument;
  animationDocument.Parse(jsonHandler.GetJsonContent());

  const std::string animationAssetsFilePath = "../assets/animations/";

  Value animationFilesArray;

  if (state == AnimationState::Walk)
  {
    if (direction == FacingDirection::North)      { animationFilesArray = animationDocument["walking-north"]; }
    else if (direction == FacingDirection::East)  { animationFilesArray = animationDocument["walking-east"]; }
    else if (direction == FacingDirection::South) { animationFilesArray = animationDocument["walking-south"]; }
    else if (direction == FacingDirection::West)  { animationFilesArray = animationDocument["walking-west"]; }
  }
  else if (state == AnimationState::Idle)
  {
    if (direction == FacingDirection::North)      { animationFilesArray = animationDocument["idle-north"]; }
    else if (direction == FacingDirection::East)  { animationFilesArray = animationDocument["idle-east"]; }
    else if (direction == FacingDirection::South) { animationFilesArray = animationDocument["idle-south"]; }
    else if (direction == FacingDirection::West)  { animationFilesArray = animationDocument["idle-west"]; }
  }

  assert(animationFilesArray.IsArray());

  for (auto &textureFile : animationFilesArray.GetArray())
  {
    std::shared_ptr<sf::Texture> texture(new sf::Texture);

    if (!texture -> loadFromFile(animationAssetsFilePath + textureFile.GetString()))
    {
      LOG_WARNING("[Animation] Could not load the file.")
    }

    if (state == AnimationState::Idle)
    {
      m_frames.emplace_back(texture, 0, 0, 0.f);
    }
    else
    {
      m_frames.emplace_back(texture, 0, 0, 0.2f);
    }
  }
}

const FrameData *Animation::GetCurrentFrame() const
{
  if (m_frames.size()  > 0) 
  { 
    return &m_frames[m_currentFrameIndex]; 
  }

  LOG_WARNING("[Animation][GetCurrentFrame] Returned nullptr.");
  return nullptr;
}

bool Animation::UpdateFrame(float deltaTime)
{
  if (m_releaseFirstFrame)
  {
    m_releaseFirstFrame = false;
    return true;
  }

  if (m_frames.size() > 1)
  {
    m_currentFrameTime += deltaTime;
  }

  if (m_currentFrameTime >= m_frames[m_currentFrameIndex].displayTime)
  {
    m_currentFrameTime = 0.f;
    IncrementFrame();
    return true;
  }

  return false;
}

void Animation::Reset()
{
  m_currentFrameIndex = 0;
  m_currentFrameTime = 0.f;
  m_releaseFirstFrame = true;
}

void Animation::IncrementFrame()
{
  m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
}