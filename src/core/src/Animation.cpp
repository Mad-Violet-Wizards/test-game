#include <iostream>
#include <fstream>

#include "Log.hpp"
#include "JsonHandler.hpp"
#include "Animation.hpp"
#include "Directory.hpp"

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

void Animation::LoadMovementAnimationMultipleFile(rapidjson::Document &animationDocument, 
                                                  AnimationState state, 
                                                  FacingDirection direction)
{
  using namespace rapidjson;

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

  for (auto &textureJsonObject : animationFilesArray.GetArray())
  {
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

    if (!texture -> loadFromFile(Directory::ANIMATIONS_DIRECTORY + textureJsonObject["fileName"].GetString()))
    {
      LOG_WARNING("[Animation] Could not load the file.")
    }

    FrameData frameData;
    
    frameData.texture = texture;
    frameData.width = 0;
    frameData.height = 0;
    frameData.displayTime = textureJsonObject["frameDuration"].GetDouble();

    m_frames.push_back(frameData);
  }
}

void Animation::LoadMovementAnimationSingleFile(rapidjson::Document &animationDocument,
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

  int tileRow = animationDetails["tileRow"].GetInt();
  int tileWidth = 32;
  int tileHeight = 32;
  int frameCount = animationDetails["frameCount"].GetInt();
  float frameDuration = animationDetails["frameDuration"].GetDouble();

  int x = 0;
  int y = tileRow * tileHeight;

  LOG_INFO(tileHeight);

  for (int i = 0; i < frameCount; i++)
  {
    LOG_INFO("Frame data added: ", tileRow);

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