#include "Scene/SceneStateMachine.hpp"

SceneStateMachine::SceneStateMachine() : m_scenes(0), m_currentScene(nullptr) {}

SceneStateMachine::~SceneStateMachine() {}

void SceneStateMachine::ProcessInput()
{
  if (m_currentScene)
  {
    m_currentScene -> ProcessInput();
  }
}

void SceneStateMachine::Update(float deltaTime)
{
  if (m_currentScene)
  {
    m_currentScene -> Update(deltaTime);
  }
}

void SceneStateMachine::Draw(Window& window)
{
  if (m_currentScene)
  {
    m_currentScene -> Draw(window);
  }
}

unsigned int SceneStateMachine::Add(std::shared_ptr<Scene> scene)
{
  auto inserted = m_scenes.insert(std::make_pair(insertedSceneID, scene));

  inserted.first -> second -> OnCreate();

  return insertedSceneID++;
}

void SceneStateMachine::Remove(unsigned int id)
{
  auto it = m_scenes.find(id);

  if (it != m_scenes.end())
  {
    if (m_currentScene == it -> second)
    {
      m_currentScene = nullptr;
    }

    it -> second -> OnDestroy();

    m_scenes.erase(it);
  }
}

void SceneStateMachine::SwitchTo(unsigned int id)
{
  auto it = m_scenes.find(id);
  if (it != m_scenes.end())
  {
    if (m_currentScene)
    {
      m_currentScene -> OnDeactivate();
    }

    m_currentScene = it -> second; // Passing ownership of m_scene - must be shared_ptr

    m_currentScene -> OnActivate();
  }
}