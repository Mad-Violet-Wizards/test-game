#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <memory>

#include "Component.hpp"
#include "Animation.hpp"
#include "C_Sprite.hpp"

using AnimationList = std::map<FacingDirection, std::shared_ptr<Animation>>;

class C_Animation : public Component
{

public:

  C_Animation(Object *owner);

  void Awake() override;
  void Update(float deltaTime) override;

  void SetAnimationFile(const std::string &filePath);

  void SetAnimationState(AnimationState state);
  AnimationState GetAnimationState() const;

  void SetAnimationDirection(FacingDirection direction);
  FacingDirection GetFacingDirection() const;


private:

  void LoadSingleFileAnimation(rapidjson::Document &animationDocument);

  std::string m_textureFileName;

  std::shared_ptr<C_Sprite> m_animationOwner;

  std::map<AnimationState, AnimationList> m_animations;
  std::pair<AnimationState, std::shared_ptr<Animation>> m_currentAnimation;
  FacingDirection m_currentDirection;
};