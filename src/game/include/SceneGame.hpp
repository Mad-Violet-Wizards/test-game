#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "KeyboardInput.hpp"
#include "Object.hpp"
#include "ObjectCollection.hpp"
#include "TiledMapParser.hpp"
#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"
#include "C_Animation.hpp"
#include "C_Velocity.hpp"
#include "C_MovementAnimation.hpp"
#include "C_ColliderBox.hpp"
#include "C_Drawable.hpp"

class SceneGame : public Scene
{

public:

  SceneGame();
  ~SceneGame();

  void OnCreate() override;
  void OnDestroy() override;

  void Update(float deltaTime) override;
  void LateUpdate(float deltaTime) override;
  void Draw(Window &window) override;

private:

  ObjectCollection m_objects;

  std::shared_ptr<Object> m_player;

  KeyboardInput m_keyboardInput;

  TiledMapParser m_mapParser;

};
