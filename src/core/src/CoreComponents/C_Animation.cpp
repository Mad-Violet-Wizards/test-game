#include <iostream>

#include "rapidjson/document.h"

#include "AssetsManager.hpp"
#include "Directory.hpp"
#include "JsonHandler.hpp"
#include "C_Animation.hpp"

//
// FIXME: Use std::tie so the code becomes more readable.
//

C_Animation::C_Animation(Object *owner) 
  : Component(owner),
  m_currentAnimation(AnimationState::None, nullptr),
  m_currentDirection(FacingDirection::South),
  m_singleFile(false) {}

void C_Animation::Awake()
{
  m_animationOwner = owner -> GetComponent<C_Sprite>();
}

void C_Animation::Update(float deltaTime)
{
  if (m_currentAnimation.first != AnimationState::None)
  {
    bool newFrame = m_currentAnimation.second -> UpdateFrame(deltaTime);

    if (newFrame)
    {
      const FrameData *frameData = m_currentAnimation.second -> GetCurrentFrame();

      if (m_singleFile)
      {
        m_animationOwner -> Load(AssetsManager::GetInstance().GetTexture(m_textureFileName));
        m_animationOwner -> SetTextureRect(frameData -> x, frameData -> y, frameData -> width, frameData -> height);
      }
      else
      {
        m_animationOwner -> Load(frameData -> texture);
      }
    }
  }
}

void C_Animation::SetAnimationFile(const std::string &filePath)
{
  //
  // WALKING ANIMATIONS.
  //

  static JsonHandler jsonHandler;
  jsonHandler.LoadFile(filePath);

  static rapidjson::Document animationDocument;
  animationDocument.Parse(jsonHandler.GetJsonContent());

  rapidjson::Value isSingleFile;

  isSingleFile = animationDocument["single-file"];

  assert(isSingleFile.IsBool());

  if (isSingleFile.GetBool() == true)
  {
    LOG_INFO("[C_Animation] Loading single file animation.");
    LoadSingleFileAnimation(animationDocument);
  }
  else
  {
    LOG_INFO("[C_Animation] Loading multiple file animation.");
    LoadMultipleFileAnimation(animationDocument);
  }
}

void C_Animation::SetAnimationState(AnimationState state)
{
  if (m_currentAnimation.first == state)
  {
    return;
  }

  auto animationList = m_animations.find(state);

  if (animationList != m_animations.end())
  {
    auto animation = animationList -> second.find(m_currentDirection);

    if (animation != animationList -> second.end())
    {
      m_currentAnimation.first = animationList -> first;
      m_currentAnimation.second = animation -> second;
      m_currentAnimation.second -> Reset();
    }
  }
}

AnimationState C_Animation::GetAnimationState() const
{
  return m_currentAnimation.first;
}

void C_Animation::SetAnimationDirection(FacingDirection direction)
{
  if (m_currentDirection != direction)
  {
    m_currentDirection = direction;

    auto animationList = m_animations.find(m_currentAnimation.first);

    if (animationList != m_animations.end())
    {
      auto animation = animationList -> second.find(m_currentDirection);

      if (animation != animationList -> second.end())
      {
        m_currentAnimation.second = animation -> second;
        m_currentAnimation.second -> Reset();
      }
    }
  }
}

FacingDirection C_Animation::GetFacingDirection() const
{
  return m_currentDirection;
}

