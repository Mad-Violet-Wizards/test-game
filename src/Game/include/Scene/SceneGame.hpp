#pragma once

#include <SFML/Graphics.hpp>

#include "Scene/Scene.hpp"
#include "Input.hpp"

class SceneGame : public Scene
{
  public:

    SceneGame();
    ~SceneGame();

    void OnCreate() override;
    void OnDestroy() override;

    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Draw(Window& window) override;

  private:

    Input m_input;

    sf::CircleShape m_testShape;
};
