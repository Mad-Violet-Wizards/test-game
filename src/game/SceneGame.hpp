#pragma once

#include "KeyboardInput.hpp"
#include "TiledMapParser.hpp"

class ObjectCollection;
class Scene;
class Object;

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