void C_Animation::LoadSingleFileAnimation(rapidjson::Document &animationDocument)
{

  //
  // WALKING ANIMATIONS.
  //

  m_textureFileName = std::move(animationDocument["animation-file"].GetString());

  m_singleFile = true;

  auto animationWalkingNorth = std::make_shared<Animation>();
  auto animationWalkingEast  = std::make_shared<Animation>();
  auto animationWalkingSouth = std::make_shared<Animation>();
  auto animationWalkingWest  = std::make_shared<Animation>();

  animationWalkingNorth -> LoadMovementAnimationSingleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::North);

  animationWalkingEast  -> LoadMovementAnimationSingleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::East);

  animationWalkingSouth -> LoadMovementAnimationSingleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::South);

  animationWalkingWest  -> LoadMovementAnimationSingleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::West);

  std::map<FacingDirection, std::shared_ptr<Animation>> walkingAnimations;

  walkingAnimations.insert( { FacingDirection::North, animationWalkingNorth } );
  walkingAnimations.insert( { FacingDirection::East,  animationWalkingEast } );
  walkingAnimations.insert( { FacingDirection::South, animationWalkingSouth } );
  walkingAnimations.insert( { FacingDirection::West,  animationWalkingWest } );

  m_animations.insert( { AnimationState::Walk, walkingAnimations } );

  //
  // IDLE ANIMATIONS
  //

  auto animationIdleNorth = std::make_shared<Animation>();
  auto animationIdleEast  = std::make_shared<Animation>();
  auto animationIdleSotuh = std::make_shared<Animation>();
  auto animationIdleWest  = std::make_shared<Animation>();

  animationIdleNorth -> LoadMovementAnimationSingleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::North);

  animationIdleEast  -> LoadMovementAnimationSingleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::East);

  animationIdleSotuh -> LoadMovementAnimationSingleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::South);

  animationIdleWest  -> LoadMovementAnimationSingleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::West);

  std::map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;

  idleAnimations.insert( { FacingDirection::North, animationIdleNorth } );
  idleAnimations.insert( { FacingDirection::East,  animationIdleEast } );
  idleAnimations.insert( { FacingDirection::South, animationIdleSotuh } );
  idleAnimations.insert( { FacingDirection::West,  animationIdleWest } );

  m_animations.insert( { AnimationState::Idle, idleAnimations } );

  if (m_currentAnimation.first == AnimationState::None)
  {
    SetAnimationState(AnimationState::Idle);
  }

}

void C_Animation::LoadMultipleFileAnimation(rapidjson::Document &animationDocument)
{

  //
  // WALKING ANIMATIONS
  //

  auto animationWalkingNorth = std::make_shared<Animation>();
  auto animationWalkingEast  = std::make_shared<Animation>();
  auto animationWalkingSouth = std::make_shared<Animation>();
  auto animationWalkingWest  = std::make_shared<Animation>();

  animationWalkingNorth -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::North);

  animationWalkingEast  -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::East);

  animationWalkingSouth -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::South);

  animationWalkingWest  -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                             AnimationState::Walk, 
                                                             FacingDirection::West);

  std::map<FacingDirection, std::shared_ptr<Animation>> walkingAnimations;

  walkingAnimations.insert( { FacingDirection::North, animationWalkingNorth } );
  walkingAnimations.insert( { FacingDirection::East,  animationWalkingEast } );
  walkingAnimations.insert( { FacingDirection::South, animationWalkingSouth } );
  walkingAnimations.insert( { FacingDirection::West,  animationWalkingWest } );

  m_animations.insert( { AnimationState::Walk, walkingAnimations } );

  //
  // IDLE ANIMATIONS
  //

  auto animationIdleNorth = std::make_shared<Animation>();
  auto animationIdleEast  = std::make_shared<Animation>();
  auto animationIdleSotuh = std::make_shared<Animation>();
  auto animationIdleWest  = std::make_shared<Animation>();

  animationIdleNorth -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::North);

  animationIdleEast  -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::East);

  animationIdleSotuh -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::South);

  animationIdleWest  -> LoadMovementAnimationMultipleFile(animationDocument, 
                                                          AnimationState::Idle, 
                                                          FacingDirection::West);

  std::map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;

  idleAnimations.insert( { FacingDirection::North, animationIdleNorth } );
  idleAnimations.insert( { FacingDirection::East,  animationIdleEast } );
  idleAnimations.insert( { FacingDirection::South, animationIdleSotuh } );
  idleAnimations.insert( { FacingDirection::West,  animationIdleWest } );

  m_animations.insert( { AnimationState::Idle, idleAnimations } );

  if (m_currentAnimation.first == AnimationState::None)
  {
    SetAnimationState(AnimationState::Idle);
  }
}