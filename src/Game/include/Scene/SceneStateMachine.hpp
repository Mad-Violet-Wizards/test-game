#pragma once

#include <memory>
#include <unordered_map>

#include "Scene/Scene.hpp"
#include "Window.hpp"

class SceneStateMachine
{
public:

  SceneStateMachine();
  ~SceneStateMachine();

  void ProcessInput();
  void Update(float deltaTime);
  void Draw(Window& window);

  unsigned int Add(std::shared_ptr<Scene> scene);
  void SwitchTo(unsigned int id);
  void Remove(unsigned int id);

private:

  std::unordered_map<unsigned int, std::shared_ptr<Scene>> m_scenes;
  std::shared_ptr<Scene> m_currentScene;
  unsigned int insertedSceneID;
};