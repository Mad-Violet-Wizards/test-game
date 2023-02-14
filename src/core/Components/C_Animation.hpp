#pragma once


using AnimationList = std::map<FacingDirection, std::shared_ptr<Animation>>;

class Component;
class C_Sprite;
class C_Direction;

class C_Animation : public Component
{

public:

  C_Animation(Object *owner);

  void Awake() override;
  void Update(float deltaTime) override;

  void SetAnimationFile(const std::string &filePath);

  void AddAnimation(AnimationState state, AnimationList &animationList);

  void SetAnimationState(AnimationState state);
  AnimationState GetAnimationState() const;

  void SetAnimationDirection(FacingDirection direction);
  FacingDirection GetFacingDirection() const;

  void AddAnimationAction(AnimationState state, FacingDirection dir, int frame, AnimationAction action);

private:

  void LoadMovementAnimationFromFile(rapidjson::Document &animationDocument);

  std::string m_textureFileName;

  std::shared_ptr<C_Sprite> m_animationOwner;
  std::shared_ptr<C_Direction> m_direction;

  std::map<AnimationState, AnimationList> m_animations;
  std::pair<AnimationState, std::shared_ptr<Animation>> m_currentAnimation;
  FacingDirection m_currentDirection;
};