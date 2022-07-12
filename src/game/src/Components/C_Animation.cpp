#include <iostream>
#include <thread>

#include "C_Animation.hpp"

//
// FIXME: Use std::tie so the code becomes more readable.
//

C_Animation::C_Animation(Object *owner) 
  : Component(owner),
  m_currentAnimation(AnimationState::None, nullptr),
  m_currentDirection(FacingDirection::South) {}

void C_Animation::Awake()
{
  m_animationOwner = m_owner -> GetComponent<C_Sprite>();
}

void C_Animation::Update(float deltaTime)
{
  if (m_currentAnimation.first != AnimationState::None)
  {
    bool newFrame = m_currentAnimation.second -> UpdateFrame(deltaTime);

    if (newFrame)
    {
      const FrameData *frameData = m_currentAnimation.second -> GetCurrentFrame();

      m_animationOwner -> Load(frameData -> texture);
    }
  }
}

void C_Animation::SetAnimationFile(const std::string &filePath)
{
  //
  // WALKING ANIMATIONS.
  //

  auto animationWalkingNorth = std::make_shared<Animation>();
  auto animationWalkingEast  = std::make_shared<Animation>();
  auto animationWalkingSouth = std::make_shared<Animation>();
  auto animationWalkingWest  = std::make_shared<Animation>();

  animationWalkingNorth -> LoadMovementAnimation(filePath, 
                                                AnimationState::Walk, 
                                                FacingDirection::North);

  animationWalkingEast  -> LoadMovementAnimation(filePath, 
                                                 AnimationState::Walk, 
                                                 FacingDirection::East);

  animationWalkingSouth -> LoadMovementAnimation(filePath, 
                                                 AnimationState::Walk, 
                                                 FacingDirection::South);

  animationWalkingWest  -> LoadMovementAnimation(filePath, 
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

  animationIdleNorth -> LoadMovementAnimation(filePath, 
                                              AnimationState::Idle, 
                                              FacingDirection::North);

  animationIdleEast  -> LoadMovementAnimation(filePath, 
                                              AnimationState::Idle, 
                                              FacingDirection::East);

  animationIdleSotuh -> LoadMovementAnimation(filePath, 
                                              AnimationState::Idle, 
                                              FacingDirection::South);

  animationIdleWest  -> LoadMovementAnimation(filePath, 
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